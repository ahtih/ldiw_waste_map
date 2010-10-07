<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function ldiw_waste_map_features_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "openlayers" && $api == "openlayers_layers") {
    return array("version" => 1);
  }
  elseif ($module == "openlayers" && $api == "openlayers_presets") {
    return array("version" => 1);
  }
  elseif ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
 */
function ldiw_waste_map_features_node_info() {
  $items = array(
    'waste_point' => array(
      'name' => t('Waste point'),
      'module' => 'features',
      'description' => t('Waste point'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Description'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function ldiw_waste_map_features_views_api() {
  return array(
    'api' => '2',
  );
}
