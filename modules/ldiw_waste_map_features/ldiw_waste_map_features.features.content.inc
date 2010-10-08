<?php

/**
 * Implementation of hook_content_default_fields().
 */
function ldiw_waste_map_features_content_default_fields() {
  $fields = array();

  // Exported field: field_coords
  $fields['waste_point-field_coords'] = array(
    'field_name' => 'field_coords',
    'type_name' => 'waste_point',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'geo',
    'required' => '1',
    'multiple' => '0',
    'module' => 'geo',
    'active' => '1',
    'srid' => 4326,
    'geo_type' => 'point',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'geo' => array(
            'lat' => '',
            'lon' => '',
          ),
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Coordinates',
      'weight' => '1',
      'description' => '',
      'type' => 'geo_latlon',
      'module' => 'geo_field',
    ),
  );

  // Exported field: field_diameter
  $fields['waste_point-field_diameter'] = array(
    'field_name' => 'field_diameter',
    'type_name' => 'waste_point',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'number_integer',
    'required' => '0',
    'multiple' => '0',
    'module' => 'number',
    'active' => '1',
    'prefix' => '',
    'suffix' => 'm',
    'min' => '0',
    'max' => '50',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_diameter][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Diameter',
      'weight' => '2',
      'description' => '',
      'type' => 'number',
      'module' => 'number',
    ),
  );

  // Exported field: field_nr_of_tires
  $fields['waste_point-field_nr_of_tires'] = array(
    'field_name' => 'field_nr_of_tires',
    'type_name' => 'waste_point',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'number_integer',
    'required' => '0',
    'multiple' => '0',
    'module' => 'number',
    'active' => '1',
    'prefix' => '',
    'suffix' => '',
    'min' => '0',
    'max' => '100000',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_nr_of_tires][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Number of tires',
      'weight' => '3',
      'description' => '',
      'type' => 'number',
      'module' => 'number',
    ),
  );

  // Exported field: field_photo
  $fields['waste_point-field_photo'] = array(
    'field_name' => 'field_photo',
    'type_name' => 'waste_point',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '10',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'png gif jpg jpeg',
      'file_path' => '',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'max_resolution' => '1280x1280',
      'min_resolution' => '50x50',
      'alt' => '',
      'custom_alt' => 0,
      'title' => '',
      'custom_title' => 0,
      'title_type' => 'textfield',
      'default_image' => NULL,
      'use_default_image' => 0,
      'label' => 'Photo',
      'weight' => '5',
      'description' => '',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Exported field: field_volume
  $fields['waste_point-field_volume'] = array(
    'field_name' => 'field_volume',
    'type_name' => 'waste_point',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'computed',
    'required' => '0',
    'multiple' => '0',
    'module' => 'computed_field',
    'active' => '1',
    'code' => '$diameter=is_null($node->field_diameter[0][\'value\']) ? 2 : $node->field_diameter[0][\'value\'];
$node_field[0][\'value\'] = max(0.1,min(0.25,$diameter*0.2/5)) * max(0.3,$diameter*$diameter);',
    'display_format' => '$display = $node_field_item[\'value\'];',
    'store' => 1,
    'data_type' => 'float',
    'data_length' => '24',
    'data_not_NULL' => 0,
    'data_default' => '',
    'data_sortable' => 0,
    'widget' => array(
      'default_value' => NULL,
      'default_value_php' => NULL,
      'label' => 'Volume',
      'weight' => '6',
      'description' => 'Volume of waste, in m3',
      'type' => 'computed',
      'module' => 'computed_field',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Coordinates');
  t('Diameter');
  t('Number of tires');
  t('Photo');
  t('Volume');

  return $fields;
}
