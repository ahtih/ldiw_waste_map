<?php
// $Id

function _ldiw_api_set_language($language_code)
{
	global $language;
	$languages=language_list('language');
	if (!empty($languages[$language_code]) &&
						!empty($languages[$language_code]->enabled)) {
		$language=$languages[$language_code];
		}
	}

function _ldiw_api_get_server_specific_fields()
{
	$data=array();
	$fields_to_omit=explode(' ',variable_get(
						'ldiw_waste_map_photo_field_names',
						LDIW_WASTE_MAP_DEFAULT_PHOTO_FIELDS));
	$fields_to_omit[]='field_geo_areas_json';
	$fields_to_omit[]='field_cleaned_by_mapper';

	$content_fields=content_fields(NULL,'waste_point');
	$composition_fields=variable_get('ldiw_waste_map_composition_fields',
																array());

	if (variable_get('ldiw_waste_map_single_composition_value',FALSE)) {
		$composition_weight=NULL;
		$composition_values=array();
		foreach ($composition_fields as $key => $info) {
			$fields_to_omit[]=$key;
			$composition_values[]=array($key,
								$content_fields[$key]['widget']['label']);
			if (isset($content_fields[$key]['widget']['weight']) &&
					(!isset($composition_weight) ||
					$content_fields[$key]['widget']['weight'] <
													$composition_weight)) {
				$composition_weight=$content_fields[$key]['widget']['weight'];
				}
			}
		$data['composition']=array(
				$composition_weight,
				'composition',
				array('type' => 'text',
						'label' => t('Composition'),
						'allowed_values' => $composition_values,
						),
				);
		}

	foreach ($content_fields as $fieldname => $field) {
		if ($field['type_name'] == 'waste_point' && in_array($field['type'],
						array('number_float','number_integer','text')) &&
						!in_array($fieldname,$fields_to_omit)) {
			$key=preg_replace('/^field_(..*)$/','$1',$fieldname);

			$entry=array('type' => preg_replace('/^number_(..*)$/','$1',
														$field['type']));

			if ($entry['type'] == 'integer' &&
					isset($field['min']) && isset($field['max']) &&
					(''.$field['min']) == '0' && (''.$field['max']) == '1') {
				$entry['type']='boolean';
				}

			if (!empty($field['suffix'])) {
				$entry['suffix']=$field['suffix'];
				}

			if (!empty($field['widget']['label'])) {
				$entry['label']=$field['widget']['label'];
				}

			if (!empty($field['widget']['description'])) {
				$entry['edit_instructions']=$field['widget']['description'];
				}

			$allowed_values=content_allowed_values($field);
			if ($allowed_values && $entry['type'] != 'boolean') {
				$entry['allowed_values']=array();
				foreach ($allowed_values as $tag => $value) {
					if (in_array($entry['type'],array('integer','float'))) {
						$tag=0 + $tag;
						}
					$entry['allowed_values'][]=array($tag,$value);
					}
				}
			else {
				if (in_array($entry['type'],array('integer','float'))) {
					foreach (array('min','max') as $f) {
						if (isset($field[$f])) {
							$entry[$f]=0 + $field[$f];
							}
						}

					if (isset($composition_fields[$fieldname])) {
						$entry['typical_values']=array(
												array(0,'0'),
												array(10,'10'),
												array(20,'20'),
												array(30,'30'),
												array(40,'40'),
												array(50,'50'),
												array(60,'60'),
												array(70,'70'),
												array(80,'80'),
												array(90,'90'),
												array(100,'100'),
												);
						}

					if ($key == 'volume') {
						$entry['typical_values']=array(
								array(0.3 / 1000.0,
									t("It all fits into my pocket")),
								array(4 / 1000.0,
									t("Fits in a plastic shopping bag")),
								array(0.5,
									t("Fits into luggage trunk of a car")),
								array(3,
									t("Fits into industrial truck/cargo vehicle")),
								array(30,
									t("It's even more than that")),
								);
						}

					//!!! Make typical_values configurable for custom fields
					}
				}

			if ($entry['type'] == 'text' && empty($entry['allowed_values']) &&
											isset($field['max_length'])) {
				$entry['max_length']=$field['max_length'];
				}

			$data[$key]=array(isset($field['widget']['weight']) ?
											$field['widget']['weight'] : 0,
								$fieldname,$entry);
			}
		}

	$node_type=node_get_types('type','waste_point');
	if ($node_type->has_body) {
		$extra_weights=
				variable_get('content_extra_weights_waste_point',array());
		$data['description']=array(
				isset($extra_weights['body_field']) ?
										$extra_weights['body_field'] : 0,
				'body',array(
						'type' => 'text',
						'label' => t($node_type->body_label),
						'max_length' =>
								LDIW_WASTE_MAP_WP_DESCRIPTION_MAX_LENGTH)
				);
		}

	asort($data);	// Ensure well-defined field order

	foreach (array_keys($data) as $key) {
		$data[$key]=array_slice($data[$key],1);
		$data[$key][1]['field_name']=$key;
		}

	return $data;
	}

