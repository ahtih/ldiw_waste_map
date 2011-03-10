// $Id$

Drupal.openlayers.style_plugin["ldiw_waste_map_point_style_plugin"]=
													function(parameters) {

Drupal.theme.openlayersAddPointContentNoNodeID=function(feature)
{
	return Drupal.t('This is a cluster of @nr_of_nodes Waste points. ' + 
		'You have to zoom in before you can see and edit them individually.',
		{'@nr_of_nodes':feature.attributes.nr_of_nodes});
	}

ldiw_waste_map_point_style_plugin_zoom_in=function(map_id,lon,lat)
{
	var map_obj=$('#' + map_id).data('openlayers').openlayers;

	map_obj.setCenter(new OpenLayers.LonLat(lon,lat),
				map_obj.getZoomForResolution(map_obj.resolution / 8,true));

		// Close popups

	for (var i=map_obj.popups.length-1;i >= 0;i--)
		map_obj.removePopup(map_obj.popups[i]);
	}

Drupal.theme.openlayersPopup=function(feature)
{
	var style_hack=document.getElementById(
						'ldiw_waste_map_point_style_plugin_firefox_hack');
	if (style_hack)
		document.body.removeChild(style_hack);

	var attrs=feature.attributes;

	var volume=parseFloat(attrs.volume || '0');
	var coeff=volume >= 5 ? 1 : 10;
	var volume_formatted=Math.round(volume * coeff) / coeff;
	if (volume_formatted == 0)
		volume_formatted=0.1;

	var composition_array=[];
	var composition_sum=0;
	for (var attrname in Drupal.settings.ldiw_waste_map_composition_fields) {
		if (attrs[attrname]) {
			var value=parseFloat(attrs[attrname]);
			if (value > 0) {
				composition_array.push([attrname,value]);
				composition_sum+=value;
				}
			}
		}

	for (var i in composition_array) {
		var attrname=composition_array[i][0];
		var text=Drupal.settings.ldiw_waste_map_composition_fields
													[attrname]['text'];
		if (composition_array.length == 1)
			text=Drupal.settings.ldiw_waste_map_composition_fields
											[attrname]['text_solo'] || text;
		composition_array[i]=Math.max(1,
				parseInt(composition_array[i][1]*100 / composition_sum)) +
				'%&nbsp;' + text;
		}

	if (attrs.nr_of_tires && attrs.nr_of_tires != '0')
		composition_array.push(Drupal.t('@nr_of_tires tires',
									{'@nr_of_tires':attrs.nr_of_tires}));

	var composition=composition_array.join(', ');
	if (composition)
		composition='<br>' + Drupal.t('Composition') + ': ' + composition;

	var output='<div style="float:right; text-align:right">';
	var reserve_text='';

	if (feature.layer.map.getZoom()+1 <
									feature.layer.map.getNumZoomLevels()) {
		var coords=feature.geometry.getBounds().getCenterLonLat();
		var reserve_text='<b>' + Drupal.t('Zoom in here') + '</b>';
		output+='<a href="#" onclick="' + 
						'ldiw_waste_map_point_style_plugin_zoom_in(\'' + 
						feature.layer.map.div.id +
						'\',' + coords.lon + ',' + coords.lat +
						')">' + reserve_text + '</a>';
		}

	if (attrs.nr_of_nodes && attrs.nr_of_nodes > 1) {
		output+='</div><b>' + Drupal.t('@nr_of_points waste points',
									{'@nr_of_points':attrs.nr_of_nodes}) +
				'</b><br>' +
				Drupal.t('Total volume <b>@volumem&sup3;</b>',
											{'@volume':volume_formatted}) +
				composition;
		}
	else {
		output+='<br>' + Drupal.t('ID') + '&nbsp;#' + attrs.id + '<br></div>';

		var volume_text=Drupal.t('Volume') + ' <b>';
		if (volume)
			volume_text+=volume_formatted + 'm&sup3;';
		else
			volume_text+=Drupal.t('unknown');
		volume_text+='</b>';
		reserve_text=volume_text + reserve_text;

		output+=volume_text + composition;
		if (attrs.geo_areas_json) {
			var geo_areas=JSON.parse(attrs.geo_areas_json);
			for (var hierarchy in geo_areas)
				output+='<br>' + hierarchy + ': ' + geo_areas[hierarchy];
			}
		if (attrs.description)
			output+='<br><br>' + attrs.description;
		if (attrs.photos) {
			var photo_divs=[];
			var photos=attrs.photos.split(' ');
			var popup_width=0;
			var max_photo_width=Math.min(
						OpenLayers.Popup.FramedCloud.prototype.maxSize.w,
						feature.layer.map.size.w-
								feature.layer.map.paddingForPopups.left-
								feature.layer.map.paddingForPopups.right)-
						170;
			for (var i in photos) {
				var photo=photos[i].split(':');
				var div_id=Math.floor(Math.random()*1000000);

				var width=photo[1] || 400;
				var height=photo[2] || 0;
				if (width > max_photo_width) {
					height=max_photo_width * height / width;
					width=max_photo_width;
					}
				popup_width=Math.max(popup_width,width);
				output+='<div id="' + div_id + '">' +
						'<img src="' +
							Drupal.settings.ldiw_waste_map_base_url +
							'/photo/' + attrs.id + '/' + photo[0] + '" ' +
							'width="' + width + '"';
				if (height)
					output+=' height="' + height + '"';
				output+='/></div>';

				photo_divs.push(photo.concat([div_id,width,height]));
				}

			if (OpenLayers.Util.getBrowserName() == 'firefox') {
				var style=document.createElement('style');
				style.id='ldiw_waste_map_point_style_plugin_firefox_hack';
				style.innerHTML=
						".olFramedCloudPopupContent { min-width:" +
						(popup_width + OpenLayers.Util.getScrollbarWidth()) +
						"px; }";
				document.body.appendChild(style);
				}

			$.post(Drupal.settings.ldiw_waste_map_base_url +
						'/photos_ajax/' + attrs.id,
					'',function(data) {
							for (var i in photo_divs) {
								var div=photo_divs[i];
								var photo=data[div[0]];
								if (!photo)
									continue;

								var html='<img src="' + photo['url'] + '"';
								if ('width' in photo)
									html+=' width="' + div[4] + '"';
								if ('height' in photo)
									html+=' height="' + div[5] + '"';
								html+='/>';
								if ('link_url' in photo)
									html='<a href="' + photo['link_url'] +
													'">' + html + '</a>';
								if ('attribution_html' in photo)
									html+='<div>' +
										photo['attribution_html'] + '</div>';

								$('#' + div[3]).html(html);
								}
							},
					'json');
			}
		else
			output+='<br><span style="opacity:0; filter:alpha(opacity=0);">' +
													reserve_text + '</span>';
		}

	return '<div class="openlayers-popup">' + output + '</div>';
	}
}

