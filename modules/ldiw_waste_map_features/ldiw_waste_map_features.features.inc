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
  elseif ($module == "openlayers" && $api == "openlayers_styles") {
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
    'geo_area' => array(
      'name' => t('Geographic area'),
      'module' => 'features',
      'description' => t('A geographic area (county, municipality etc) belonging to an already-defined <em>Geographic area hierarchy level</em>.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => t('This defines a geographic area (county, municipality etc) belonging to an already-defined <em>Geographic area hierarchy level</em>. If you have not defined any hierarchy levels yet, you should do so before creating a <em>Geographic area</em>.
<p>
After adding/editing Geographic areas, you should perform a
<em>Recalculate Geographic Areas fields for Waste point nodes</em> operation in
<em>LDIW Waste Map settings</em>.'),
    ),
    'geo_hierarchy_level' => array(
      'name' => t('Geographic area hierarchy level'),
      'module' => 'features',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Name'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => t('This is a level in a hierarchy of geographical subdivisions of Waste Map. Three examples of hierarchy levels could be municipality, country, and forestry ranger district. Obviously these are related to each other (each municipality belongs to a country) and these relationships are described by <em>Parent hierarchy level</em> and <em>Display parent name</em> fields. Here is an example of hieararchy levels for United States cleanup:
<ul>
<li>Name: <em>State</em>; Parent hierarchy level: None
<li>Name: <em>County</em>; Parent hierarchy level: <em>State</em>; Display parent name: <em>Yes</em>; Display label: <em>County</em>
<li>Name: <em>Forest Service Region</em>; Parent hierarchy level: None
<li>Name: <em>National Forest</em>; Parent hierarchy level: <em>Forest Service Region</em>
<li>Name: <em>Ranger District</em>; Parent hierarchy level: <em>National Forest</em>; Display parent name: <em>Yes</em>; Display label: <em>Forest Service</em>
</ul>
<p>
After adding/editing hierarchy levels, you should perform a
<em>Recalculate Geographic Areas fields for Waste point nodes</em> operation in
<em>LDIW Waste Map settings</em>.'),
    ),
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