function ldiw_api_get_api_base_url()
{
	$result=array(
			'api_base_url' => 'http://api.letsdoitworld.org/?q=api',
			'safe_bbox' => '-180,-90,180,90',
			);
	$display_coords='empty coords';

	if (isset($_REQUEST['lon']) && isset($_REQUEST['lat'])) {
	
		$coords=array(floatval($_REQUEST['lon']),floatval($_REQUEST['lat']));
		$display_coords=implode(',',$coords);

		$views_result=views_get_view_result('api_servers_for_point',NULL,
									'POINT(' . implode(' ',$coords) . ')');
		$servers=array();
		foreach ($views_result as $entry) {
			$servers[$entry->node_node_data_field_hierarchy_level_nid]=
														$entry->node_title;
			}

			/**************************************************/
			/*****                                        *****/
			/***** Eliminate parent areas from $servers[] *****/
			/*****                                        *****/
			/**************************************************/

		$processed_level_nids=array();
		$unprocessed_level_nids=$servers;

		while (count($servers) >= 2 && $unprocessed_level_nids) {
			$keys=array_keys($unprocessed_level_nids);
			$nid=$keys[0];
			unset($unprocessed_level_nids[$nid]);
			$processed_level_nids[$nid]=TRUE;

			$node=node_load($nid);
			if (!empty($node->field_parent_level[0]['nid'])) {
				$parent_nid=$node->field_parent_level[0]['nid'];
				$unprocessed_level_nids[$parent_nid]=TRUE;
				unset($servers[$parent_nid]);
				}
			}

		if (!empty($servers)) {
			$result['api_base_url']=array_pop($servers);
			}

			/*************************/
			/*****               *****/
			/***** Set safe_bbox *****/
			/*****               *****/
			/*************************/

		$geo_handler=geo_load(array('name' => 'field_geo'));
		$areas_table_name=$geo_handler->tableName(TRUE);
		$geo_handler->setTableName("a",TRUE);

		for ($coords_delta=2;;$coords_delta /= 4.0) {
			$safe_bbox=array(	$coords[0]-$coords_delta,
								$coords[1]-$coords_delta,
								$coords[0]+$coords_delta,
								$coords[1]+$coords_delta);
			$result['safe_bbox']=implode(',',$safe_bbox);
			if ($coords_delta < 1e-4) {
				break;
				}
			list($wkt,$query_params)=geoclustering_polygon_sql($safe_bbox);

			//!!! This query often takes 150ms
			if (!db_fetch_array(db_query("SELECT 1 " .
						"FROM $areas_table_name AS a " .
								"INNER JOIN {node} AS n ON (n.nid=a.nid) " .
						"WHERE " . $geo_handler->intersects($geo_handler,
												$wkt) . " AND NOT " .
						$geo_handler->contains($geo_handler,$wkt) . " " .
						"LIMIT 1",
						array_merge($query_params,$query_params)))) {
				break;
				}
			}
		}

	watchdog('ldiw_api',"Client requested API base_url for %coords, " .
															"returned %url",
							array('%coords' => $display_coords,
								'%url' => $result['api_base_url']),
							WATCHDOG_NOTICE);

	print json_encode($result);
	}

/***************************************************************************/
/********************                                   ********************/
/******************** ldiw_api_waste_point_extra_fields ********************/
/********************                                   ********************/
/***************************************************************************/

