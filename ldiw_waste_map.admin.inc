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

	$form['recalculate_geo_areas']=array(
				'#type' => 'submit',
				'#value' => t("Recalculate Geographic Areas data " .
												"for Waste point nodes"),
				'#submit' => array('ldiw_waste_map_recalculate_geo_areas'),
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

	$recalculate_geo_areas=drupal_render($form['recalculate_geo_areas']);

	return $recalculate_geo_areas .
			'<h3>' . t('List of float-valued Waste point fields') . '</h3>' .
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
				'ldiw_waste_map_single_composition_value');

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
