<?php

/**
 * Implementation of hook_strongarm().
 */
function ldiw_waste_map_features_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_pattern_waste_point';
  $strongarm->value = 'WP';

  $export['ant_pattern_waste_point'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_php_waste_point';
  $strongarm->value = 0;

  $export['ant_php_waste_point'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_waste_point';
  $strongarm->value = '1';

  $export['ant_waste_point'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_geo_area';
  $strongarm->value = 0;

  $export['comment_anonymous_geo_area'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_geo_hierarchy_level';
  $strongarm->value = 0;

  $export['comment_anonymous_geo_hierarchy_level'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_waste_point';
  $strongarm->value = 0;

  $export['comment_anonymous_waste_point'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_controls_geo_area';
  $strongarm->value = '3';

  $export['comment_controls_geo_area'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_controls_geo_hierarchy_level';
  $strongarm->value = '3';

  $export['comment_controls_geo_hierarchy_level'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_controls_waste_point';
  $strongarm->value = '3';

  $export['comment_controls_waste_point'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_geo_area';
  $strongarm->value = '4';

  $export['comment_default_mode_geo_area'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_geo_hierarchy_level';
  $strongarm->value = '4';

  $export['comment_default_mode_geo_hierarchy_level'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_waste_point';
  $strongarm->value = '4';

  $export['comment_default_mode_waste_point'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_geo_area';
  $strongarm->value = '1';

  $export['comment_default_order_geo_area'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_geo_hierarchy_level';
  $strongarm->value = '1';

  $export['comment_default_order_geo_hierarchy_level'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_waste_point';
  $strongarm->value = '1';

  $export['comment_default_order_waste_point'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_geo_area';
  $strongarm->value = '50';

  $export['comment_default_per_page_geo_area'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_geo_hierarchy_level';
  $strongarm->value = '50';

  $export['comment_default_per_page_geo_hierarchy_level'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_waste_point';
  $strongarm->value = '50';

  $export['comment_default_per_page_waste_point'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_geo_area';
  $strongarm->value = '0';

  $export['comment_form_location_geo_area'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_geo_hierarchy_level';
  $strongarm->value = '0';

  $export['comment_form_location_geo_hierarchy_level'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_waste_point';
  $strongarm->value = '0';

  $export['comment_form_location_waste_point'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_geo_area';
  $strongarm->value = '0';

  $export['comment_geo_area'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_geo_hierarchy_level';
  $strongarm->value = '0';

  $export['comment_geo_hierarchy_level'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_geo_area';
  $strongarm->value = '1';

  $export['comment_preview_geo_area'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_geo_hierarchy_level';
  $strongarm->value = '1';

  $export['comment_preview_geo_hierarchy_level'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_waste_point';
  $strongarm->value = '1';

  $export['comment_preview_waste_point'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_geo_area';
  $strongarm->value = '1';

  $export['comment_subject_field_geo_area'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_geo_hierarchy_level';
  $strongarm->value = '1';

  $export['comment_subject_field_geo_hierarchy_level'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_waste_point';
  $strongarm->value = '1';

  $export['comment_subject_field_waste_point'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_waste_point';
  $strongarm->value = '2';

  $export['comment_waste_point'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_geo_area';
  $strongarm->value = array(
    'title' => '-5',
    'revision_information' => '-3',
    'author' => '-2',
    'options' => '-1',
    'comment_settings' => '0',
    'menu' => '-4',
  );

  $export['content_extra_weights_geo_area'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_geo_hierarchy_level';
  $strongarm->value = array(
    'title' => '-5',
    'revision_information' => '20',
    'author' => '20',
    'options' => '25',
    'comment_settings' => '30',
    'menu' => '-2',
  );

  $export['content_extra_weights_geo_hierarchy_level'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_waste_point';
  $strongarm->value = array(
    'title' => '-5',
    'body_field' => '4',
    'revision_information' => '-3',
    'author' => '-2',
    'options' => '-1',
    'comment_settings' => '0',
    'menu' => '-4',
  );

  $export['content_extra_weights_waste_point'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_geo_area';
  $strongarm->value = '0';

  $export['language_content_type_geo_area'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_geo_hierarchy_level';
  $strongarm->value = '0';

  $export['language_content_type_geo_hierarchy_level'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_geo_area';
  $strongarm->value = array(
    0 => 'status',
  );

  $export['node_options_geo_area'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_geo_hierarchy_level';
  $strongarm->value = array(
    0 => 'status',
  );

  $export['node_options_geo_hierarchy_level'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_waste_point';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
    2 => 'revision',
  );

  $export['node_options_waste_point'] = $strongarm;
  return $export;
}
