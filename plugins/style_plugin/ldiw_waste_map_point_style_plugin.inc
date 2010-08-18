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

  function options_init() {
    return array(
      'context_properties' => array(
        'pointRadius' => 'getpointRadius',
		'fillColor' => 'getfillColor',
      ),
      'context_object' => 'ldiw_waste_map_context',
    );
  }

  function render(&$style) {
    // For context styling, we want to replace the
    // style properties with their context value
    foreach ($this->options['context_properties'] as $prop => $callback) {
      $style->data[$prop] = '${' . $callback . '}';
    }
    
    // Enable context and tell context about our plugin
    $style->data['context_object'] = $this->options['context_object'];
    $style->data['context_plugin'] = 'openlayers_style_plugin_point_style_plugin';
    
    // Add JS
    drupal_add_js(drupal_get_path('module', 'ldiw_waste_map') .
      '/plugins/style_plugin/ldiw_waste_map_point_style_plugin.js');
  }
}
