<?php
// $Id

/**
 * WFS BBOX Vector Layer Type class
 */
class ldiw_waste_map_layer_type_wfs extends openlayers_layer_type {
  function __construct($layer = array(), $map = array()) {
    parent::__construct($layer, $map);
    if (isset($this->data)) {
      $this->data += $this->options_init();
    }
    else {
      $this->data = $this->options_init();
    }
  }

  /**
   * Provide initial values for options.
   */
	function options_init()
		{
			global $base_url;
			return array(
					'base_url' => $base_url,
					'layer_type' => 'ldiw_waste_map_wfs',
					'layer_handler' => 'ldiw_waste_map_wfs',
					'projection' => array('4326', '900913'),
					'baselayer' => FALSE,
					'typeName' => '',
					'formatOptions' => array(
							'extractStyles' => TRUE,
							'extractAttributes' => TRUE,
							),
					);
			}

  /**
   * Options form which generates layers
   */
  function options_form() {
    return array(
      'url' => array(
        '#type' => 'textfield',
        '#title' => t('WFS URL'),
        '#description' => t('WFS endpoint URL, relative to Drupal root.'),
        '#maxlength' => 1024,
        '#default_value' => isset($this->data['url']) ?
												$this->data['url'] : ''
      ),
      'typeName' => array(
        '#type' => 'textfield',
        '#title' => t('Type Name'),
        '#description' => t('The typename of the features requested.
          In the case of Drupal WFS views, this is the view name.'),
        '#maxlength' => 100,
        '#default_value' => isset($this->data['typeName']) ?
          $this->data['typeName'] : ''
      ),
      'geometryName' => array(
        '#type' => 'textfield',
        '#title' => t('Geometry Name'),
        '#description' => t('The name of the geometry field in the GML
        returned from the WFS layer. For Drupal, this is geometry'),
        '#maxlength' => 100,
        '#default_value' => isset($this->data['geometryName']) ?
          $this->data['geometryName'] : 'geometry'
      ),
      'layer_type' => array(
        '#type' => 'hidden',
        '#value' => 'ldiw_waste_map_layer_type_wfs'
      ),
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module','ldiw_waste_map')
													. '/wfs_layer_type.js');
    return $this->options;
  }
}
