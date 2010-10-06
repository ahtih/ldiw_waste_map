<?php

/**
 * Implementation of hook_openlayers_presets().
 */
function ldiw_waste_map_features_openlayers_presets() {
  $export = array();
  $openlayers_presets = new stdClass;
  $openlayers_presets->disabled = FALSE; /* Edit this to true to make a default openlayers_presets disabled initially */
  $openlayers_presets->api_version = 1;
  $openlayers_presets->name = 'waste_map_wfs';
  $openlayers_presets->title = 'Waste Map';
  $openlayers_presets->description = 'Waste Map';
  $openlayers_presets->data = array(
    'width' => 'auto',
    'height' => '800px',
    'image_path' => 'http://openlayers.org/api/img/',
    'css_path' => 'http://openlayers.org/api/theme/default/style.css',
    'proxy_host' => '',
    'hide_empty_map' => 0,
    'center' => array(
      'initial' => array(
        'centerpoint' => '25.263061522439, 58.645581224282',
        'zoom' => '8',
      ),
      'restrict' => array(
        'restrictextent' => 0,
        'restrictedExtent' => '',
      ),
    ),
    'behaviors' => array(
      'ldiw_waste_map_behavior_addpointcontent' => array(
        'content_type' => 'waste_point',
        'features_layer' => 'waste_map_wfs',
      ),
      'openlayers_behavior_attribution' => array(),
      'openlayers_behavior_popup' => array(
        'layers' => array(),
      ),
      'openlayers_behavior_keyboarddefaults' => array(),
      'openlayers_behavior_layerswitcher' => array(
        'ascending' => 1,
      ),
      'openlayers_behavior_navigation' => array(
        'zoomWheelEnabled' => 1,
      ),
      'openlayers_behavior_panzoombar' => array(),
      'openlayers_behavior_scaleline' => array(),
    ),
    'default_layer' => 'google_normal',
    'layers' => array(
      'google_normal' => 'google_normal',
      'waste_map_wfs' => 'waste_map_wfs',
    ),
    'layer_styles' => array(),
    'layer_activated' => array(
      'waste_map_wfs' => 'waste_map_wfs',
    ),
    'layer_switcher' => array(),
    'projection' => '900913',
    'displayProjection' => '4326',
    'styles' => array(
      'default' => 'waste_point_style',
      'select' => 'waste_point_highlight_style',
      'temporary' => 'default',
    ),
  );

  $export['waste_map_wfs'] = $openlayers_presets;
  return $export;
}
