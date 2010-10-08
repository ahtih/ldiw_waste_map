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

  // Exported permission: edit own waste_point content
  $permissions['edit own waste_point content'] = array(
    'name' => 'edit own waste_point content',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  return $permissions;
}
