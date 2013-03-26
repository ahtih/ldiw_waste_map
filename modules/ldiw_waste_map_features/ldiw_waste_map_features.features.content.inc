<?php

/**
 * Implementation of hook_content_default_fields().
 */
function ldiw_waste_map_features_content_default_fields() {
  $fields = array();

  // Exported field: field_geo
  $fields['geo_area-field_geo'] = array(
    'field_name' => 'field_geo',
    'type_name' => 'geo_area',
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
      'token' => array(
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
    'geo_type' => 'multipolygon',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'geo' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Geometry',
      'weight' => '1',
      'description' => 'The borders of this area in WKT format (usually a MULTIPOLYGON). This is usually very long text, often 100 000 characters or more; so take care when copy/pasting it.',
      'type' => 'geo_wkt',
      'module' => 'geo_field',
    ),
  );

  // Exported field: field_hierarchy_level
  $fields['geo_area-field_hierarchy_level'] = array(
    'field_name' => 'field_hierarchy_level',
    'type_name' => 'geo_area',
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
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '1',
    'multiple' => '0',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'geo_hierarchy_level' => 'geo_hierarchy_level',
      'cleanup_project' => 0,
      'geo_area' => 0,
      'page' => 0,
      'story' => 0,
      'waste_point' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => 60,
      'default_value' => array(
        '0' => array(
          'nid' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Hierarchy level',
      'weight' => '2',
      'description' => 'The <em>Geographic area hierarchy level</em> this area belongs to; e.g. is it a country, or state, or municipality, or something else.',
      'type' => 'nodereference_select',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_parent
  $fields['geo_area-field_parent'] = array(
    'field_name' => 'field_parent',
    'type_name' => 'geo_area',
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
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '0',
    'multiple' => '0',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'geo_area' => 'geo_area',
      'cleanup_project' => 0,
      'geo_hierarchy_level' => 0,
      'page' => 0,
      'story' => 0,
      'waste_point' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'starts_with',
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
          '_error_element' => 'default_value_widget][field_parent][0][nid][nid',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Parent area name',
      'weight' => '3',
      'description' => 'If this geographic area is not at highest defined hierarchy level, then usually it is topologically part of a larger area one level up in hierarchy. If so, fill in the name of this larger area.',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_display_parent
  $fields['geo_hierarchy_level-field_display_parent'] = array(
    'field_name' => 'field_display_parent',
    'type_name' => 'geo_hierarchy_level',
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
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'number_integer',
    'required' => '1',
    'multiple' => '0',
    'module' => 'number',
    'active' => '1',
    'prefix' => '',
    'suffix' => '',
    'min' => '',
    'max' => '',
    'allowed_values' => '0|Do not display parent name
1|Display parent name',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => 0,
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Display parent name',
      'weight' => '32',
      'description' => 'Check this if the <em>Name</em> of areas in this hiearchy level is not enough to uniquely identify them without parent area name being present. For example, in Germany not everybody might know where <em>Main-Spessart</em> is, so displaying the parent name (<em>Main-Spessart, Bavaria</em>) is good; similarly, in USA there are several <em>Fayette</em> counties, so <em>Fayette county, Texas</em> is appropriate to display. This is achieved by checking this checkbox for <em>County</em> hierarchy level.',
      'type' => 'optionwidgets_onoff',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_parent_level
  $fields['geo_hierarchy_level-field_parent_level'] = array(
    'field_name' => 'field_parent_level',
    'type_name' => 'geo_hierarchy_level',
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
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '0',
    'multiple' => '0',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'geo_hierarchy_level' => 'geo_hierarchy_level',
      'cleanup_project' => 0,
      'geo_area' => 0,
      'page' => 0,
      'story' => 0,
      'waste_point' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => 60,
      'default_value' => array(
        '0' => array(
          'nid' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Parent hierarchy level',
      'weight' => '31',
      'description' => 'Select a hierarchy level which is one level up from the level you are creating/editing. For example, if you are editing a <em>County</em> hierarchy level, then you might want to select its parent to be the <em>Country</em> level. Select <em>None</em> if this is the highest hierarchy level you have.',
      'type' => 'nodereference_select',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_waste_point_display_label
  $fields['geo_hierarchy_level-field_waste_point_display_label'] = array(
    'field_name' => 'field_waste_point_display_label',
    'type_name' => 'geo_hierarchy_level',
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
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_waste_point_display_label][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => '"Waste point" display label',
      'weight' => '33',
      'description' => 'This controls how information about geographic areas is displayed for individual Waste points in Waste Map popups. If you write a label here for a hierarchy level, then popups will include this label and the area of this level where the Waste point belongs to. For example, having label "Administrative division" for United States <em>County</em> level makes <em>Administrative division: Fayette County, Texas</em> to be displayed in popups. More than one hierarchy level may have this set; this makes sense for example if one is administrative division, and another a state forestry division. Then popups show where Waste point belongs to according to both hierarchies.',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_cleaned_by_mapper
  $fields['waste_point-field_cleaned_by_mapper'] = array(
    'field_name' => 'field_cleaned_by_mapper',
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
      'token' => array(
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
    'max' => '1',
    'allowed_values' => '0|I did not clean it up
1|I cleaned it up after mapping',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => 0,
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Cleaned by mapper',
      'weight' => '31',
      'description' => '',
      'type' => 'optionwidgets_onoff',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_composition_glass
  $fields['waste_point-field_composition_glass'] = array(
    'field_name' => 'field_composition_glass',
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
      'token' => array(
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
          '_error_element' => 'default_value_widget][field_composition_glass][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Glass (incl glass bottles)',
      'weight' => '7',
      'description' => '',
      'type' => 'number',
      'module' => 'number',
    ),
  );

  // Exported field: field_composition_large
  $fields['waste_point-field_composition_large'] = array(
    'field_name' => 'field_composition_large',
    'type_name' => 'waste_point',
    'display_settings' => array(
      'weight' => '5',
      'parent' => '',
      'label' => array(
        'format' => 'above',
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
      'label' => 'Large objects like furniture',
      'weight' => '8',
      'description' => '',
      'type' => 'number',
      'module' => 'number',
    ),
  );

  // Exported field: field_composition_other
  $fields['waste_point-field_composition_other'] = array(
    'field_name' => 'field_composition_other',
    'type_name' => 'waste_point',
    'display_settings' => array(
      'weight' => '9',
      'parent' => '',
      'label' => array(
        'format' => 'above',
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
      'label' => 'Other',
      'weight' => '9',
      'description' => '',
      'type' => 'number',
      'module' => 'number',
    ),
  );

  // Exported field: field_composition_paper
  $fields['waste_point-field_composition_paper'] = array(
    'field_name' => 'field_composition_paper',
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
      'token' => array(
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
          '_error_element' => 'default_value_widget][field_composition_paper][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Paper or cardboard',
      'weight' => '6',
      'description' => '',
      'type' => 'number',
      'module' => 'number',
    ),
  );

  // Exported field: field_composition_pmp
  $fields['waste_point-field_composition_pmp'] = array(
    'field_name' => 'field_composition_pmp',
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
      'token' => array(
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
          '_error_element' => 'default_value_widget][field_composition_pmp][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Plastics, metals, packaging',
      'weight' => '5',
      'description' => '',
      'type' => 'number',
      'module' => 'number',
    ),
  );

  // Exported field: field_coords
  $fields['waste_point-field_coords'] = array(
    'field_name' => 'field_coords',
    'type_name' => 'waste_point',
    'display_settings' => array(
      'weight' => '1',
      'parent' => '',
      'label' => array(
        'format' => 'above',
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

  // Exported field: field_external_photo
  $fields['waste_point-field_external_photo'] = array(
    'field_name' => 'field_external_photo',
    'type_name' => 'waste_point',
    'display_settings' => array(
      'weight' => '13',
      'parent' => '',
      'label' => array(
        'format' => 'above',
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
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '10',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '10000',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_external_photo][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'External photo',
      'weight' => '12',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_geo_areas
  $fields['waste_point-field_geo_areas'] = array(
    'field_name' => 'field_geo_areas',
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
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '0',
    'multiple' => '10',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'geo_area' => 'geo_area',
      'cleanup_project' => 0,
      'geo_hierarchy_level' => 0,
      'page' => 0,
      'story' => 0,
      'waste_point' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'starts_with',
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'nid' => NULL,
          '_error_element' => 'default_value_widget][field_geo_areas][0][nid][nid',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Geographic areas',
      'weight' => '14',
      'description' => '',
      'type' => 'nodereference_autocomplete',
      'module' => 'nodereference',
    ),
  );

  // Exported field: field_geo_areas_json
  $fields['waste_point-field_geo_areas_json'] = array(
    'field_name' => 'field_geo_areas_json',
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
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_geo_areas_json][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Geographic area names',
      'weight' => '15',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_nr_of_tires
  $fields['waste_point-field_nr_of_tires'] = array(
    'field_name' => 'field_nr_of_tires',
    'type_name' => 'waste_point',
    'display_settings' => array(
      'weight' => '3',
      'parent' => '',
      'label' => array(
        'format' => 'above',
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
      'weight' => '10',
      'parent' => '',
      'label' => array(
        'format' => 'above',
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

  // Exported field: field_photos_id_width_height
  $fields['waste_point-field_photos_id_width_height'] = array(
    'field_name' => 'field_photos_id_width_height',
    'type_name' => 'waste_point',
    'display_settings' => array(
      'weight' => '12',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
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
    'code' => '$node_field[0][\'value\'] = ldiw_waste_map_compute_photos_id_width_height($node);',
    'display_format' => '$display = $node_field_item[\'value\'];',
    'store' => 1,
    'data_type' => 'text',
    'data_length' => '',
    'data_not_NULL' => 0,
    'data_default' => '',
    'data_sortable' => 0,
    'widget' => array(
      'default_value' => NULL,
      'default_value_php' => NULL,
      'label' => 'Photos ID:Width:Height',
      'weight' => '11',
      'description' => '',
      'type' => 'computed',
      'module' => 'computed_field',
    ),
  );

  // Exported field: field_volume
  $fields['waste_point-field_volume'] = array(
    'field_name' => 'field_volume',
    'type_name' => 'waste_point',
    'display_settings' => array(
      'weight' => '2',
      'parent' => '',
      'label' => array(
        'format' => 'above',
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
      'description' => '',
      'type' => 'number',
      'module' => 'number',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('"Waste point" display label');
  t('Cleaned by mapper');
  t('Coordinates');
  t('Diameter');
  t('Display parent name');
  t('External photo');
  t('Geographic area names');
  t('Geographic areas');
  t('Geometry');
  t('Glass (incl glass bottles)');
  t('Hierarchy level');
  t('Large objects like furniture');
  t('Number of tires');
  t('Other');
  t('Paper or cardboard');
  t('Parent area name');
  t('Parent hierarchy level');
  t('Photo');
  t('Photos ID:Width:Height');
  t('Plastics, metals, packaging');
  t('Volume');

  return $fields;
}