Drupal.openlayers.style_plugin["ldiw_waste_map_point_style_plugin"].prototype=
{
	calc_pointRadius:function(feature)
		{
			this.parse_composition(feature);
			return feature.attributes.style_pointRadius;
			},

	calc_backgroundWidth:function(feature)
		{
			return this.calc_pointRadius(feature)*2 + 4;
			},

	calc_backgroundHeight:function(feature)
		{
			return this.calc_backgroundWidth(feature);
			},

	calc_backgroundXOffset:function(feature)
		{
			return this.calc_backgroundWidth(feature) * -0.5 + 4;
			},

	calc_backgroundYOffset:function(feature)
		{
			return this.calc_backgroundXOffset(feature);
			},

	parse_composition:function(feature)
		{
			if (feature.attributes.style_pointRadius !== undefined)
				return;

			var attrs=feature.attributes;

			feature.attributes.style_pointRadius=parseInt(Math.min(20,
						4+3*Math.log(Math.sqrt(Math.max(1,
							parseFloat(feature.attributes.volume || '0'))))));

			var composition=[];
			var composition_sum=0;

			for (var attrname in Drupal.settings.
										ldiw_waste_map_composition_fields) {
				if (attrs[attrname]) {
					var value=parseFloat(attrs[attrname]);
					if (value > 0) {
						composition.push([Drupal.settings.
								ldiw_waste_map_composition_fields
														[attrname]['color'],
								value]);
						composition_sum+=value;
						}
					}
				}

			composition.sort(function(a,b){return a[1]-b[1]});

			if (composition.length > 1) {
				var threshold=composition_sum * (1 - 500 / Math.pow(
									feature.attributes.style_pointRadius,4));
				if (composition[composition.length-1][1] > threshold) {
					composition[0]=composition[composition.length-1];
					composition.length=1;
					composition_sum=composition[0][1];
					}
				}

			feature.attributes.style_fillColor='';
			feature.attributes.style_externalGraphic='';

			if (composition.length <= 1) {
				feature.attributes.style_fillColor=composition.length ?
										'#' + composition[0][0] : '#a0a0a0';
				return;
				}

			var composition_slots_left=8;
			var coeff=composition_slots_left / Math.max(1e-9,composition_sum);
			for (var i=0;i < composition.length-1;i++) {
				composition[i][1]=Math.max(1,Math.round(
											composition[i][1] * coeff));
				composition_slots_left-=composition[i][1];
				}
			composition[composition.length-1][1]=composition_slots_left;
			composition.sort(function(a,b){
									if (a[0] < b[0]) return -1;
									if (a[0] > b[0]) return 1;
									return 0;});

			for (var i=0;i < composition.length;i++)
				composition[i]=composition[i].join(':');

			feature.attributes.style_externalGraphic=Drupal.settings.
						ldiw_waste_map_point_style_plugin_icons_base_url +
											composition.join('_') + '.png';
			},

	calc_externalGraphic:function(feature)
		{
			this.parse_composition(feature);
			return feature.attributes.style_externalGraphic;
			},

	calc_fillColor:function(feature)
		{
			this.parse_composition(feature);
			return feature.attributes.style_fillColor;
			}
	};
