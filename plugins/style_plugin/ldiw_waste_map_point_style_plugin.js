// $Id$

Drupal.openlayers.styleContext.ldiw_waste_map_context=function(parameters) {

	this.getpointRadius=function(feature)
		{
			return 2+2*Math.log(feature.attributes.field_diameter_value ?
							feature.attributes.field_diameter_value : 1);
			};

	this.getfillColor=function(feature)
		{
			return (feature.attributes.nr_of_nodes &&
									feature.attributes.nr_of_nodes > 1) ?
													'#d07070' : '#ff4040';
			};
	};

Drupal.theme.openlayersPopup=function(feature)
{
	var output='';
	if (feature.attributes.nr_of_nodes &&
									feature.attributes.nr_of_nodes > 1) {
		output=feature.attributes.nr_of_nodes + ' waste points';
		if (feature.attributes.field_nr_of_tires_value != '' &&
					feature.attributes.field_nr_of_tires_value != '0') {
			output+='<br>Contains ' +
							feature.attributes.field_nr_of_tires_value +
							' tires';
			}
		}
	else {
		output='Diameter ' + feature.attributes.field_diameter_value +
																	'm';
		if (feature.attributes.field_nr_of_tires_value != '' &&
					feature.attributes.field_nr_of_tires_value != '0') {
			output+='<br>Contains ' +
							feature.attributes.field_nr_of_tires_value +
							' tires';
			}
		if (feature.attributes.body != '') {
			output+='<br><br>' + feature.attributes.body;
			}
		}

	return '<div class="openlayers-popup">' + output + '</div>';
	}
