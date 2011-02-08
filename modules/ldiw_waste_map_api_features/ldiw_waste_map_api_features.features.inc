<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function ldiw_waste_map_api_features_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "services" && $api == "services") {
    return array("version" => 3);
  }
}
