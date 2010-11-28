// $Id

/**
 * Openlayer layer handler for WFS BBOX Vector Layer Type
 */
Drupal.openlayers.layer.ldiw_waste_map_wfs = function(title, map, options) {
  var layer_options = {
    drupalID: options.drupalID,
    strategies: [new OpenLayers.Strategy.BBOX({	resFactor:1.4,
												ratio:1})],
    projection: "EPSG:4326",
    buffer: 0,
	rendererOptions: {zIndexing: true},
    protocol: new OpenLayers.Protocol.WFS({
        url: options.base_url + options.url,
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

  var layer=new OpenLayers.Layer.Vector(title,layer_options);
  layer.styleMap=Drupal.openlayers.getStyleMap(map,options.drupalID);
  return layer;
};
