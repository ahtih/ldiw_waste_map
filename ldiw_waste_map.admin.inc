<?php
// $Id$

function ldiw_waste_map_admin_settings()
{
	$form=array();

	//!!! Display table caption/instructions

	$form['composition']['#tree']=TRUE;

	$composition_defaults=
				variable_get('ldiw_waste_map_composition_fields',array());

	foreach (content_fields(NULL,'waste_point') as $fieldname => $field) {
		if ($field['type_name'] == 'waste_point' &&
									$field['type'] == 'number_float' &&
									$fieldname != 'field_volume') {
			$field_form=array(
				'color' => array(
						'#type' => (module_exists('colorpicker') ?
										'colorpicker_' : '') . 'textfield',
						'#default_value' => '#000000',
						),
				'text' => array(
						'#type' => 'textfield',
						'#size' => 12,
						),
				'text_solo' => array(
						'#type' => 'textfield',
						'#size' => 12,
						),
				);

			foreach ($field_form as $key => $info) {
				if (isset($composition_defaults[$fieldname][$key])) {
					$field_form[$key]['#default_value']=
									$composition_defaults[$fieldname][$key];
					}
				}

			$form['composition'][$fieldname]=$field_form;
			}
		}

	$form['ldiw_waste_map_single_composition_value']=array(
				'#type' => 'checkbox',
				'#title' => t('For each Waste point, select only the main ' .
						'composition type, instead of percentages of ' .
						'all composition types'),
				'#default_value' => variable_get(
								'ldiw_waste_map_single_composition_value',
								FALSE),
				);

	$form['ldiw_waste_map_photo_field_names']=array(
				'#type' => 'textfield',
				'#title' => t('Space-separated list of CCK Field names ' .
										'containing Waste Point photos'),
				'#default_value' => variable_get(
								'ldiw_waste_map_photo_field_names',
								LDIW_WASTE_MAP_DEFAULT_PHOTO_FIELDS),
				'#size' => 32,
				'#maxlength' => 1000,
				);

	$form['ldiw_waste_map_minimum_initial_zoom']=array(
				'#type' => 'textfield',
				'#title' => t('Minimum initial zoom level of Waste Map'),
				'#description' => t('When the user opens Waste Map, the ' .
						'map position and zoom is selected automatically ' .
						'based on GeoIP and number of Waste points nearby. ' .
						'This setting allows you to impose a minimum ' .
						'limit to this automatically selected zoom. ' .
						'0 corresponds to maximally zoomed out map; ' .
						'increasing it progressively zooms in.'),
				'#default_value' => variable_get(
								'ldiw_waste_map_minimum_initial_zoom',
								LDIW_WASTE_MAP_DEFAULT_MINIMUM_INITIAL_ZOOM),
				'#size' => 4,
				'#maxlength' => 4,
				);

	$form=system_settings_form($form);

	unset($form['#theme']);
	$form['#submit']=array('ldiw_waste_map_admin_settings_submit');

	return $form;
	}

/***************************************************************************/
/******************                                       ******************/
/****************** theme_ldiw_waste_map_admin_settings() ******************/
/******************                                       ******************/
/***************************************************************************/

function theme_ldiw_waste_map_admin_settings($form)
{
	$header=array(t('Waste point field'),t('Marker color'),
						t('Label in popup'),t('Solo label in popup'));
	$rows=array();
	foreach (element_children($form['composition']) as $key) {
		if (is_array($form['composition'][$key])) {
			$row=array($key);
			foreach (element_children($form['composition'][$key]) as $col_key) {
				$row[]=drupal_render($form['composition'][$key][$col_key]);
				}
			$rows[]=$row;
			}
		}

	return '<h3>' . t('List of float-valued Waste point fields') . '</h3>' .
			t('For any fields holding waste composition information, ' .
				'specify a label text and marker color; optionally Solo ' .
				'label could be configured too, this is used as a label ' .
				'if this is the sole composition type for the waste point.').
			theme('table',$header,$rows) .
			drupal_render($form);
	}

/***************************************************************************/
/*****************                                        ******************/
/***************** ldiw_waste_map_admin_settings_submit() ******************/
/*****************                                        ******************/
/***************************************************************************/

