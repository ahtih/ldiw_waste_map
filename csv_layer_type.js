// $Id

/**
 * Openlayers layer handler for CSV BBOX Vector Layer Type
 */

ldiw_waste_map_csv_protocol=OpenLayers.Class(OpenLayers.Protocol,{

	initialize:function(options) {
		OpenLayers.Protocol.prototype.initialize.apply(this,[options]);
		this.regexp=new RegExp(
						// Delimiters
					"(,|\\r?\\n|\\r|^)" +
						// Quoted fields
					"(?:\"([^\"]*(?:\"\"[^\"]*)*)\"|" +
						// Standard fields
					"([^\",\\r\\n]*))",
					'gi');
		this.unquote_regexp=new RegExp('""','g');
		},

	read:function(options) {
		OpenLayers.Protocol.prototype.read.apply(this,arguments);
		options=OpenLayers.Util.extend({},options);
		OpenLayers.Util.applyDefaults(options,this.options||{});

		var max_results=100;

		if (options.scope.layer.renderer.CLASS_NAME ==
												'OpenLayers.Renderer.SVG')
			max_results=400;

		var screen_size;	// Screen size is a rough proxy for CPU speed
		if (window.innerWidth)
			screen_size=window.innerWidth + window.innerHeight;
        else
			screen_size=document.body.clientWidth +
												document.body.clientHeight;
		if (screen_size)
			max_results=parseInt(Math.min(400,max_results*
									Math.max(0.1,screen_size / 2400.0)));

		var url=options.url;
		url+=(url.indexOf('?') >= 0) ? '&' : '?';
		url+='max_results=' + max_results;

		if (options.filter) {
			var bbox=options.filter.value;
			url+='&BBOX=' +
					[bbox.left,bbox.bottom,bbox.right,bbox.top].join(',');
			}

		var response=new OpenLayers.Protocol.Response({requestType:"read"});
		response.priv=OpenLayers.Request.POST({
					url:url,
					callback:this.createCallback(
										this.handleRead,response,options),
					params:options.params,
					headers:options.headers});
		return response;
		},

	handleRead:function(response,options) {
		if (options.callback) {
			var request=response.priv;
			if (request.status >= 200 && request.status < 300) {
				response.features=this.parseFeatures(request);
				response.code=OpenLayers.Protocol.Response.SUCCESS;
				}
			else
				response.code=OpenLayers.Protocol.Response.FAILURE;
			options.callback.call(options.scope,response);
			}
		},

	parseFeatures:function(request) {
		if (!request.responseText || request.responseText.length <= 0)
			return null;

		var features=[];
		var columns;

		this.regexp.lastIndex=0;
		var cur_row=[];
		var match;
		while (match=this.regexp.exec(request.responseText)) {
			var delimiter=match[1];

				// Check if we are at the start of a new row

			if (delimiter.length && delimiter != ',') {
				if (!columns)
					columns=cur_row;
				else
					ldiw_waste_map_csv_protocol.add_feature(
												features,columns,cur_row);
				cur_row=[];
				}

			if (match[2])
					// Quoted value; unescape any double quotes
				cur_row.push(match[2].replace(this.unquote_regexp,'"'));
			else	// Unquoted value
				cur_row.push(match[3]);
			}

		ldiw_waste_map_csv_protocol.add_feature(features,columns,cur_row);
		return features;
		}
	});

ldiw_waste_map_csv_protocol.add_feature=function(features,columns,row) {
	var attributes={};

	for (var i=0;i < row.length;i++)
		if (row[i])
			attributes[columns[i]]=row[i];

	var lat_column='lat';	//!!! make configurable
	var lon_column='lon';	//!!! make configurable

	if (attributes[lat_column] == null || attributes[lon_column] == null)
		return;

	var geometry=new OpenLayers.Geometry.Point(attributes[lon_column],
													attributes[lat_column]);
	delete attributes[lat_column];
	delete attributes[lon_column];

	features.push(new OpenLayers.Feature.Vector(geometry,attributes));
	}

Drupal.openlayers.layer.ldiw_waste_map_csv=function(title,map,options) {
	var layer_options={
		drupalID: options.drupalID,
		strategies: [new OpenLayers.Strategy.BBOX({	resFactor:1.4,
													ratio:1})],
		projection: "EPSG:4326",
		buffer: 0,
		rendererOptions: {zIndexing: true},
		protocol: new ldiw_waste_map_csv_protocol(
									{url: options.base_url + options.url})
		};

	var layer=new OpenLayers.Layer.Vector(title,layer_options);
	layer.styleMap=Drupal.openlayers.getStyleMap(map,options.drupalID);
	return layer;
	};
