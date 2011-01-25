// $Id$

ldiw_waste_map_behavior_automaticpopup_finished=false;

Drupal.behaviors.ldiw_waste_map_behavior_automaticpopup=function(context)
{
	var data=$(context).data('openlayers');
	if (data && data.map.behaviors['ldiw_waste_map_behavior_automaticpopup']) {
		var options=data.map.behaviors[
								'ldiw_waste_map_behavior_automaticpopup'];
		var layers=data.openlayers.getLayersBy('drupalID',
												options.features_layer);
		if (layers.length)
			layers[0].events.register('featuresadded',layers[0],function()
					{
						if (!Drupal.openlayers.popup.popupSelect)
							return;

						if (ldiw_waste_map_behavior_automaticpopup_finished)
							return;
						ldiw_waste_map_behavior_automaticpopup_finished=true;

						var map_extent=this.map.getExtent();
						var map_size=map_extent.getSize();
						var leeway_w=map_size.w * Math.max(0.1,
									1-(this.map.paddingForPopups.left+
									this.map.paddingForPopups.right+
									OpenLayers.Popup.FramedCloud.
													prototype.maxSize.w) /
												parseFloat(this.map.size.w));
						var leeway_h=map_size.h * Math.max(0.1,
									1-(this.map.paddingForPopups.top+
									this.map.paddingForPopups.bottom+
									OpenLayers.Popup.FramedCloud.
													prototype.maxSize.h) /
												parseFloat(this.map.size.h));
						var min_forbidden_w=map_extent.left  + leeway_w;
						var max_forbidden_w=map_extent.right - leeway_w;

						var min_forbidden_h=map_extent.bottom + leeway_h;
						var max_forbidden_h=map_extent.top    - leeway_h;

						var candidates=Array();
						for (var i in this.features) {
							var coords=this.features[i].geometry.
											getBounds().getCenterLonLat();
							if ((coords.lon >= min_forbidden_w &&
										coords.lon <= max_forbidden_w) ||
								(coords.lat >= min_forbidden_h &&
										coords.lat <= max_forbidden_h))
								continue;
							if (options.required_feature_attribute &&
									!this.features[i].attributes[
										options.required_feature_attribute])
								continue;
							candidates.push(i);
							}

						if (candidates.length) {
							var feature=this.features[candidates[Math.floor(
										Math.random()*candidates.length)]];
							Drupal.openlayers.popup.popupSelect.select(
																feature);
							}
						});
		}
	};