function ldiw_waste_map_admin_settings_submit($form,&$form_state)
{
	$vars=array('ldiw_waste_map_photo_field_names',
				'ldiw_waste_map_single_composition_value',
				'ldiw_waste_map_minimum_initial_zoom');

	if (isset($form_state['values']['op'])) {
		if ($form_state['values']['op'] == t('Reset to defaults')) {
			foreach ($vars as $varname) {
				variable_del($varname);
				}
			drupal_set_message(t('The configuration options have been ' .
										'reset to their default values.'));
			return;
			}
		}

	foreach ($vars as $varname) {
		variable_set($varname,$form_state['values'][$varname]);
		}

	$composition=$form_state['values']['composition'];
	foreach ($composition as $fieldname => $info) {
		if (empty($info['text'])) {
			unset($composition[$fieldname]);
			}
		}

	variable_set('ldiw_waste_map_composition_fields',$composition);
	ldiw_waste_map_locale_refresh();

	cache_clear_all('services:','cache',TRUE);

	drupal_set_message(t('The configuration options have been saved.'));
	}

/***************************************************************************/
/*************                                                **************/
/************* ldiw_waste_map_recalculate_geo_areas_process() **************/
/*************                                                **************/
/***************************************************************************/

function ldiw_waste_map_recalculate_geo_areas_process(&$context)
{
	if (empty($context['sandbox'])) {
		$context['sandbox']['nodes_processed']=0;
		$context['sandbox']['nodes_modified']=0;
		$context['sandbox']['current_nid']=-1;
		$context['sandbox']['nr_of_nodes']=db_result(db_query(
							"SELECT COUNT(DISTINCT nid) FROM {node}"));
		}

	$result=db_query_range("SELECT nid FROM {node} " .
								"WHERE type='waste_point' AND nid > %d " .
								"ORDER BY nid",
							$context['sandbox']['current_nid'],0,30);
	$prev_progress=$context['sandbox']['nodes_processed'];
	while ($row=db_fetch_array($result)) {
		if ($context['sandbox']['current_nid'] === $row['nid']) {
			continue;
			}
		$node=node_load($row['nid'],NULL,TRUE);
		if ($node) {
			$coords=geoclustering_extract_coords_from_node(
													$node,'field_coords');
			if (_ldiw_waste_map_set_geo_areas($coords,$node)) {

				// Workaround for http://drupal.org/node/667034
				$node->field_coords[0]['geo']=array(
								'lon' => $coords[0],'lat' => $coords[1]);

				$node_changed=$node->changed;
				node_save($node);
				db_query("UPDATE {node} SET changed='%s' WHERE nid=%d",
												$node_changed,$node->nid);
				$context['sandbox']['nodes_modified']++;
				}
			}

		$context['sandbox']['nodes_processed']++;
		$context['sandbox']['current_nid']=$row['nid'];
		}

	if ($context['sandbox']['nodes_processed'] != $prev_progress) {
		$context['finished']=$context['sandbox']['nodes_processed'] /
						max($context['sandbox']['nr_of_nodes'],
								$context['sandbox']['nodes_processed']+1);
		$context['message']=t("Processed @nodes_processed of " .
					"@nr_of_nodes nodes (@nodes_modified nodes modified)",
					array('@nodes_processed' =>
								$context['sandbox']['nodes_processed'],
							'@nr_of_nodes' =>
								$context['sandbox']['nr_of_nodes'],
							'@nodes_modified' =>
								$context['sandbox']['nodes_modified']));
		}
	}

/***************************************************************************/
/*************                                                 *************/
/************* ldiw_waste_map_recalculate_geo_areas_finished() *************/
/*************                                                 *************/
/***************************************************************************/

function ldiw_waste_map_recalculate_geo_areas_finished()
{
	drupal_set_message(t('Done.'));
	}

/***************************************************************************/
/*****************                                        ******************/
/***************** ldiw_waste_map_recalculate_geo_areas() ******************/
/*****************                                        ******************/
/***************************************************************************/

