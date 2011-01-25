<?php
// $Id$

class ldiw_waste_map_behavior_automaticpopup extends openlayers_behavior
{
	function options_form($defaults)
	{
		return array(
			'features_layer' => array(
				'#type' => 'select',
				'#options' => $this->map['layers'],
				'#description' => t('Vector layer containing features ' .
											'to be considered for popup.'),
				'#default_value' => isset($defaults['features_layer']) ?
										$defaults['features_layer'] : NULL
				),
			'required_feature_attribute' => array(
				'#type' => 'textfield',
				'#description' => t('Name of non-empty attribute that ' .
										'a feature must have in order ' .
										'to be considered for popup.'),
				'#default_value' =>
							isset($defaults['required_feature_attribute']) ?
							$defaults['required_feature_attribute'] : NULL
				),
			);
		}
	function render(&$map)
	{
		drupal_add_js(drupal_get_path('module','ldiw_waste_map') .
							'/ldiw_waste_map_behavior_automaticpopup.js');
		return $this->options;
		}
	}
