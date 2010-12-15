<?php

/**
 * Implementation of hook_content_default_fields().
 */
function ldiw_waste_map_features_content_default_fields() {
  $fields = array();

  // Exported field: field_composition_biodegradable
  $fields['waste_point-field_composition_biodegradable'] = array(
    'field_name' => 'field_composition_biodegradable',
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
    'type' => 'number_float',
    'required' => '0',
    'multiple' => '0',
    'module' => 'number',
    'active' => '1',
    'prefix' => '',
    'suffix' => '%',
    'min' => '0',
    'max' => '100',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_composition_biodegradable][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Composition: biodegradable',
      'weight' => '7',
      'description' => 'Percentage (in volume) of soil, biomass, sand etc',
      'type' => 'number',
      'module' => 'number',
    ),
  );

  // Exported field: field_composition_construction
  $fields['waste_point-field_composition_construction'] = array(
    'field_name' => 'field_composition_construction',
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
    'type' => 'number_float',
    'required' => '0',
    'multiple' => '0',
    'module' => 'number',
    'active' => '1',
    'prefix' => '',
    'suffix' => '%',
    'min' => '0',
    'max' => '100',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_composition_construction][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Composition: construction',
      'weight' => '8',
      'description' => 'Percentage (in volume) of construction waste',
      'type' => 'number',
      'module' => 'number',
    ),
  );

  // Exported field: field_composition_dangerous
  $fields['waste_point-field_composition_dangerous'] = array(
    'field_name' => 'field_composition_dangerous',
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
    'type' => 'number_float',
    'required' => '0',
    'multiple' => '0',
    'module' => 'number',
    'active' => '1',
    'prefix' => '',
    'suffix' => '%',
    'min' => '0',
    'max' => '100',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_composition_dangerous][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Composition: dangerous waste and tires',
      'weight' => '6',
      'description' => 'Percentage (in volume) of dangerous waste and tires',
      'type' => 'number',
      'module' => 'number',
    ),
  );

  // Exported field: field_composition_large
  $fields['waste_point-field_composition_large'] = array(
    'field_name' => 'field_composition_large',
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
    'type' => 'number_float',
    'required' => '0',
    'multiple' => '0',
    'module' => 'number',
    'active' => '1',
    'prefix' => '',
    'suffix' => '%',
    'min' => '0',
    'max' => '100',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_composition_large][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Composition: large',
      'weight' => '5',
      'description' => 'Percentage (in volume) of large objects like furniture',
      'type' => 'number',
      'module' => 'number',
    ),
  );

  // Exported field: field_composition_other
  $fields['waste_point-field_composition_other'] = array(
    'field_name' => 'field_composition_other',
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
    'type' => 'number_float',
    'required' => '0',
    'multiple' => '0',
    'module' => 'number',
    'active' => '1',
    'prefix' => '',
    'suffix' => '%',
    'min' => '0',
    'max' => '100',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_composition_other][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Composition: other',
      'weight' => '9',
      'description' => 'Percentage (in volume) of other waste',
      'type' => 'number',
      'module' => 'number',
    ),
  );

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
    'multiple' => '0',
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
      'max_resolution' => '0',
      'min_resolution' => '0',
      'alt' => '',
      'custom_alt' => 0,
      'title' => '',
      'custom_title' => 0,
      'title_type' => 'textfield',
      'default_image' => NULL,
      'use_default_image' => 0,
      'label' => 'Photo',
      'weight' => '10',
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
    'type' => 'number_float',
    'required' => '0',
    'multiple' => '0',
    'module' => 'number',
    'active' => '1',
    'prefix' => '',
    'suffix' => 'm³',
    'min' => '0',
    'max' => '10000000',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_volume][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Volume',
      'weight' => '2',
      'description' => 'Volume of waste, in m³',
      'type' => 'number',
      'module' => 'number',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Composition: biodegradable');
  t('Composition: construction');
  t('Composition: dangerous waste and tires');
  t('Composition: large');
  t('Composition: other');
  t('Coordinates');
  t('Number of tires');
  t('Photo');
  t('Volume');

  return $fields;
}
