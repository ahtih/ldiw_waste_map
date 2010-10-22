// $Id$

Drupal.openlayers.style_plugin.ldiw_waste_map_point_style_plugin=
													function(parameters) {}

Drupal.openlayers.style_plugin.ldiw_waste_map_point_style_plugin.prototype=
{
	calc_pointRadius:function(feature)
		{
			return parseInt(Math.min(20,4+3*Math.log(Math.sqrt(
					Math.max(1,feature.attributes.field_volume_value)))));
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

	parse_composition:function(attrs)
		{
			//!!! compute this only once
			//!!! make colors and fields configurable
			var composition=[
					['e41e2f',parseFloat(
							attrs.field_composition_dangerous_value || 0)],
					['f7c16b',parseFloat(
							attrs.field_composition_construction_value || 0)],
					['3ab54a',parseFloat(
							attrs.field_composition_biodegradable_value || 0)],
					['38439c',parseFloat(
								attrs.field_composition_other_value || 0) +
							parseFloat(
								attrs.field_composition_large_value || 0)]];
			composition.sort(function(a,b){return a[1]-b[1]});

			while (composition.length && composition[0][1] <= 0)
				composition.shift();

			return composition;
			},

	calc_externalGraphic:function(feature)
		{
			var composition=this.parse_composition(feature.attributes);
			if (composition.length < 2)
				return '';

			var composition_sum=0;
			for (var i=0;i < composition.length;i++)
				composition_sum+=composition[i][1];

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

			return Drupal.settings.ldiw_waste_map_point_style_plugin_icons_base_url +
					composition.join('_') + '.png';
			},

	calc_fillColor:function(feature)
		{
			var composition=this.parse_composition(feature.attributes);
			if (composition.length > 1)
				return '';

			if (!composition.length)
				return '#a0a0a0';

			return '#' + composition[0][0];
			},
	};

Drupal.theme.openlayersPopup=function(feature)
{
	var attrs=feature.attributes;

	var coeff=attrs.field_volume_value >= 5 ? 1 : 10;
	var volume_formatted=Math.round(attrs.field_volume_value * coeff) / coeff;

	var composition_map={};
	var composition_sum=0;
	for (var attrname in attrs) {
		var type=attrname.replace(/^field_composition_(.*)_value/,'$1');
		if (type != attrname && attrs[attrname]) {
			var value=parseFloat(attrs[attrname]);
			if (value > 0) {
				composition_map[type]=value;
				composition_sum+=value;
				}
			}
		}

	var composition_array=[];
	for (var type in composition_map)
		composition_array.push(Math.max(1,
				parseInt(composition_map[type] * 100 / composition_sum)) +
				'% ' + type);

	if (attrs.field_nr_of_tires_value &&
								attrs.field_nr_of_tires_value != '0')
		composition_array.push(attrs.field_nr_of_tires_value + ' tires');

	var composition=composition_array.join(', ');
	if (composition)
		composition='<br>Composition: ' + composition;

	var output='';
	if (attrs.nr_of_nodes && attrs.nr_of_nodes > 1) {
		output=attrs.nr_of_nodes + ' waste points<br>' + 
				'Total volume ' + volume_formatted + 'm&sup3;' +
				composition;
		}
	else {
		output='Volume ' + volume_formatted + 'm&sup3;';
		if (attrs.field_diameter_value)
			output+='<br>Diameter ' + attrs.field_diameter_value + 'm';
		output+=composition;
		if (attrs.body != '')
			output+='<br><br>' + attrs.body;
		}

	return '<div class="openlayers-popup">' + output + '</div>';
	}
