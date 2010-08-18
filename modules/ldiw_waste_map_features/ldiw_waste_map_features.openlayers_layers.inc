<?php

/**
 * Implementation of hook_openlayers_layers().
 */
function ldiw_waste_map_features_openlayers_layers() {
  $export = array();
  $openlayers_layers = new stdClass;
  $openlayers_layers->disabled = FALSE; /* Edit this to true to make a default openlayers_layers disabled initially */
  $openlayers_layers->api_version = 1;
  $openlayers_layers->name = 'waste_map_wfs';
  $openlayers_layers->title = 'Waste Map';
  $openlayers_layers->description = 'Waste Map';
  $openlayers_layers->data = array(
    'url' => 'http://127.0.0.1/waste_map_geoclustering.wfs',
    'typeName' => 'waste_map_geoclustering_wfs',
    'geometryName' => 'geometry',
    'layer_type' => 'ldiw_waste_map_layer_type_wfs',
  );

  $export['waste_map_wfs'] = $openlayers_layers;
  return $export;
}
