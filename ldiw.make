core = 6.x

projects[] = drupal

projects[] = auto_nodetitle
projects[] = computed_field
projects[] = cck
projects[] = ctools
projects[] = features
projects[] = filefield
projects[] = imagefield
projects[] = strongarm
projects[] = views
projects[] = formfilter

projects[openlayers][version] = 2.x-dev

projects[wfs][patch][] = "http://drupal.org/files/issues/wfs-filter-changes.patch"
projects[geo][patch][] = "http://drupal.org/files/issues/geo-filter-float.patch"
projects[geo][patch][] = "http://drupal.org/files/issues/geo-ewkb-parsing.patch"
projects[geo][patch][] = "http://drupal.org/files/issues/geo-883032.patch"

projects[geoclustering][type] = "module"
projects[geoclustering][download][type] = "git"
projects[geoclustering][download][url] = "git://github.com/ahtih/Geoclustering.git"

projects[ldiw_waste_map][type] = "module"
projects[ldiw_waste_map][download][type] = "git"
projects[ldiw_waste_map][download][url] = "git://github.com/ahtih/ldiw_waste_map.git"

projects[] = advanced_help
projects[] = date
projects[node_import][patch][] = http://drupal.org/files/issues/node_import-707760.patch
