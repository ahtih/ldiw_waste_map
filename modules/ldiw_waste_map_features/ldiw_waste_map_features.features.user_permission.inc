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

  // Exported permission: edit field_composition_biodegradable
  $permissions['edit field_composition_biodegradable'] = array(
    'name' => 'edit field_composition_biodegradable',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: edit field_composition_construction
  $permissions['edit field_composition_construction'] = array(
    'name' => 'edit field_composition_construction',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: edit field_composition_dangerous
  $permissions['edit field_composition_dangerous'] = array(
    'name' => 'edit field_composition_dangerous',
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

  // Exported permission: edit field_coords
  $permissions['edit field_coords'] = array(
    'name' => 'edit field_coords',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: edit field_external_photo
  $permissions['edit field_external_photo'] = array(
    'name' => 'edit field_external_photo',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: edit field_nr_of_tires
  $permissions['edit field_nr_of_tires'] = array(
    'name' => 'edit field_nr_of_tires',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
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

  // Exported permission: edit own waste_point content
  $permissions['edit own waste_point content'] = array(
    'name' => 'edit own waste_point content',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view field_composition_biodegradable
  $permissions['view field_composition_biodegradable'] = array(
    'name' => 'view field_composition_biodegradable',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view field_composition_construction
  $permissions['view field_composition_construction'] = array(
    'name' => 'view field_composition_construction',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view field_composition_dangerous
  $permissions['view field_composition_dangerous'] = array(
    'name' => 'view field_composition_dangerous',
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

  // Exported permission: view field_coords
  $permissions['view field_coords'] = array(
    'name' => 'view field_coords',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view field_external_photo
  $permissions['view field_external_photo'] = array(
    'name' => 'view field_external_photo',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: view field_nr_of_tires
  $permissions['view field_nr_of_tires'] = array(
    'name' => 'view field_nr_of_tires',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
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

  return $permissions;
}
