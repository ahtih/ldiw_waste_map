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

"Geo" module needs to be extensively patched for Waste Map to work,
and the simplest way is to get a patched version of Geo using
	git clone --branch master git@git.drupal.org:sandbox/ahtih/1081362.git <your-destination-dir>
This is Geo HEAD version patched with http://drupal.org/node/{804878,883020,776436,813482,667034}

"Views Bonus Pack" module needs the following patches:
- http://drupal.org/files/issues/views_bonus_csv_strip_html.patch (http://drupal.org/node/205741)
- http://drupal.org/files/issues/views_bonus_csv_separator.patch (http://drupal.org/node/890544)

You also need to make sure you are using 6.x-2.x-dev version of OpenLayers
Drupal module, or else apply patches for http://drupal.org/node/710908 ,
http://drupal.org/node/945728 and http://drupal.org/node/1011980 yourself.

You also need to patch OpenLayers JavaScript library:
- http://trac.osgeo.org/openlayers/ticket/2891
To do so:
	* Download it from http://www.openlayers.org/api/2.9/OpenLayers.js
						to sites/all/modules/openlayers/
	* Patch it with http://trac.osgeo.org/openlayers/ticket/2891
	* After installing Drupal OpenLayers module, configure the
						"OpenLayers Source" at `admin/build/openlayers` as
						"sites/all/modules/openlayers/OpenLayers.js"

The LDIW Waste Map API (ldiw_api submodule of this module) requires
Services module to have at least 3.x version.

Drupal status report at `admin/reports/status` checks some of these
requirements/patches and reports whether the setup is OK.

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
