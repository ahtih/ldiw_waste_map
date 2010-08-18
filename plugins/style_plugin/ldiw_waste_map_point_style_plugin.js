// $Id$

Drupal.openlayers.styleContext.ldiw_waste_map_context=function(parameters) {

	this.getpointRadius=function(feature)
		{
			if (feature.attributes.nr_of_nodes == '') {
				return 2+2*Math.log(feature.attributes.field_diameter_value ?
							feature.attributes.field_diameter_value : 1);
				}
			return 2+2*Math.log(feature.attributes.nr_of_nodes);
			};

	this.getfillColor=function(feature)
		{
			return (feature.attributes.nr_of_nodes &&
									feature.attributes.nr_of_nodes > 1) ?
													'#d07070' : '#ff4040';
			};
	};
