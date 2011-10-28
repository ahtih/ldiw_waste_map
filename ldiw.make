api = 2

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
projects[] = colorpicker
projects[] = geoip
projects[] = autoload
projects[] = i18nstrings

projects[openlayers][version] = 2.x-dev

projects[views_bonus][version] = 1.x-dev
projects[views_bonus][patch][] = "http://drupal.org/files/issues/views_bonus_csv_strip_html.patch"
projects[views_bonus][patch][] = "http://drupal.org/files/issues/views_bonus_csv_separator.patch"

projects[geo][download][type] = "cvs"
projects[geo][download][module] = "contributions/modules/geo"
projects[geo][download][revision] = HEAD
projects[geo][patch][] = "http://drupal.org/files/issues/geo_openlayers_0.patch"
projects[geo][patch][] = "http://drupal.org/files/issues/geo-ewkb-parsing.patch"
projects[geo][patch][] = "http://drupal.org/files/issues/geo-table-prefixes-776436.patch"
projects[geo][patch][] = "http://drupal.org/files/issues/geo-813482-updated.patch"
projects[geo][patch][] = "http://drupal.org/files/issues/geo-667034.patch"
projects[geo][patch][] = "http://drupal.org/files/issues/geo-883032.patch"
projects[geo][patch][] = "http://drupal.org/files/issues/geo_latlon_maxlength.patch"
projects[geo][patch][] = "http://drupal.org/files/issues/geo-shp2sql-char-encoding.patch"

projects[geoclustering][type] = "module"
projects[geoclustering][download][type] = "git"
projects[geoclustering][download][url] = "git://github.com/ahtih/Geoclustering.git"

projects[ldiw_waste_map][type] = "module"
projects[ldiw_waste_map][download][type] = "git"
projects[ldiw_waste_map][download][url] = "git://github.com/ahtih/ldiw_waste_map.git"

projects[] = advanced_help
projects[] = date
projects[node_import][patch][] = http://drupal.org/files/issues/node_import-707760.patch

projects[services][version] = 3.x-dev
