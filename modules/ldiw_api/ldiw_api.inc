<?php
// $Id

function _ldiw_api_get_server_specific_fields()
{
	$data=array();
	$fields_to_omit=explode(' ',variable_get(
						'ldiw_waste_map_photo_field_names',
						LDIW_WASTE_MAP_DEFAULT_PHOTO_FIELDS));
	$fields_to_omit[]='field_geo_areas_json';

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
				$entry['label']=$field['widget']['label'];	//!!! run through t()?
				}

			if (!empty($field['widget']['description'])) {
				$entry['edit_instructions']=$field['widget']['description'];	//!!! run through t()?
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

function _ldiw_api_get_photo_upload_fields()
{
	$fieldnames=explode(' ',variable_get(
						'ldiw_waste_map_photo_field_names',
						LDIW_WASTE_MAP_DEFAULT_PHOTO_FIELDS));
	$data=array();
	foreach ($fieldnames as $fieldname) {
		$fieldinfo=content_fields($fieldname,'waste_point');
		if (!empty($fieldinfo) && $fieldinfo['type'] == 'filefield') {
			for ($i=0;$i < max(1,$fieldinfo['multiple']);$i++) {
				$data[]=array($fieldname,$i);
				}
			}
		}

	return $data;
	}

function ldiw_api_get_api_base_url()
{
	//!!! remove hardcoding of this data
	print json_encode(array(
			'api_base_url' => 'http://api.letsdoitworld.org/?q=api',
			'safe_bbox' => '-180,-90,180,90',
			));
	}

/***************************************************************************/
/********************                                   ********************/
/******************** ldiw_api_waste_point_extra_fields ********************/
/********************                                   ********************/
/***************************************************************************/

function _ldiw_api_waste_point_extra_fields()
{
	$retval=array();

		//!!! Add language_code parameter

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
				throw new ServicesException("Invalid session cookie",401);
				}
			}
		}

	$coords=array_splice($args,0,2);

	if ($id === FALSE && isset($coords[0]) && isset($coords[1])) {
		$db_info=content_database_info(
							content_fields('field_coords','waste_point'));
		$geo_handler=geo_load(array('table_name' => $db_info['table']));

		$distance_threshold_meters=50;
		$earth_circumference_meters=40030081;
		$lat_tolerance=360 * $distance_threshold_meters /
											$earth_circumference_meters;
		$lon_tolerance=$lat_tolerance / max(0.001,cos(deg2rad($coords[1])));

		$bbox_sql=geoclustering_get_bbox_sql($geo_handler,
				array(	$coords[0]-$lon_tolerance,$coords[1]-$lat_tolerance,
						$coords[0]+$lon_tolerance,$coords[1]+$lat_tolerance));

		$distance_query=$geo_handler->distance($geo_handler,
									"POINT(${coords[0]} ${coords[1]})");
		$query="SELECT nid FROM {" . $db_info['table'] . "} " .
						"WHERE $distance_query < %f AND ${bbox_sql[0]} " .
						"ORDER BY $distance_query DESC LIMIT 1";
		$row=db_fetch_array(db_query($query,array_merge(
						array($distance_threshold_meters),$bbox_sql[1])));
		if ($row) {
			$id=$row['nid'];
			$coords=array(NULL,NULL);
			}
		}

	$node=($id !== FALSE) ? @node_load($id) :
									(object)array('type' => 'waste_point');
	$node->uid=$user->uid;
	$node->name=$user->name;

	$form_state=array();
	$form_state['values']['op']=t('Save');

		/***********************/
		/*****             *****/
		/***** Set lon/lat *****/
		/*****             *****/
		/***********************/

	if ($id !== FALSE) {
		$prev_coords=geoclustering_extract_coords_from_node(
													$node,'field_coords');
		if (!isset($coords[0])) {
			$coords[0]=$prev_coords[0];
			}
		if (!isset($coords[1])) {
			$coords[1]=$prev_coords[1];
			}

		if ($coords === $prev_coords) {
			$coords=FALSE;
			}
		}

	if (!empty($coords)) {
		if (!isset($coords[0]) || !isset($coords[1])) {
			throw new ServicesException("Missing required lon/lat fields",400);
			}
		$form_state['values']['field_coords'][0]['geo']=
							array('lon' => $coords[0],'lat' => $coords[1]);
		}

	$client_id=array_shift($args);
	//!!! Store client_id field

		/**********************/
		/*****            *****/
		/***** Set photos *****/
		/*****            *****/
		/**********************/

	$photo_fields=_ldiw_api_get_photo_upload_fields();

	$file_fids=array();
	foreach ($photo_fields as $idx => $photo_field) {
		$photo_param=array_shift($args);
		if (!$photo_param) {
			continue;
			}
		if (is_object($photo_param)) {
			$fname=$photo_param->tmp_name;
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

	$server_specific_fields=_ldiw_api_get_server_specific_fields();
	if ($args !== array_fill(0,count($args),null)) {
		foreach ($server_specific_fields as $key => $info) {
			$value=array_shift($args);
			if ($info[1]['type'] == 'text' && !isset($value)) {
				$value='';
				}
			if ($info[0] == 'body' || $info[0] == 'composition') {
				$form_state['values'][$info[0]]=$value;
				}
			else {
				$form_state['values'][$info[0]][0]['value']=$value;
				}
			}
		}

		/*********************/
		/*****           *****/
		/***** Save node *****/
		/*****           *****/
		/*********************/

	if (function_exists('_element_info')) {	// Workaround for Geo bug http://drupal.org/node/1059916
		module_implements('elements',FALSE,TRUE);
		_element_info('',TRUE);
		}

	$prev_vid=isset($node->vid) ? $node->vid : null;
	module_load_include('inc','node','node.pages');

	@drupal_execute('waste_point_node_form',$form_state,$node);

	foreach ($file_fids as $fid) {
		field_file_load($fid,TRUE);	// Reload file cache; otherwise file is not found if "FileField Paths" module is used
		}

	$success=FALSE;
	if (isset($form_state['nid'])) {
		$node=@node_load(array('nid' => $form_state['nid']));	// This argument style does not use node cache
		$success=($id === FALSE || $node->vid != $prev_vid);
		}

		/****************************/
		/*****                  *****/
		/***** Check for errors *****/
		/*****                  *****/
		/****************************/

	$messages=drupal_get_messages();
	if (!$success) {
		$error="Unknown error";
		if (!empty($messages['error'])) {
			$error=strip_tags(implode(';',$messages['error']));
			}
		throw new ServicesException($error,400);
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
	return _waste_point_html($attrs,$photos,$max_width,$language_code);
	}
