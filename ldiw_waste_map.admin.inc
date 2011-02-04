<?php
// $Id$

function ldiw_waste_map_admin_settings()
{
	$form=array();
	$form['composition']['#tree']=TRUE;

	//!!! Display table caption/instructions

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

	$form=system_settings_form($form);

	unset($form['#theme']);
	$form['#submit']=array('ldiw_waste_map_admin_settings_submit');

	return $form;
	}

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

function ldiw_waste_map_admin_settings_submit($form,&$form_state)
{
	$vars=array('ldiw_waste_map_photo_field_names');

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

	drupal_set_message(t('The configuration options have been saved.'));
	}
