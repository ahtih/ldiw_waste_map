<?php

/**
 * Implementation of hook_default_services_endpoint().
 */
function ldiw_waste_map_api_features_default_services_endpoint() {
  $export = array();
  $endpoint = new stdClass;
  $endpoint->disabled = FALSE; /* Edit this to true to make a default endpoint disabled initially */
  $endpoint->api_version = 3;
  $endpoint->name = 'wp';
  $endpoint->title = 'Waste points';
  $endpoint->server = 'rest_server';
  $endpoint->path = 'api';
  $endpoint->authentication = array();
  $endpoint->resources = array(
    'wp' => array(
      'alias' => '',
      'operations' => array(
        'retrieve' => array(
          'enabled' => 1,
          'services_oauth' => array(
            'credentials' => 'none',
            'authorization' => '*',
          ),
        ),
        'create' => array(
          'enabled' => 1,
          'services_oauth' => array(
            'credentials' => 'token',
            'authorization' => '*',
          ),
        ),
        'update' => array(
          'enabled' => 1,
        ),
      ),
    ),
    'user' => array(
      'alias' => '',
      'actions' => array(
        'login' => array(
          'enabled' => 1,
        ),
      ),
    ),
  );
  $endpoint->debug = 0;
  $endpoint->status = 1;

  $export['wp'] = $endpoint;
  return $export;
}
