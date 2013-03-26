<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function ldiw_waste_map_features_user_default_permissions() {
  $permissions = array();

  // Exported permission: create waste_point content
  $permissions['create waste_point content'] = array(
    'name' => 'create waste_point content',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: delete any waste_point content
  $permissions['delete any waste_point content'] = array(
    'name' => 'delete any waste_point content',
    'roles' => array(),
  );

  // Exported permission: delete own waste_point content
  $permissions['delete own waste_point content'] = array(
    'name' => 'delete own waste_point content',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: edit any waste_point content
  $permissions['edit any waste_point content'] = array(
    'name' => 'edit any waste_point content',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: edit field_cleaned_by_mapper
  $permissions['edit field_cleaned_by_mapper'] = array(
    'name' => 'edit field_cleaned_by_mapper',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: edit field_composition_glass
  $permissions['edit field_composition_glass'] = array(
    'name' => 'edit field_composition_glass',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: edit field_composition_large
  $permissions['edit field_composition_large'] = array(
    'name' => 'edit field_composition_large',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: edit field_composition_other
  $permissions['edit field_composition_other'] = array(
    'name' => 'edit field_composition_other',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: edit field_composition_paper
  $permissions['edit field_composition_paper'] = array(
    'name' => 'edit field_composition_paper',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: edit field_composition_pmp
  $permissions['edit field_composition_pmp'] = array(
    'name' => 'edit field_composition_pmp',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: edit field_coords
  $permissions['edit field_coords'] = array(
    'name' => 'edit field_coords',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: edit field_display_parent
  $permissions['edit field_display_parent'] = array(
    'name' => 'edit field_display_parent',
    'roles' => array(),
  );

  // Exported permission: edit field_external_photo
  $permissions['edit field_external_photo'] = array(
    'name' => 'edit field_external_photo',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: edit field_geo
  $permissions['edit field_geo'] = array(
    'name' => 'edit field_geo',
    'roles' => array(),
  );

  // Exported permission: edit field_geo_areas
  $permissions['edit field_geo_areas'] = array(
    'name' => 'edit field_geo_areas',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: edit field_geo_areas_json
  $permissions['edit field_geo_areas_json'] = array(
    'name' => 'edit field_geo_areas_json',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: edit field_hierarchy_level
  $permissions['edit field_hierarchy_level'] = array(
    'name' => 'edit field_hierarchy_level',
    'roles' => array(),
  );

  // Exported permission: edit field_nr_of_tires
  $permissions['edit field_nr_of_tires'] = array(
    'name' => 'edit field_nr_of_tires',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: edit field_parent
  $permissions['edit field_parent'] = array(
    'name' => 'edit field_parent',
    'roles' => array(),
  );

  // Exported permission: edit field_parent_level
  $permissions['edit field_parent_level'] = array(
    'name' => 'edit field_parent_level',
    'roles' => array(),
  );

  // Exported permission: edit field_photo
  $permissions['edit field_photo'] = array(
    'name' => 'edit field_photo',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: edit field_photos_id_width_height
  $permissions['edit field_photos_id_width_height'] = array(
    'name' => 'edit field_photos_id_width_height',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: edit field_volume
  $permissions['edit field_volume'] = array(
    'name' => 'edit field_volume',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: edit field_waste_point_display_label
  $permissions['edit field_waste_point_display_label'] = array(
    'name' => 'edit field_waste_point_display_label',
    'roles' => array(),
  );

  // Exported permission: edit own waste_point content
  $permissions['edit own waste_point content'] = array(
    'name' => 'edit own waste_point content',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view field_cleaned_by_mapper
  $permissions['view field_cleaned_by_mapper'] = array(
    'name' => 'view field_cleaned_by_mapper',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view field_composition_glass
  $permissions['view field_composition_glass'] = array(
    'name' => 'view field_composition_glass',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view field_composition_large
  $permissions['view field_composition_large'] = array(
    'name' => 'view field_composition_large',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view field_composition_other
  $permissions['view field_composition_other'] = array(
    'name' => 'view field_composition_other',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view field_composition_paper
  $permissions['view field_composition_paper'] = array(
    'name' => 'view field_composition_paper',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view field_composition_pmp
  $permissions['view field_composition_pmp'] = array(
    'name' => 'view field_composition_pmp',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view field_coords
  $permissions['view field_coords'] = array(
    'name' => 'view field_coords',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view field_display_parent
  $permissions['view field_display_parent'] = array(
    'name' => 'view field_display_parent',
    'roles' => array(),
  );

  // Exported permission: view field_external_photo
  $permissions['view field_external_photo'] = array(
    'name' => 'view field_external_photo',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view field_geo
  $permissions['view field_geo'] = array(
    'name' => 'view field_geo',
    'roles' => array(),
  );

  // Exported permission: view field_geo_areas
  $permissions['view field_geo_areas'] = array(
    'name' => 'view field_geo_areas',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view field_geo_areas_json
  $permissions['view field_geo_areas_json'] = array(
    'name' => 'view field_geo_areas_json',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view field_hierarchy_level
  $permissions['view field_hierarchy_level'] = array(
    'name' => 'view field_hierarchy_level',
    'roles' => array(),
  );

  // Exported permission: view field_nr_of_tires
  $permissions['view field_nr_of_tires'] = array(
    'name' => 'view field_nr_of_tires',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view field_parent
  $permissions['view field_parent'] = array(
    'name' => 'view field_parent',
    'roles' => array(),
  );

  // Exported permission: view field_parent_level
  $permissions['view field_parent_level'] = array(
    'name' => 'view field_parent_level',
    'roles' => array(),
  );

  // Exported permission: view field_photo
  $permissions['view field_photo'] = array(
    'name' => 'view field_photo',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view field_photos_id_width_height
  $permissions['view field_photos_id_width_height'] = array(
    'name' => 'view field_photos_id_width_height',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view field_volume
  $permissions['view field_volume'] = array(
    'name' => 'view field_volume',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view field_waste_point_display_label
  $permissions['view field_waste_point_display_label'] = array(
    'name' => 'view field_waste_point_display_label',
    'roles' => array(),
  );

  return $permissions;
}