function _ldiw_api_waste_point_extra_fields()
{
	$retval=array();

		/**********************************************/
		/*****                                    *****/
		/***** Set language for this HTTP request *****/
		/*****                                    *****/
		/**********************************************/

	if (isset($_REQUEST['language_code'])) {
		_ldiw_api_set_language($_REQUEST['language_code']);
		}

	$composition_fields=variable_get('ldiw_waste_map_composition_fields',
																array());
	$composition_section_started=FALSE;
	foreach (_ldiw_api_get_server_specific_fields() as $key => $info) {
		if (isset($composition_fields[$info[0]]) &&
										!$composition_section_started) {
			$composition_section_started=TRUE;
			$retval[]=array('type' => 'begin_section',
						'label' => t('Composition percentages (in volume)'));
			}

		$retval[]=$info[1];
		}

	//!!! how to encode Unicode >255 chars?

	print json_encode($retval);
	}

/***************************************************************************/
/******************                                       ******************/
/****************** _ldiw_api_set_server_specific_field() ******************/
/******************                                       ******************/
/***************************************************************************/

function _ldiw_api_set_server_specific_field(&$form_state,$info,&$value)
{
	if ($info[1]['type'] == 'text' && !isset($value)) {
		$value='';
		}
	if ($info[1]['type'] == 'float' && isset($value) && floatval($value)) {
		$value=floatval($value);
		}

	if ($info[0] == 'body' || $info[0] == 'composition') {
		$form_state['values'][$info[0]]=$value;
		}
	else {
		$form_state['values'][$info[0]][0]['value']=$value;
		}
	}

/***************************************************************************/
/**************************                       **************************/
/************************** _ldiw_api_save_node() **************************/
/**************************                       **************************/
/***************************************************************************/

function _ldiw_api_save_node($node,$form_state,$file_fids)
{
	$node_or_errormsg=ldiw_waste_map_submit_waste_point_form(
											$node,$form_state,$file_fids);
	if (!is_object($node_or_errormsg)) {
		watchdog('ldiw_api',"Error in request sent by API client: %error",
									array('%error' => $node_or_errormsg));
		throw new ServicesException($node_or_errormsg,400);
		}

	return $node_or_errormsg;
	}

/***************************************************************************/
/************************                           ************************/
/************************ _ldiw_api_create_update() ************************/
/************************                           ************************/
/***************************************************************************/

