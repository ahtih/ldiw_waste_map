$Id:

LDIW Waste Map for Drupal 6.x
-----------------------------
LDIW Waste Map module provides:

- "Waste Point" content type, which has fields such as Geo coordinates,
	photos, amount and composition of waste, etc.
- Waste Map display, displaying the "Waste Point" nodes. This is implemented
	using OpenLayers and Geoclustering modules. If you have more than
	ca 400 points, map level of detail will start to change dynamically
	as you zoom in and out in map display. It should scale to over
	100 000 waste points.
- Adding/editing Waste Points directly on map display, by clicking on map.

The module is intended to be used in http://www.letsdoitworld.org/ project,
and is likely not useful outside of it.

Installation
------------
LDIW Waste Map can be installed like any other Drupal module -- place it
in the modules directory for your site and enable it on the
`admin/build/modules` page. There are a number of dependencies as well
(e.g. OpenLayers) which are pointed out to you when you enable the module.

Many patches to other modules are needed for Waste Map to really work:
- http://drupal.org/files/issues/geo_openlayers_0.patch (http://drupal.org/node/804878)
- http://drupal.org/files/issues/geo-ewkb-parsing.patch (http://drupal.org/node/883020)
- http://drupal.org/files/issues/geo-table-prefixes-776436.patch (http://drupal.org/node/776436)
- http://drupal.org/files/issues/geo-813482-updated.patch (http://drupal.org/node/813482)
- http://drupal.org/files/issues/geo-667034.patch (http://drupal.org/node/667034)
- http://drupal.org/files/issues/views_bonus_csv_strip_html.patch (http://drupal.org/node/205741)
- http://drupal.org/files/issues/views_bonus_csv_separator.patch (http://drupal.org/node/890544)

You also need to make sure you are using dev version of OpenLayers Drupal
module, or else apply patch es for http://drupal.org/node/945728 and
http://drupal.org/node/1011980 yourself.

You also need to patch OpenLayers JavaScript library:
- http://trac.osgeo.org/openlayers/ticket/2891

The LDIW Waste Map API (ldiw_api submodule of this module) requires
Services module to have at least 3.x version.

Adding data to Waste Map
------------------------
To see anything useful on Waste Map, you need to add some content
(nodes having "Waste Point" content type) using the usual Drupal methods
(e.g. on `node/add/waste-point` page) or clicking on map in
"Add/Edit Waste points" mode.

You can also mass-import ca 10k Waste Points from Estonia's 2008 cleanup;
these are provided in sample_data/prygikohad.csv in CSV format. You can
import them e.g. using Node Import module, but you have to apply
http://drupal.org/files/issues/node_import-707760.patch to get Node Import
to support Geo fields.

After that you should see the map at http://{your-drupal-root-URL}/waste_map

Using Geographic areas
----------------------
You can optionally define a system of "Geographic areas" like counties,
municipalities etc. Then each Waste point will automatically be categorised
to some of these areas; you can see that information in Waste Map, and you
can also easily create reports on Waste points by county etc.

First you need to obtain boundaries of these areas in WKT format. Potential
sources are http://www.gadm.org/countryres or your national Land Board
or GIS companies.

Then you can create a number of "Geographic area hierarchy levels" at
/node/add/geo-hierarchy-level , and then "Geographic areas" at
/node/add/geo-area. Both of these are ordinary nodes with some CCK fields;
thus you can get an overview of defined hierarchy levels and areas at
/admin/content/node.

After editing areas or hierarchy levels, you should perform a
"Recalculate Geographic Areas data for Waste point nodes" operation at
/admin/settings/ldiw_waste_map.

Maintainers
-----------
- ahtih (Ahti Heinla)
