// $Id$

function ldiw_waste_map_behavior_addpointcontent_close_form(layer,options)
{
	layer.map.removePopup(options.form_popup);
	options.form_popup=null;

	layer.removeFeatures(layer.features);

	options.hover_control.activate();

		// Re-activate drawfeature_control so that it remains
		//   at top priority in event listeners list

	options.drawfeature_control.deactivate();
	options.drawfeature_control.activate();

	if (options.hover_control.last_highlighted_feature) {
		options.hover_control.unhighlight(
							options.hover_control.last_highlighted_feature);
		}
	}

function ldiw_waste_map_behavior_addpointcontent_fixup_form(
						popup,title,temp_features_layer,options,coords)
{
	var coords_map={	//!!! Remove hardcoding of field_coords
			'field_coords[0][geo][lon]': coords && coords.lon,
			'field_coords[0][geo][lat]': coords && coords.lat};
	for (var fieldname in coords_map) {
		var node=$(popup.contentDiv).find("[name='" + fieldname + "']");
		if (node.length) {
			if (coords) {
				node.attr('value',coords_map[fieldname]);
				}
			node.parents('.form-item').hide();
			}
		}

	$(popup.contentDiv).prepend('<b>' + title + '</b>');
												//!!! Move style to CSS

	Drupal.attachBehaviors(popup.contentDiv);

	$(popup.contentDiv).find(':submit').click(function()
		{
				// This is also triggered when submitting the form via
				//   keyboard, not just via click
			$(this.form).data('submit-attribute',
									this.name + '=' + this.value + '&');
			});

	$(popup.contentDiv).find('form').submit(function()
		{
			$.post(this.action,
					$(this).data('submit-attribute') + $(this).serialize(),
					function(data)
						{
							var doc=jQuery('<div />').append(data);
							if (doc.find('#node-form,#node-delete-confirm').
																length) {
									// New form was returned, thus form
									//  validation probably failed or
									//  delete needs confirmation. Show the
									//  new form then
								var form=doc.find('.left-corner > *').
									not('.breadcrumb,#tabs-wrapper,#footer');
								$(popup.contentDiv).html(form);
								ldiw_waste_map_behavior_addpointcontent_fixup_form(
										popup,title,temp_features_layer,
										options,coords);

									// scroll form to beginning to ensure
									//   that error messages are visible
								popup.contentDiv.scrollTop=0;
								}
							else {
									// Form submission was successful

								var layers_to_refresh=temp_features_layer.
										map.getLayersBy('drupalID',
												options.features_layer);
								for (var i in layers_to_refresh) {
									layers_to_refresh[i].events.triggerEvent(
													"refresh",{force:true});
									}
								ldiw_waste_map_behavior_addpointcontent_close_form(
													temp_features_layer,options);
								}
							},
					'html');
			return false;
			});
	}

function ldiw_waste_map_behavior_addpointcontent_sketchcomplete(args)
{
	return !this.form_popup;
	}

function ldiw_waste_map_behavior_addpointcontent_drawmenu(args)
{
	var options=this;	// Drupal options form values are in "this"
	var layer=args.object;
	var coords=args.feature.geometry.getBounds().getCenterLonLat();

	var form_url;
	var form_title;
	var coords_to_set_in_form;

	var feature_to_edit=options.hover_control.last_highlighted_feature;
	if (feature_to_edit && feature_to_edit.renderIntent == 'select') {
		layer.removeFeatures(layer.features);

		var node_id=feature_to_edit.fid;	//!!! Remove hardcoding of .fid
		if (isNaN(node_id)) {
			return;
			}
		form_url='/node/' + node_id + '/edit';

		form_title=Drupal.t('Edit existing @type',
								{'@type':options.content_type_name});
		}
	else {
		form_url='/node/add/' + options.content_type.replace('_','-');
		form_title=Drupal.t('Add new @type',
								{'@type':options.content_type_name});
		coords_to_set_in_form=coords.clone().transform(
								layer.map.getProjectionObject(),
								new OpenLayers.Projection('EPSG:4326'));
		}

	options.form_popup=new OpenLayers.Popup.FramedCloud(
			'ldiw_waste_map_behavior_addpointcontent_form',
			coords,null,'Loading...',null,true,
			function(e)
				{
					ldiw_waste_map_behavior_addpointcontent_close_form(
															layer,options);
					OpenLayers.Event.stop(e);
					}
			);
	options.form_popup.panMapIfOutOfView=false;	// Avoid layer refresh which
												//   would un-select the
												//   feature we clicked on
	options.hover_control.deactivate();

		//!!! Deactivate map navigation (zoom, pan, ...) which would trigger
		//  a layer refresh and thus un-select the feature we clicked on

		// Fetch form content using AJAX

	$(options.form_popup.contentDiv).load(form_url + ' #node-form',null,
			function() {
				ldiw_waste_map_behavior_addpointcontent_fixup_form(
									options.form_popup,form_title,layer,
									options,coords_to_set_in_form);
				options.form_popup.updateSize();
				});

	args.feature.popup=options.form_popup;
	layer.map.addPopup(options.form_popup,true);
	}

Drupal.behaviors.ldiw_waste_map_behavior_addpointcontent=function(context)
{
	var data=$(context).data('openlayers');
	if (data && data.map.behaviors['ldiw_waste_map_behavior_addpointcontent']) {

		var options=
				data.map.behaviors['ldiw_waste_map_behavior_addpointcontent'];

			// Create temporary features layer

		var temp_features_layer=new OpenLayers.Layer.Vector(
					Drupal.t('Temporary Features Layer'),
					{projection: new OpenLayers.Projection('EPSG:4326'),
					styleMap: new OpenLayers.StyleMap(
								{'default':data.map.styles.temporary}),
					});
		data.openlayers.addLayer(temp_features_layer);

			// Create panel with mode switching buttons

		var invisible_stylemap=new OpenLayers.StyleMap(
									new OpenLayers.Style({pointRadius:0}));
		options.drawfeature_control=new OpenLayers.Control.DrawFeature(
						temp_features_layer,
						OpenLayers.Handler.Point,
						{'displayClass':'olControlDrawFeaturePoint',
						'handlerOptions':{layerOptions:{
											styleMap:invisible_stylemap}}}
						);
		var panel=new OpenLayers.Control.Panel();
		panel.addControls([	new OpenLayers.Control.Navigation(),
							options.drawfeature_control]);
		panel.defaultControl=panel.controls[0];

		//!!! on selecting Navigation, close options.form_popup

		temp_features_layer.events.register('sketchcomplete',options,
					ldiw_waste_map_behavior_addpointcontent_sketchcomplete);
		temp_features_layer.events.register('featureadded',options,
					ldiw_waste_map_behavior_addpointcontent_drawmenu);

		data.openlayers.addControl(panel);
    	panel.activate();
    	panel.redraw();

			// Create control to highlight existing points on hover

		options.hover_control=new OpenLayers.Control.SelectFeature(
			data.openlayers.getLayersBy('drupalID',options.features_layer),
			{hover: true,
				onBeforeSelect: function(feature)
					{
						this.highlight(feature);
						this.last_highlighted_feature=feature;
						return false; // Prevent actual select from happening
						}
				});

			// Prevent hover_control hijacking clicks

		options.hover_control.handlers.feature.stopClick=false;

		data.openlayers.addControl(options.hover_control);
		options.hover_control.activate();
		}
	};