function _ldiw_api_create_update($args,$id=FALSE)
{
	global $user;
	if (!$user->uid) {
		foreach ($_COOKIE as $key => $value) {
			if (strpos($key,'SESS') === 0) {
				watchdog('ldiw_api',
							"Invalid session cookie sent by API client");
				throw new ServicesException("Invalid session cookie",401);
				}
			}
		}

	$coords=array_splice($args,0,2);

	list($node,$form_state)=ldiw_waste_map_prepare_adding_waste_point(
															$coords,$id);

	if ($coords !== FALSE && (!isset($coords[0]) || !isset($coords[1]))) {
		watchdog('ldiw_api',"Missing required lon/lat fields " .
										"in request sent by API client");
		throw new ServicesException("Missing required lon/lat fields",400);
		}

	$client_id=array_shift($args);
	//!!! Store client_id field

	$cleaned_by_mapper=array_shift($args);

		/**********************/
		/*****            *****/
		/***** Set photos *****/
		/*****            *****/
		/**********************/

	$photo_fields=ldiw_waste_map_get_photo_upload_fields();

	$file_fids=array();
	foreach ($photo_fields as $idx => $photo_field) {
		$photo_param=array_shift($args);
		if (!$photo_param) {
			continue;
			}
		if (is_object($photo_param)) {
			$fname=$photo_param->tmp_name;
			}
		else if (is_array($photo_param)) {
			$fname=$photo_param['tmp_name'];
			}
		else {
			$fname=file_destination(file_create_path(
					file_directory_temp() . '/' . time()),FILE_EXISTS_RENAME);
			$fp=fopen($fname,'w');
			if ($fp === FALSE) {
				continue;
				}
			fwrite($fp,$photo_param);
			fclose($fp);
			}
		$fileinfo=field_file_save_file($fname,array(),
					filefield_widget_file_path(content_fields(
									$photo_field[0],'waste_point')));
		@unlink($fname);
		$form_state['values'][$photo_field[0]][$photo_field[1]]=$fileinfo;

		$file_fids[]=$fileinfo['fid'];
		}

		/****************************************/
		/*****                              *****/
		/***** Write server-specific fields *****/
		/*****                              *****/
		/****************************************/

	$mapped_as_no_waste=TRUE;
	$server_specific_fields=_ldiw_api_get_server_specific_fields();
	if ($args !== array_fill(0,count($args),null)) {
		foreach ($server_specific_fields as $key => $info) {
			$value=array_shift($args);
			_ldiw_api_set_server_specific_field($form_state,$info,$value);

			if (($key == 'volume' || $key == 'diameter') && !empty($value)) {
					//!!! If there are no server-specific 'volume' or
					//     'diameter' fields, then check other size fields
				$mapped_as_no_waste=FALSE;
				}
			}
		}

	$form_state['values']['field_cleaned_by_mapper'][0]['value']=
							(int)($cleaned_by_mapper && $mapped_as_no_waste);

		/*********************/
		/*****           *****/
		/***** Save node *****/
		/*****           *****/
		/*********************/

	$node=_ldiw_api_save_node($node,$form_state,$file_fids);

		/************************************************/
		/*****                                      *****/
		/***** Re-map as empty if cleaned_by_mapper *****/
		/*****                                      *****/
		/************************************************/

	if ($cleaned_by_mapper && !$mapped_as_no_waste) {
		$coords=array(null,null);
		list($node,$form_state)=ldiw_waste_map_prepare_adding_waste_point(
															$coords,$id);
		$form_state['values']['field_cleaned_by_mapper'][0]['value']=1;

		foreach ($server_specific_fields as $key => $info) {
			$value=($key == 'volume' || $key == 'diameter') ? 0 : null;
						//!!! If there are no server-specific 'volume' or
						//   'diameter' fields, then set other size fields
			_ldiw_api_set_server_specific_field($form_state,$info,$value);
			}

		$node=_ldiw_api_save_node($node,$form_state,array());
		}

		/******************************/
		/*****                    *****/
		/***** Build return value *****/
		/*****                    *****/
		/******************************/

	$coords=geoclustering_extract_coords_from_node($node,'field_coords');
	$wp=array('id' => '' . $node->nid,
			'lon' => $coords[0],
			'lat' => $coords[1],
			'cleaned_by_mapper' =>
						(int)$node->field_cleaned_by_mapper[0]['value'],
			);

	if (!empty($node->field_photos_id_width_height[0]['value'])) {
		$wp['photos']=$node->field_photos_id_width_height[0]['value'];
		}

	foreach ($server_specific_fields as $key => $info) {
		if ($info[0] != 'body') {
			if (!isset($node->{$info[0]}[0]['value'])) {
				continue;
				}
			$value=$node->{$info[0]}[0]['value'];
			}
		else {
			if (!isset($node->{$info[0]})) {
				continue;
				}
			$value=$node->{$info[0]};
			}

		if ($info[1]['type'] == 'text') {
			if ($value === '') {
				continue;
				}
			}
		else {
			$value=0 + $value;
			}
		$wp[$key]=$value;
		}

	foreach (variable_get('ldiw_waste_map_composition_fields',array())
													as $key => $info) {
		$dest_key=preg_replace('/^field_(..*)$/','$1',$key);
		if (isset($node->{$key}[0]['value'])) {
			$wp[$dest_key]=0 + $node->{$key}[0]['value'];
			}
		}

	return array('wp' => $wp);
	}

function _ldiw_api_create()
{
	return _ldiw_api_create_update(func_get_args());
	}

function _ldiw_api_update()
{
	$args=func_get_args();
	$id=array_pop($args);
	return _ldiw_api_create_update($args,$id);
	}

function _ldiw_api_retrieve($id,$max_width,$language_code)
{
	_ldiw_api_set_language($language_code);

	$attrs=array('id' => $id);
	$photos=array();

	$cluster_info=geoclustering_get_cluster_info('ldiw_waste_map',$id);
	if ($cluster_info) {
		foreach ($cluster_info[1] as $key => $value) {
			$attrs[preg_replace('/^field_(..*)$/','$1',$key)]=$value;
			}
		$attrs['nr_of_nodes']=$cluster_info[0];
		}
	else {
		$node=node_load($id);

		if (!$node || $node->type != 'waste_point') {
			throw new ServicesException("No node/cluster with ID '$id'",404);
			}

		$photos=ldiw_waste_map_list_photos($node);

		foreach (content_fields(NULL,'waste_point') as $key => $field) {
			if (!empty($node->{$key}[0]['value'])) {
				$attrs[preg_replace('/^field_(..*)$/','$1',$key)]=
												$node->{$key}[0]['value'];
				}
			}

		if (!empty($node->body)) {
			$attrs['description']=$node->body;
			}
		}

	require_once(dirname(__FILE__) . '/waste_point_html.inc');
	return _waste_point_html($attrs,$photos,$max_width);
	}
