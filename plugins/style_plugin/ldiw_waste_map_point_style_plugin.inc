<?php
// $Id$

// Define plugin for CTools
$plugin = array(
  'title' => t('Waste point style plugin'),
  'description' => t('Waste point style plugin'),
  'style_plugin' => array(
    'class' => 'openlayers_style_plugin_point_style_plugin',
    'parent' => 'openlayers_style_plugin',
  ),
);

class openlayers_style_plugin_point_style_plugin extends 
  openlayers_style_plugin {

  function get_context_properties() {
    return array(
        'pointRadius' => 'getpointRadius',
		'fillColor' => 'getfillColor',
    );
  }

  function render() {
    drupal_add_js(drupal_get_path('module', 'ldiw_waste_map') .
      '/plugins/style_plugin/ldiw_waste_map_point_style_plugin.js');
  }
}
