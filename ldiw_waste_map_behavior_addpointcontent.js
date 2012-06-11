// $Id$

ldiw_waste_map_coords_form_control=OpenLayers.Class(OpenLayers.Control,{
	type: OpenLayers.Control.TYPE_BUTTON,
	trigger: function() {},

	stop_openlayers_events: function(evt) {
		OpenLayers.Event.stop(evt,true);
		return false;
		},

	draw: function() {
		OpenLayers.Control.prototype.draw.apply(this,arguments);
		$(this.div).stop(true);
		$(this.div).hide();
		OpenLayers.Event.stopObservingElement(this.div);	// Prevent OpenLayers hijacking clicks
		OpenLayers.Event.observe(this.div,"mousedown",
					OpenLayers.Function.bindAsEventListener(
										this.stop_openlayers_events,this));
		return this.div;
		},

	hide_div: function() {
		$(this.div).hide();
		},

	ajax_done: function(response_json) {
		this.addpointcontent_state.remove_addpoint_help();

		$(this.div).stop(true);
		$(this.div).show();

		this.div.innerHTML='';
		if (response_json.error)
			this.div.innerHTML=response_json.error;

		if (response_json.missing_coords_fid) {
			if (!response_json.error)
				this.div.innerHTML+=Drupal.t('This photo is not ' +
						'geotagged, so please enter coordinates manually:');
			this.div.innerHTML+='<p>' +
					'<form class="UploadCoordsForm" method="post">' +
					Drupal.t('Latitude') +
					':<input type="text" name="lat" size="6" maxlength="30">' +
					Drupal.t('Longitude') +
					':<input type="text" name="lon" size="6" maxlength="30">' +
					'<input type="hidden" name="fid" value="' +
						response_json.missing_coords_fid + '">' +
					'<input type="submit" value="' + Drupal.t('Done') + '">' +
					'</form>';
			var form=$(this.div).find('form');
			var obj=this;
			form.submit(function() {
					//!!! Disable submit button until fields are filled in
					$.post(obj.ajax_url,form.serialize(),
									function(data) { obj.ajax_done(data); },
									'json');
					return false;
					});
			}
		else if (!response_json.error) {
			this.map.panTo(new OpenLayers.LonLat(
								response_json.lon,response_json.lat).
							transform(new OpenLayers.Projection('EPSG:4326'),
								this.map.projection));
			if (this.map.getZoom() < 10)
				this.map.zoomTo(10);

			this.div.innerHTML=Drupal.t('Photo added. Thank you for your ' + 
											'contribution to Waste Map!');
			$(this.div).fadeTo(8000,1).fadeOut(1000);
			}
		},

	CLASS_NAME: 'ldiw_waste_map_coords_form_control'
	});

ldiw_waste_map_upload_photo_control=OpenLayers.Class(OpenLayers.Control,{
	type: OpenLayers.Control.TYPE_BUTTON,
	trigger: function() {},

	stop_openlayers_events: function(evt) {
		OpenLayers.Event.stop(evt,true);
		return true;
		},

	draw: function() {
		OpenLayers.Control.prototype.draw.apply(this,arguments);

		this.panel_div.innerHTML="<div class='qq-upload-button' " + 
					"id='file-uploader-button'>" + this.title + "</div>";
		var coords_form_control=this.coords_form_control;
		new qq.FileUploaderBasic({
	        element: this.panel_div,
    	    button: this.panel_div.children[0],
			multiple: false,
	        action: coords_form_control.ajax_url,
			onComplete: function(id,fileName,response_json) {
							coords_form_control.ajax_done(response_json);
							},
			showMessage: function(message) {}
			});

		OpenLayers.Event.stopObservingElement(this.panel_div);	// Prevent OpenLayers hijacking clicks
		OpenLayers.Event.observe(this.panel_div,"mousedown",
					OpenLayers.Function.bindAsEventListener(
										this.stop_openlayers_events,this));
		OpenLayers.Event.observe(this.panel_div,"click",
					OpenLayers.Function.bindAsEventListener(
										this.stop_openlayers_events,this));

		return this.div;
		},

	CLASS_NAME: 'ldiw_waste_map_upload_photo_control'
	});