function ldiw_waste_map_recalculate_geo_areas()
{
	$batch = array(
			'title' => t('Recalculating...'),
			'progress_message' => '',
			'operations' => array(array(
					'ldiw_waste_map_recalculate_geo_areas_process',array())),
			'finished' => 'ldiw_waste_map_recalculate_geo_areas_finished',
			'file' => drupal_get_path('module','ldiw_waste_map') .
											'/ldiw_waste_map.admin.inc',
			);
	batch_set($batch);
	}

/***************************************************************************/
/********************                                  *********************/
/******************** ldiw_waste_map_admin_geo_areas() *********************/
/********************                                  *********************/
/***************************************************************************/

function ldiw_waste_map_admin_geo_areas()
{
	$form=array();

	$form['#attributes']['enctype']='multipart/form-data';

	$form['recalculate_geo_areas']=array(
				'#type' => 'submit',
				'#value' => t("Recalculate Geographic Areas fields " .
												"for Waste point nodes"),
				'#submit' => array('ldiw_waste_map_recalculate_geo_areas'),
				);

	$hierarchy_level_options=array();

	$r=db_query("SELECT nid,title FROM {node} " .
							"WHERE type='geo_hierarchy_level' ORDER BY nid");
	while ($row=db_fetch_object($r)) {
		$hierarchy_level_options[$row->nid]=$row->title;
		}

	$form['import']=array(
		'#type' => 'fieldset',
		'#title' => t('Import Geographic Areas from ESRI shapefile'),
		'#tree' => TRUE,
		'file' => array(
				'#type' => 'file',
				'#title' => t('Shapefile .zip'),
				'#description' => t("The shapefile must be a .zip file " .
					"that includes at least a .shp, .dbf and .shx file."),
				),
		'hierarchy_level' => array(
				'#type' => 'select',
				'#title' => t('Hierarchy level of areas in this shapefile'),
				'#description' =>
						t("All areas in imported shapefile must belong " .
							"to the same hierarchy level."),
				'#options' => $hierarchy_level_options,
				'#required' => TRUE,
				),
		'area_name_fieldname' => array(
				'#type' => 'textfield',
				'#title' => t("Name of shapefile attribute storing " .
															"area name"),
				'#description' =>
						t("If you leave this blank, the resulting areas " .
							"will all be named 'Unnamed area'."),
				'#size' => 10,
				'#maxlength' => 100,
				),
		'parentarea_name_fieldname' => array(
				'#type' => 'textfield',
				'#title' => t("Name of shapefile attribute storing " .
														"parent area name"),
				'#description' =>
						t('If you leave this blank, the resulting areas ' .
							'will not have parent areas defined.'),
				'#size' => 10,
				'#maxlength' => 100,
				),
		'character_encoding' => array(
				'#type' => 'textfield',
				'#title' =>
						t('Character encoding used for attribute values'),
				'#description' =>
						t('Shapefile format does not specify a character ' .
							'encoding. Therefore you have to know which ' .
							'encoding your shapefile uses, in order to ' .
							'correctly interpret non-ASCII characters.'),
				'#required' => TRUE,
				'#default_value' => 'Windows-1252',
				'#size' => 15,
				'#maxlength' => 100,
				),
		'submit' => array(
				'#type' => 'submit',
				'#value' => t('Import file'),
				),
		);

	return $form;
	}

/***************************************************************************/
/*****************                                        ******************/
/***************** _ldiw_waste_map_check_shapefile_attr() ******************/
/*****************                                        ******************/
/***************************************************************************/

function _ldiw_waste_map_check_shapefile_attr($table_name,$fieldname)
{
	$fieldname=db_escape_table(preg_replace('/[^a-z0-9_]/','',
										strtolower(trim($fieldname))));
	if ($fieldname && !db_column_exists($table_name,$fieldname)) {
		drupal_set_message(t("Attribute %attr not found in shapefile, " .
				"treating it as blank",array('%attr' => $fieldname)),
				'error');
		$fieldname='';
		}

	return $fieldname;
	}

/***************************************************************************/
/*****************                                         *****************/
/***************** ldiw_waste_map_admin_geo_areas_submit() *****************/
/*****************                                         *****************/
/***************************************************************************/

