<?php

/**
 * Implementation of hook_openlayers_presets().
 */
function ldiw_waste_map_features_openlayers_presets() {
  $export = array();
  $openlayers_presets = new stdClass;
  $openlayers_presets->disabled = FALSE; /* Edit this to true to make a default openlayers_presets disabled initially */
  $openlayers_presets->api_version = 1;
  $openlayers_presets->name = 'waste_map';
  $openlayers_presets->title = 'Waste Map';
  $openlayers_presets->description = 'Waste Map';
  $openlayers_presets->data = array(
    'width' => 'auto',
    'height' => '500px',
    'image_path' => 'http://openlayers.org/api/2.9/img/',
    'css_path' => 'http://openlayers.org/api/2.9/theme/default/style.css',
    'proxy_host' => '',
    'hide_empty_map' => 0,
    'center' => array(
      'initial' => array(
        'centerpoint' => '9.0692138668392, 49.760982892584',
        'zoom' => '4',
      ),
      'restrict' => array(
        'restrictextent' => 0,
        'restrictedExtent' => '',
      ),
    ),
    'behaviors' => array(
      'openlayers_behavior_attribution' => array(),
      'openlayers_behavior_popup' => array(
        'layers' => array(),
      ),
      'openlayers_behavior_keyboarddefaults' => array(),
      'openlayers_behavior_navigation' => array(
        'zoomWheelEnabled' => 1,
      ),
      'openlayers_behavior_panzoombar' => array(),
      'openlayers_behavior_scaleline' => array(),
      'ldiw_waste_map_behavior_addpointcontent' => array(
        'content_type' => 'waste_point',
        'features_layer' => 'waste_map_csv',
      ),
      'ldiw_waste_map_behavior_automaticpopup' => array(
        'features_layer' => 'waste_map_csv',
        'required_feature_attribute' => 'photos',
      ),
    ),
    'default_layer' => 'osm_mapnik',
    'layers' => array(
      'google_normal' => 'google_normal',
      'osm_mapnik' => 'osm_mapnik',
      'waste_map_csv' => 'waste_map_csv',
    ),
    'layer_styles' => array(),
    'layer_activated' => array(
      'waste_map_csv' => 'waste_map_csv',
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

  $export['waste_map'] = $openlayers_presets;
  return $export;
}
