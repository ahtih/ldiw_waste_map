<?php
// $Id

/**
 * CSV BBOX Vector Layer Type class
 */
class ldiw_waste_map_layer_type_csv extends openlayers_layer_type {
	function __construct($layer=array(),$map=array()) {
		parent::__construct($layer,$map);
		if (isset($this->data)) {
			$this->data+=$this->options_init();
			}
		else {
			$this->data=$this->options_init();
			}
		}

	function options_init()
		{
			return array(
				'base_url' => substr(url('.',array('absolute'=>TRUE)),0,-1),
				'layer_type' => 'ldiw_waste_map_csv',
				'layer_handler' => 'ldiw_waste_map_csv',
				'projection' => array('4326','900913'),
				'baselayer' => FALSE,
				);
			}

	function options_form() {
		return array(
			'url' => array(
				'#type' => 'textfield',
				'#title' => t('CSV URL'),
				'#description' => t('CSV ?BBOX=... endpoint URL, relative to Drupal root.'),
				'#maxlength' => 1024,
				'#default_value' => isset($this->data['url']) ?
												$this->data['url'] : '',
				),
			'layer_type' => array(
				'#type' => 'hidden',
				'#value' => 'ldiw_waste_map_layer_type_csv',
				),
			);
		}

	function render(&$map) {
		drupal_add_js(drupal_get_path('module','ldiw_waste_map') .
													'/csv_layer_type.js');
		return $this->options;
		}
	}