function ldiw_waste_map_admin_geo_areas_submit($form,&$form_state)
{
	if (!isset($_FILES['files']['tmp_name']['import'])) {
		return;
		}

	if (!file_exists($_FILES['files']['tmp_name']['import'])) {
		drupal_set_message(t("File upload failed, probably due to your " .
				"php.ini settings limiting upload of such large files. " .
				"Check post_max_size and upload_max_filesize in php.ini"),
				'error');
		return;
		}

	$table_name='ldiw_waste_map_import_' . time();

	module_load_include('inc','geo','includes/shp2sql');
	geo_shp2sql($_FILES['files']['tmp_name']['import'],$table_name,TRUE,4326,
					$form_state['values']['import']['character_encoding']);
	$geo=geo_load(array('table_name' => $table_name));

	if (!$geo->name()) {
		return; 	// geo_shp2sql() failed, error message is already set
		}

	drupal_get_messages();	// Clear successful import message

	$fieldname=_ldiw_waste_map_check_shapefile_attr($table_name,
				$form_state['values']['import']['area_name_fieldname']);
	$parent_fieldname=_ldiw_waste_map_check_shapefile_attr($table_name,
				$form_state['values']['import']['parentarea_name_fieldname']);

	$hierarchy_level_node=node_load(
						$form_state['values']['import']['hierarchy_level']);

	$r=db_query("SELECT " .
				($fieldname ? $fieldname : "''") . " AS area," .
				($parent_fieldname ? $parent_fieldname : "''") .
														" AS parentarea," .
				$geo->AsText($geo) . " AS wkt FROM {%s}",
				$table_name);
	$success_count=0;
	$errors=array();
	while ($row=db_fetch_object($r)) {
		if (substr($row->wkt,0,7) == 'POLYGON') {
			$row->wkt='MULTIPOLYGON(' . substr($row->wkt,7) . ')';
			}

		global $user;
		$node=(object)array('type' => 'geo_area');
		$node->uid=$user->uid;
		$node->name=$user->name;

			//!!! Append coordinates to unnamed area title
		$title=empty($row->area) ? 'Unnamed area' : $row->area;

		$node_form_state=array();
		$node_form_state['values']['op']=t('Save');
		$node_form_state['values']['title']=$title;
		$node_form_state['values']['og_description']=$title;

		$node_form_state['values']['field_hierarchy_level'][0]['nid']=
												$hierarchy_level_node->nid;
				//!!! check if input widget is optionwidgets

		if (!empty($row->parentarea) && isset(
					$hierarchy_level_node->field_parent_level[0]['nid'])) {
			$rr=db_query("SELECT nid FROM {node} " .
									"WHERE type='geo_area' AND title='%s'",
									$row->parentarea);
			$parent_nids=array();
			while ($parent_row=db_fetch_object($rr)) {
				$parent_node=node_load($parent_row->nid);
				if (isset($parent_node->field_hierarchy_level[0]['nid']) &&
						$parent_node->field_hierarchy_level[0]['nid'] ==
						$hierarchy_level_node->field_parent_level[0]['nid']) {
					$parent_nids[]=$parent_row->nid;
					}
				}

			if (count($parent_nids) == 1) {
				//!!! check if input widget is autocomplete
				$node_form_state['values']['field_parent'][0]['nid']['nid']=
										'[nid:' . $parent_nids[0] . ']';
				}
			else {
				$errors[]=(empty($parent_nids) ?
							'No parent area ' : 'Multiple parent areas ') .
							$row->parentarea . ' found for area ' .
							$row->area;
				}
			}

		$node_form_state['values']['field_geo'][0]['geo']=$row->wkt;
		module_load_include('inc','node','node.pages');
		module_load_include('inc','node_import','node_import');
		@node_import_drupal_execute('geo_area_node_form',$node_form_state,
																	$node);
		if (isset($node_form_state['nid'])) {
			@node_load(array('nid' => $node_form_state['nid']));	// This argument style clears node cache
			$success_count++;
			}
		else {
			$errors[]='Failed to save node for area ' . $row->area;
			}
		}

	foreach ($errors as $e) {
		drupal_set_message($e,'error');
		}

	if ($success_count || empty($errors)) {
		drupal_set_message("Successfully imported $success_count areas");
		}

	geo_delete($geo);
	db_query("DROP TABLE {" . $table_name . "}");
	}
