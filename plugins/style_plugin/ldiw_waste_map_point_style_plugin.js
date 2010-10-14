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

	var output='';
	if (attrs.nr_of_nodes && attrs.nr_of_nodes > 1) {
		output=attrs.nr_of_nodes + ' waste points<br>' + 
				'Total volume ' + volume_formatted + 'm&sup3;';
		if (attrs.field_nr_of_tires_value != '' &&
								attrs.field_nr_of_tires_value != '0') {
			output+='<br>Contains ' + attrs.field_nr_of_tires_value +
																' tires';
			}
		}
	else {
		output='Volume ' + volume_formatted + 'm&sup3;';
		if (attrs.field_diameter_value != '') {
			output+='<br>Diameter ' + attrs.field_diameter_value + 'm';
			}
		if (attrs.field_nr_of_tires_value != '' &&
								attrs.field_nr_of_tires_value != '0') {
			output+='<br>Contains ' + attrs.field_nr_of_tires_value +
																' tires';
			}
		if (attrs.body != '') {
			output+='<br><br>' + attrs.body;
			}
		}

	return '<div class="openlayers-popup">' + output + '</div>';
	}