ldiw_waste_map_layer_switcher=OpenLayers.Class(OpenLayers.Control.Button,{

	eligible_layers: function(map) {
		var dest=[];
		for (var i=0;i < map.layers.length;i++) {
			var layer=map.layers[i];
			if (layer.displayInLayerSwitcher && layer.isBaseLayer)
				dest.push(layer);
			}
		return dest;
		},

	trigger: function() {
		var layers=this.eligible_layers(this.map);
		if (!layers.length)
			return;

		var new_base_layer=layers[0];

		for (var i=0;i+1 < layers.length;i++)
			if (layers[i] == this.map.baseLayer) {
				new_base_layer=layers[i+1];
				break;
				}

		if (new_base_layer)
			this.map.setBaseLayer(new_base_layer);
		},

	CLASS_NAME: 'ldiw_waste_map_layer_switcher'
	});

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

	this.remove_addpoint_help=function()
		{
			if (this.helptext_control)
				this.temp_features_layer.map.removeControl(
													this.helptext_control);
			}

	this.check_display_addpoint_help=function()
		{
			this.coords_form_control.hide_div();
			this.remove_addpoint_help();

			if (this.form_displayed)
				return;

			this.helptext_control=new OpenLayers.Control({
						displayClass: 'ldiw_waste_map_addpoint_help'});
			OpenLayers.Util.extend(this.helptext_control,{
					draw: function () {
						OpenLayers.Control.prototype.draw.apply(this,
																arguments);
						OpenLayers.Event.stopObservingElement(this.div);
									// Prevent OpenLayers hijacking clicks
						this.div.innerHTML=Drupal.t('To add a Waste Point, '+
								'zoom in and click the exact location of ' +
								'the waste on map. Click <em>Move map</em> '+
								'if you want to move the map to correct ' +
								'location beforehand.');
						return this.div;
						}
					});
			this.temp_features_layer.map.addControl(this.helptext_control);
			}

	this.close_form=function()
		{
			this.remove_addpoint_help();

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

			$(this.form_popup.contentDiv).find('.column-side').hide();
						// This hides redundant Save button in Fusion theme

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
			this.form_displayed=true;

			this.remove_addpoint_help();

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

		// Create hidden control for upload photo coordinates form

	this.coords_form_control=new ldiw_waste_map_coords_form_control({
						displayClass: 'ldiw_waste_map_coords_form_control',
						ajax_url: this.options.upload_photo_url,
						addpointcontent_state: this });

	data.openlayers.addControl(this.coords_form_control);
	this.coords_form_control.hide_div();

		// Create temporary features layer

	this.temp_features_layer=new OpenLayers.Layer.Vector(
					Drupal.t('Temporary Features Layer'),
					{projection: new OpenLayers.Projection('EPSG:4326'),
					styleMap: new OpenLayers.StyleMap(
								{'default':data.map.styles.temporary}),
					displayInLayerSwitcher: false
					});
	data.openlayers.addLayer(this.temp_features_layer);

		// Create panel with mode switching buttons

	var invisible_stylemap=new OpenLayers.StyleMap(
									new OpenLayers.Style({pointRadius:0}));
	this.drawfeature_control=new OpenLayers.Control.DrawFeature(
						this.temp_features_layer,
						OpenLayers.Handler.Point,
						{displayClass: 'olControlDrawFeaturePoint',
						title: Drupal.t('Add/Edit Waste Point'),
						handlerOptions: {layerOptions:{
											styleMap: invisible_stylemap}}}
						);
	var panel=new OpenLayers.Control.Panel();
	var controls=[		new OpenLayers.Control.Navigation({
								title: Drupal.t('Move map')}),
						this.drawfeature_control,
						new ldiw_waste_map_upload_photo_control({
							title: Drupal.t('Upload geotagged photo'),
							displayClass: 'WasteMapButton',
							coords_form_control: this.coords_form_control})];

	if (ldiw_waste_map_layer_switcher.prototype.eligible_layers(
											data.openlayers).length >= 2)
		controls.push(new ldiw_waste_map_layer_switcher({
									title: Drupal.t('Switch map type'),
									displayClass: 'WasteMapButton'}));
	panel.addControls(controls);

	panel.defaultControl=panel.controls[0];

	for (var i=0;i < panel.controls.length;i++)
		$(panel.controls[i].panel_div).text(panel.controls[i].title);

	this.drawfeature_control.events.register('activate',this,
										this.check_display_addpoint_help);
	this.drawfeature_control.events.register('deactivate',this,
														this.close_form);
	this.temp_features_layer.events.register('sketchcomplete',this,
														this.sketchcomplete);
	this.temp_features_layer.events.register('featureadded',this,
														this.draw_menu);

		// Workaround for http://trac.osgeo.org/openlayers/ticket/2745

	OpenLayers.Util.extend(panel,{
			redraw: function () {
				if (this.div.children.length > 0)
					for (var l=this.div.children.length,i=l-1;i >= 0;i--)
						this.div.removeChild(this.div.children[i]);
				OpenLayers.Control.Panel.prototype.redraw.apply(this,
																arguments);
				}});

	data.openlayers.addControl(panel);
	if (OpenLayers.Util.getBrowserName() != 'firefox' ||
						(navigator.userAgent.indexOf('Firefox/1') < 0 &&
						navigator.userAgent.indexOf('Firefox/2') < 0)) {
		data.openlayers.layerContainerDiv.style.zIndex=
				(OpenLayers.Util.getBrowserName() == 'msie' &&
						(navigator.userAgent.indexOf('MSIE 6') >= 0 ||
						navigator.userAgent.indexOf('MSIE 7') >= 0)) ?
															null : 'auto';
		panel.div.style.zIndex=data.openlayers.Z_INDEX_BASE['Popup']-1;
		}
	panel.activate();
	panel.redraw();

		// Make sure that popupSelect is before panel in listeners[]
		//   list, otherwise popups do not work after panning map

	Drupal.openlayers.popup.popupSelect.deactivate();
	Drupal.openlayers.popup.popupSelect.activate();

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
	this.hover_control.handlers.feature.stopDown=false;
	this.hover_control.handlers.feature.stopUp=false;

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
