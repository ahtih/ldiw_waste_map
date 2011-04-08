<?php

/**
 * Implementation of hook_openlayers_styles().
 */
function ldiw_waste_map_features_openlayers_styles() {
  $export = array();
  $openlayers_styles = new stdClass;
  $openlayers_styles->disabled = FALSE; /* Edit this to true to make a default openlayers_styles disabled initially */
  $openlayers_styles->api_version = 1;
  $openlayers_styles->name = 'waste_point_highlight_style';
  $openlayers_styles->title = 'Waste point highlight style';
  $openlayers_styles->description = 'Waste point highlight style';
  $openlayers_styles->data = array(
    'externalGraphic' => array(
      'plugin' => 'ldiw_waste_map_point_style_plugin',
    ),
    'pointRadius' => array(
      'plugin' => 'ldiw_waste_map_point_style_plugin',
    ),
    'fillColor' => array(
      'plugin' => 'ldiw_waste_map_point_style_plugin',
    ),
    'strokeColor' => '#000000',
    'strokeWidth' => 1,
    'fillOpacity' => 1,
    'strokeOpacity' => 0.8,
    'strokeLinecap' => 'round',
    'strokeDashstyle' => 'solid',
    'graphicOpacity' => 1,
    'graphicZIndex' => 1,
    'backgroundGraphic' => '/sites/all/modules/ldiw_waste_map/img/selected-marker.png',
    'backgroundWidth' => array(
      'plugin' => 'ldiw_waste_map_point_style_plugin',
    ),
    'backgroundHeight' => array(
      'plugin' => 'ldiw_waste_map_point_style_plugin',
    ),
    'backgroundXOffset' => array(
      'plugin' => 'ldiw_waste_map_point_style_plugin',
    ),
    'backgroundYOffset' => array(
      'plugin' => 'ldiw_waste_map_point_style_plugin',
    ),
    'backgroundGraphicZIndex' => 0,
    'labelAlign' => 'cm',
  );

  $export['waste_point_highlight_style'] = $openlayers_styles;
  $openlayers_styles = new stdClass;
  $openlayers_styles->disabled = FALSE; /* Edit this to true to make a default openlayers_styles disabled initially */
  $openlayers_styles->api_version = 1;
  $openlayers_styles->name = 'waste_point_style';
  $openlayers_styles->title = 'Waste point style';
  $openlayers_styles->description = 'Waste point style';
  $openlayers_styles->data = array(
    'externalGraphic' => array(
      'plugin' => 'ldiw_waste_map_point_style_plugin',
    ),
    'pointRadius' => array(
      'plugin' => 'ldiw_waste_map_point_style_plugin',
    ),
    'fillColor' => array(
      'plugin' => 'ldiw_waste_map_point_style_plugin',
    ),
    'fillOpacity' => 1,
    'strokeColor' => '#000000',
    'strokeWidth' => 1,
    'strokeOpacity' => 0.8,
    'strokeLinecap' => 'round',
    'strokeDashstyle' => 'solid',
    'graphicOpacity' => 1,
    'labelAlign' => 'cm',
  );

  $export['waste_point_style'] = $openlayers_styles;
  return $export;
}
