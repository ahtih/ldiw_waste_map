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
	git clone git@git.drupal.org:sandbox/ahtih/1081362.git <your-destination-dir>
This is Geo HEAD version patched with http://drupal.org/node/{804878,883020,776436,813482,667034,883032,1104696,1136622,1090154}

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

When users view the Waste Map, the map can automatically zoom in to users
location, determined using geoip module. To enable this, you need
to download the http://geolite.maxmind.com/download/geoip/database/GeoLiteCity.dat.gz
(or the paid version at http://www.maxmind.com/app/city ) file, and
uncompress it to sites/all/libraries/geoip directory (create the directory
if it does not exist).

The LDIW Waste Map API (ldiw_api submodule of this module) requires
Services module to have at least 3.x version.

Drupal status report at `admin/reports/status` checks some of these
requirements/patches and reports whether the setup is OK.

Configuring Waste Point data fields
-----------------------------------
The module supports configurable data fields for Waste Points.
For example, you can define a "Terrain type" field, with a "Select list"
input widget; or a checkbox "Contains hazardous substances" or
"Located on private property". To do so, just edit the Waste Point
content type at `admin/content/node-type/waste-point/fields`
and add/remove fields as you wish. Only the "Coordinates", "Volume",
"Photos ID:Width:Height", "Geographic areas", and "Geographic area names"
fields are mandatory, do not remove these.

After adding new fields, you must also give permissions to view/edit
these fields for anonymous users at `admin/user/permissions`, otherwise
they do not appear in Waste point edit form due to lack of permissions.

If you want to determine waste quantity by other means than asking
for volume in cubic meters, you can change the "Volume" field to
be a Computed Field, and calculate its value (always in cubic meters)
based on other fields using a PHP code snippet
(see http://drupal.org/project/computed_field ).

Configuring Waste Point composition data fields
-----------------------------------------------
Some of Waste Point data fields describe composition of waste
(plastics, paper, ...). By default there are 5 composition fields:
field_composition_pmp, field_composition_paper etc. If these are not
suitable for you, you can configure these as well.

First modify the "Waste point" content type so that the composition
fields are such that you need: `admin/content/node-type/waste-point/fields`

You can delete default composition fields and replace them with fields
suitable for you. Add all of them as Float fields. You can name them any
way you want. In "Configuration" for these fields, use the same settings
as default composition fields (min value 0, max value 100, suffix %,
and not "Required").

When you have added these fields, you can go to LDIW settings at
`admin/settings/ldiw_waste_map` and specify that those fields are meant
to be composition fields. To do that, specify a map label and marker
color for each of them. These labels/colors specify how the composition
is displayed in map and mobile app. Colors do not need to be unique:
you can have several composition types share the same color.

There is also a checkbox "For each Waste point, select only the main
composition type, instead of percentages of all composition types".
This means that instead of inputting/displaying these fields as percentages
("80% glass, 20% large"), only the largest composition type is
input/displayed ("glass" in this example).

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

First you need to obtain boundaries of these areas in WKT or ESRI Shapefile
(SHP) format. Potential sources are http://www.gadm.org/countryres or your
national Land Board or GIS companies.

Then you can create a number of "Geographic area hierarchy levels" at
`node/add/geo-hierarchy-level` , and then "Geographic areas" at
`node/add/geo-area`. Both of these are ordinary nodes with some CCK fields;
thus you can get an overview of defined hierarchy levels and areas at
`admin/content/node`.

You can also import Geographic areas from ESRI Shapefile at
`admin/settings/ldiw_waste_map/geo_areas`.

After editing areas or hierarchy levels, you should perform a
"Recalculate Geographic Areas fields for Waste point nodes" operation at
`admin/settings/ldiw_waste_map/geo_areas`.

Maintainers
-----------
- ahtih (Ahti Heinla)
