// $Id$

Drupal.theme.prototype.openlayersAddPointContentNoNodeID=function(feature)
{
	return Drupal.t('Selected feature has no Node ID to edit');
	}

function ldiw_waste_map_behavior_addpointcontent_state(data,options)
{
	this.restart_editing_mode=function()
		{
				// Re-activate drawfeature_control so that it remains
				//   at top priority in event listeners list.
				// This also triggers this.close_form()

			this.drawfeature_control.deactivate();
			this.drawfeature_control.activate();
			}

	this.close_form=function()
		{
			if (this.form_popup) {
				this.temp_features_layer.map.removePopup(this.form_popup);
				this.form_popup=null;
				}

			this.temp_features_layer.removeFeatures(
										this.temp_features_layer.features);

			this.hover_control.activate();

			if (this.hover_control.last_highlighted_feature) {
				this.hover_control.unhighlight(
							this.hover_control.last_highlighted_feature);
				}
			}

	this.process_form_response=function(data)
		{
			var doc=jQuery('<div />').append(data);
			if (doc.find('#node-form,#node-delete-confirm').length) {
					// New form was returned, thus either form validation
					//  failed or delete needs confirmation.
					//  Show the new form then
				var form=doc.find('form:first').parent().children().
							not('.breadcrumb,.title,#tabs-wrapper,#footer');
				form.find('a[href*="formfilter_id="]').css('display','none');
				$(this.form_popup.contentDiv).html(form);
				this.fixup_form();

					// Scroll form to beginning to ensure that
					//   error messages are visible
				this.form_popup.contentDiv.scrollTop=0;
				}
			else {
					// Form submission was successful

				var layers_to_refresh=this.temp_features_layer.map.
						getLayersBy('drupalID',this.options.features_layer);
				for (var i in layers_to_refresh) {
					layers_to_refresh[i].events.triggerEvent(
												"refresh",{force:true});
					}
				this.restart_editing_mode();
				}
			}

	this.fixup_form=function()
		{
			var coords_map={	//!!! Remove hardcoding of field_coords
					'field_coords[0][geo][lon]':
								this.coords_to_set_in_form &&
											this.coords_to_set_in_form.lon,
					'field_coords[0][geo][lat]':
								this.coords_to_set_in_form &&
											this.coords_to_set_in_form.lat};
			for (var fieldname in coords_map) {
				var node=$(this.form_popup.contentDiv).find(
											"[name='" + fieldname + "']");
				if (node.length) {
					if (this.coords_to_set_in_form) {
						node.attr('value',coords_map[fieldname]);
						}
					node.parents('.form-item').hide();
					}
				}

			$(this.form_popup.contentDiv).prepend(
					'<b>' + this.form_title + '</b>'); //!!! Move style to CSS

			Drupal.attachBehaviors(this.form_popup.contentDiv);

			var state=this;
			$(this.form_popup.contentDiv).find(':submit').click(function()
						// This is also triggered when submitting the form
						//   via keyboard, not just via click
				{ state.submit_attribute=this.name+'='+this.value + '&'; });

			$(this.form_popup.contentDiv).find('form').submit(function()
				{
					$.post(this.action,
							state.submit_attribute + $(this).serialize(),
							function(data) {
								state.process_form_response(data);
								},
							'html');
					return false;
					});
			}

	this.sketchcomplete=function()
		{
			return !this.form_popup;
			}

	this.draw_menu=function(args)
		{
			var layer=args.object;
			var coords=args.feature.geometry.getBounds().getCenterLonLat();

			var form_url=this.options.node_base_url;

			var feature_to_edit=this.hover_control.last_highlighted_feature;
			if (feature_to_edit && feature_to_edit.renderIntent == 'select') {
				layer.removeFeatures(layer.features);

				var node_id=feature_to_edit.attributes.id; //!!! Remove hardcoding of .id
				if (isNaN(node_id)) {
					var popup_text=Drupal.theme(
									'openlayersAddPointContentNoNodeID',
									feature_to_edit);
					if (popup_text)
						layer.map.addPopup(
							new OpenLayers.Popup.FramedCloud(
								'ldiw_waste_map_behavior_addpointcontent_no_node_id',
								coords,null,popup_text,null,true),
							true);
					return;
					}
				form_url+=node_id + '/edit';

				this.form_title=Drupal.t('Edit existing @type',
								{'@type':this.options.content_type_name});
				this.coords_to_set_in_form=null;
				}
			else {
				form_url+='add/' + this.options.content_type.replace('_','-');
				this.form_title=Drupal.t('Add new @type',
								{'@type':this.options.content_type_name});
				this.coords_to_set_in_form=coords.clone().transform(
								layer.map.getProjectionObject(),
								new OpenLayers.Projection('EPSG:4326'));
				}

			var state=this;
			this.form_popup=new OpenLayers.Popup.FramedCloud(
					'ldiw_waste_map_behavior_addpointcontent_form',
					coords,null,Drupal.t('Loading...'),null,true,
					function(e)
						{
							state.restart_editing_mode();
							OpenLayers.Event.stop(e);
							}
					);
			this.form_popup.panMapIfOutOfView=false;
								// Avoid layer refresh which would
								//   un-select the feature we clicked on
			this.hover_control.deactivate();

				//!!! Deactivate map navigation (zoom, pan, ...) which would trigger
				//  a layer refresh and thus un-select the feature we clicked on

				// Fetch form content using AJAX

			var state=this;
			$(this.form_popup.contentDiv).load(
					form_url + ' #node-form',null,
					function() {
						state.fixup_form();
						state.form_popup.updateSize();
						});

			args.feature.popup=this.form_popup;
			layer.map.addPopup(this.form_popup,true);
			}

		/***********************/
		/*****             *****/
		/***** Constructor *****/
		/*****             *****/
		/***********************/

	this.options=options;
	this.form_popup=null;

		// Create temporary features layer

	this.temp_features_layer=new OpenLayers.Layer.Vector(
					Drupal.t('Temporary Features Layer'),
					{projection: new OpenLayers.Projection('EPSG:4326'),
					styleMap: new OpenLayers.StyleMap(
								{'default':data.map.styles.temporary})
					});
	data.openlayers.addLayer(this.temp_features_layer);

		// Create panel with mode switching buttons

	var invisible_stylemap=new OpenLayers.StyleMap(
									new OpenLayers.Style({pointRadius:0}));
	this.drawfeature_control=new OpenLayers.Control.DrawFeature(
						this.temp_features_layer,
						OpenLayers.Handler.Point,
						{'displayClass':'olControlDrawFeaturePoint',
						'title':Drupal.t('Add/Edit Waste Point'),
						'handlerOptions':{layerOptions:{
											styleMap:invisible_stylemap}}}
						);
	var panel=new OpenLayers.Control.Panel();
	panel.addControls([	new OpenLayers.Control.Navigation(
							{'title':Drupal.t('Move map')}),
							this.drawfeature_control]);
	panel.defaultControl=panel.controls[0];

	for (var i=0;i < panel.controls.length;i++) {
		$(panel.controls[i].panel_div).text(panel.controls[i].title);
		}

	this.drawfeature_control.events.register('deactivate',this,
														this.close_form);
	this.temp_features_layer.events.register('sketchcomplete',this,
														this.sketchcomplete);
	this.temp_features_layer.events.register('featureadded',this,
														this.draw_menu);

	data.openlayers.addControl(panel);
	if (OpenLayers.Util.getBrowserName() != 'firefox' ||
						(navigator.userAgent.indexOf('Firefox/1') < 0 &&
						navigator.userAgent.indexOf('Firefox/2') < 0)) {
		data.openlayers.layerContainerDiv.style.zIndex=null;
		panel.div.style.zIndex=data.openlayers.Z_INDEX_BASE['Popup']-1;
		}
   	panel.activate();
   	panel.redraw();

		// Create control to highlight existing points on hover

	this.hover_control=new OpenLayers.Control.SelectFeature(
			data.openlayers.getLayersBy('drupalID',
											this.options.features_layer),
			{hover: true,
				onBeforeSelect: function(feature)
					{
						this.highlight(feature);
						this.last_highlighted_feature=feature;

							// Hack to work around problems caused by
							//   popupSelect and hover_control sharing the
							//   same layer.selectedFeatures[] object

						Drupal.openlayers.popup.popupSelect.onBeforeSelect=
								function() {
									for (var i=this.map.popups.length-1;
																i >= 0;i--)
										this.map.removePopup(
														this.map.popups[i]);
									}

						return false; // Prevent actual select from happening
						}
				});

		// Prevent hover_control hijacking clicks

	this.hover_control.handlers.feature.stopClick=false;

	data.openlayers.addControl(this.hover_control);
	this.hover_control.activate();
	}

Drupal.behaviors.ldiw_waste_map_behavior_addpointcontent=function(context)
{
	var data=$(context).data('openlayers');
	if (data && data.map.behaviors['ldiw_waste_map_behavior_addpointcontent']) {
		new ldiw_waste_map_behavior_addpointcontent_state(data,
			data.map.behaviors['ldiw_waste_map_behavior_addpointcontent']);
		}
	};
