// $Id

/**
 * Openlayer layer handler for WFS BBOX Vector Layer Type
 */
Drupal.openlayers.layer.ldiw_waste_map_wfs = function(title, map, options) {
  options_2 = {
    drupalID: options.drupalID,
    strategies: [new OpenLayers.Strategy.BBOX({	resFactor:1.4,
												ratio:1})],
    projection: "EPSG:4326",
    buffer: 0,
    protocol: new OpenLayers.Protocol.WFS({
        url: options.url,
        featurePrefix: 'drupal',
        featureType: options.typeName,
        geometryName: options.geometryName,
        formatOptions: {
          extractAttributes: true
        },
        featureNS: 'http://drupal.org/project/wfs',
        srsName: 'EPSG:4326',
        version: '1.1.0'
      })
  };

  var layer = new OpenLayers.Layer.Vector(title, options_2);
  layer.styleMap=Drupal.openlayers.getStyleMap(map,options.drupalID);
  return layer;
};
