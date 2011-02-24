<?php
// $Id

function _waste_point_html($attrs,$photos,$max_width_pixels)
{
		/****************************/
		/*****                  *****/
		/***** Set $composition *****/
		/*****                  *****/
		/****************************/

	$composition_array=array();
	$composition_sum=0;
	foreach (variable_get('ldiw_waste_map_composition_fields',array())
												as $fieldname => $info) {
		$attrname=preg_replace('/^field_/','',$fieldname);
		if (!empty($attrs[$attrname])) {
			$composition_array[]=array($info,$attrs[$attrname]);
			$composition_sum+=$attrs[$attrname];
			}
		}

	foreach ($composition_array as $key => $entry) {
		list($info,$value)=$entry;
		$text=$info['text'];
		if (count($composition_array) == 1 && !empty($info['text_solo'])) {
			$text=$info['text_solo'];
			}
		$composition_array[$key]=
							max(1,round($value*100 / $composition_sum)) .
														'%&nbsp;' . $text;
		}

	if (!empty($attrs['nr_of_tires']))
		$composition_array[]=$attrs['nr_of_tires'] . ' tires';

	$composition=implode(', ',$composition_array);
	if ($composition) {
		$composition='<br>Composition: ' . $composition;
		}

		/*********************************/
		/*****                       *****/
		/***** Set $volume_formatted *****/
		/*****                       *****/
		/*********************************/

	$volume_formatted=NULL;
	if (!empty($attrs['volume'])) {
		$volume_formatted=sprintf(($attrs['volume'] >= 5 ? '%.0f' : '%.1f'),
														$attrs['volume']);
		if ($volume_formatted == '0') {
			$volume_formatted='0.1';
			}
		}

		/***********************/
		/*****             *****/
		/***** Set $output *****/
		/*****             *****/
		/***********************/

	if (!empty($attrs['nr_of_nodes']) && $attrs['nr_of_nodes'] > 1) {
		return '</div>' . $attrs['nr_of_nodes'] . ' waste points<br>' .
				'Total volume ' . $volume_formatted . 'm&sup3;' .
				$composition;
		}

	$output='';
	if ($volume_formatted) {
		$output.='Volume <b>' . $volume_formatted . 'm&sup3;</b>';
		}

	$output.=$composition;

	if (!empty($attrs['geo_areas_json'])) {
		foreach (json_decode($attrs['geo_areas_json'],TRUE) as
													$hierarchy => $areas) {
			$output.='<br>' . mb_convert_encoding("$hierarchy: $areas",
												'HTML-ENTITIES','UTF-8');
			}
		}

	if (!empty($attrs['description'])) {
		$output.='<br><br>' . mb_convert_encoding($attrs['description'],
												'HTML-ENTITIES','UTF-8');
		}

	foreach ($photos as $photo) {
		list($id,,$serialized_data)=$photo;

		$width=empty($serialized_data['width']) ?
										400 : $serialized_data['width'];
		$height=empty($serialized_data['height']) ?
										0 : $serialized_data['height'];
		if ($width > $max_width_pixels) {
			$height=round($max_width_pixels * $height / $width);
			$width=$max_width_pixels;
			}

		$url=empty($serialized_data['url']) ?
						url('ldiw_waste_map',array('absolute' => TRUE)) .
										'/photo/' . $attrs['id'] . "/$id" :
						$serialized_data['url'];

		$html='<img src="' . $url . '" width="' . $width . '"';
		if ($height) {
			$html.=' height="' . $height . '"';
			}
		$html.='/>';

		if (!empty($serialized_data['link_url'])) {
			$html='<a href="' . $serialized_data['link_url'] .
													'">' . $html . '</a>';
			}
		$html="<div>$html</div>";
		if (!empty($serialized_data['attribution_html'])) {
			$html.='<div>' . mb_convert_encoding(
									$serialized_data['attribution_html'],
									'HTML-ENTITIES','UTF-8') . '</div>';
			}

		$output.=$html;
		}

	return $output;
	}
?>
