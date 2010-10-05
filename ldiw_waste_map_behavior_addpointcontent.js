// $Id$

function ldiw_waste_map_behavior_addpointcontent_fixup_form(
								popup,temp_features_layer,options,coords)
{
	var coords_map={'field_coords[0][geo][lon]': coords.lon,
					'field_coords[0][geo][lat]': coords.lat};
	for (var fieldname in coords_map) {
		var node=$(popup.contentDiv).find("[name='" + fieldname + "']");
		node.attr('value',coords_map[fieldname]);
		node.parents('.form-item').hide();
		}

	Drupal.attachBehaviors(popup.contentDiv);
	$(popup.contentDiv).find('#node-form').submit(function()
		{
			$.post(this.action,$(this).serialize(),
					function(data)
						{
							var doc=jQuery('<div />').append(data);
							if (doc.find('#node-form').length) {
									// New form was returned, thus form
									//  validation probably failed. Show the
									//  new form then
								$(popup.contentDiv).html(
										doc.find('.messages, .messages ~'));
								ldiw_waste_map_behavior_addpointcontent_fixup_form(
										popup,temp_features_layer,
										options,coords);

									// scroll form to beginning to ensure
									//   that error message is visible
								popup.contentDiv.scrollTop=0;
								}
							else {
									// Form submission was successful

								var layers_to_refresh=temp_features_layer.
										map.getLayersBy('drupalID',
												options.layer_to_refresh);
								for (var i in layers_to_refresh) {
									layers_to_refresh[i].events.triggerEvent(
													"refresh",{force:true});
									}
								temp_features_layer.map.removePopup(popup);
								temp_features_layer.removeFeatures(
											temp_features_layer.features);
								}
							},
					'html');
			return false;
			});
	}

function ldiw_waste_map_behavior_addpointcontent_drawmenu(args)
{
	var options=this;	// Drupal options form values are in "this"
	var layer=args.object;
	var coords=args.feature.geometry.getBounds().getCenterLonLat();

	var popup=new OpenLayers.Popup.FramedCloud(
			'ldiw_waste_map_behavior_addpointcontent_form',
			coords,null,
			'Loading...',
			null,true,
			function(e)
				{
					layer.removeFeatures(layer.features);
					this.hide();
					OpenLayers.Event.stop(e);
					}
			);

		// Remove all temp layer features except the current one

	for (var i=layer.features.length-1;i >= 0;i--) {
		if (layer.features[i] != args.feature) {
			layer.removeFeatures(Array(layer.features[i]));
			}
		}

		// Fetch form content using AJAX

	var form_url='/node/add/' + options.content_type.replace('_','-');
	$(popup.contentDiv).load(form_url + ' #node-form',null,
			function() {
				ldiw_waste_map_behavior_addpointcontent_fixup_form(
						popup,layer,options,
						coords.clone().transform(
							layer.map.getProjectionObject(),
							new OpenLayers.Projection('EPSG:4326')));
				popup.updateSize();
				});

	args.feature.popup=popup;
	layer.map.addPopup(popup,true);
	}

Drupal.behaviors.ldiw_waste_map_behavior_addpointcontent=function(context)
{
	var data=$(context).data('openlayers');
	if (data && data.map.behaviors['ldiw_waste_map_behavior_addpointcontent']) {

		var options=
				data.map.behaviors['ldiw_waste_map_behavior_addpointcontent'];

			// Create temporary features layer

		var temp_features_layer_options={
			projection: new OpenLayers.Projection('EPSG:4326'),
			drupalID: 'ldiw_waste_map_addpointcontent_layer'
			};
		var temp_features_layer=new OpenLayers.Layer.Vector(
							Drupal.t("Temporary Features Layer"),
							temp_features_layer_options);
		temp_features_layer.styleMap=Drupal.openlayers.getStyleMap(
							data.map,temp_features_layer_options.drupalID);
		data.openlayers.addLayer(temp_features_layer);

			// Create panel with mode switching buttons

		var panel=new OpenLayers.Control.Panel();
		panel.addControls([
				new OpenLayers.Control.Navigation(),
				new OpenLayers.Control.DrawFeature(
						temp_features_layer,
						OpenLayers.Handler.Point,
						{'displayClass':'olControlDrawFeaturePoint'})]);
		panel.defaultControl=panel.controls[0];

		temp_features_layer.events.register('featureadded',options,
						ldiw_waste_map_behavior_addpointcontent_drawmenu);

		data.openlayers.addControl(panel);
    	panel.activate();
    	panel.redraw();
		}
	};
