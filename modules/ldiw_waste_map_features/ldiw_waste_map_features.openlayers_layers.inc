<?php

/**
 * Implementation of hook_openlayers_layers().
 */
function ldiw_waste_map_features_openlayers_layers() {
  $export = array();
  $openlayers_layers = new stdClass;
  $openlayers_layers->disabled = FALSE; /* Edit this to true to make a default openlayers_layers disabled initially */
  $openlayers_layers->api_version = 1;
  $openlayers_layers->name = 'waste_map_csv';
  $openlayers_layers->title = 'Waste Map CSV';
  $openlayers_layers->description = 'Waste Map using CSV BBOX layer type';
  $openlayers_layers->data = array(
    'url' => 'api/waste_points.csv',
    'layer_type' => 'ldiw_waste_map_layer_type_csv',
  );

  $export['waste_map_csv'] = $openlayers_layers;
  return $export;
}
