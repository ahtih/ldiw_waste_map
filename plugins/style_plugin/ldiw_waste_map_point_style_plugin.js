// $Id$

Drupal.openlayers.style_plugin.ldiw_waste_map_point_style_plugin=
													function(parameters) {}

Drupal.openlayers.style_plugin.ldiw_waste_map_point_style_plugin.prototype=
{
	'getpointRadius':function(feature)
		{
			return parseInt(Math.min(20,3+3*Math.log(Math.sqrt(
					Math.max(1,feature.attributes.field_volume_value)))));
			},

	'getfillColor':function(feature)
		{
			return (feature.attributes.nr_of_nodes &&
									feature.attributes.nr_of_nodes > 1) ?
													'#d07070' : '#ff4040';
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

	var composition_array=new Array();
	for (var type in composition_map) {
		composition_array.push(Math.max(1,
				parseInt(composition_map[type] * 100 / composition_sum)) +
				'% ' + type);
		}

	if (attrs.field_nr_of_tires_value &&
								attrs.field_nr_of_tires_value != '0') {
		composition_array.push(attrs.field_nr_of_tires_value + ' tires');
		}

	var composition=composition_array.join(', ');
	if (composition) {
		composition='<br>Composition: ' + composition;
		}

	var output='';
	if (attrs.nr_of_nodes && attrs.nr_of_nodes > 1) {
		output=attrs.nr_of_nodes + ' waste points<br>' + 
				'Total volume ' + volume_formatted + 'm&sup3;' +
				composition;
		}
	else {
		output='Volume ' + volume_formatted + 'm&sup3;';
		if (attrs.field_diameter_value) {
			output+='<br>Diameter ' + attrs.field_diameter_value + 'm';
			}
		output+=composition;
		if (attrs.body != '') {
			output+='<br><br>' + attrs.body;
			}
		}

	return '<div class="openlayers-popup">' + output + '</div>';
	}
