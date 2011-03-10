<?php
// $Id

function _waste_point_html_separator()
{
	foreach (func_get_args() as $arg) {
		if (empty($arg)) {
			return '';
			}
		}
	return "<hr>\n";
	}

function _waste_point_html_section($class_name,$label,$values)
{
	if (empty($values)) {
		return '';
		}

	$output="<span class='${class_name}'>\n" .
			"\t<div class='field_label'>${label}:</div>\n";
	foreach ($values as $value) {
		$output.="\t<div class='value";
		if (is_array($value)) {
			$output.=" ${value[0]}";
			$value=$value[1];
			}
		$output.="'>${value}</div>\n";
		}
	$output.="</span>\n\n";

	return $output;
	}

//!!! Move this to theme system

function _waste_point_html($attrs,$photos,$max_width_pixels,
													$language_code=NULL)
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
			$composition_array[]=array($attrname,$info,$attrs[$attrname]);
			$composition_sum+=$attrs[$attrname];
			}
		}

	foreach ($composition_array as $key => $entry) {
		list($attrname,$info,$value)=$entry;
		$text=$info['text'];
		if (count($composition_array) == 1 && !empty($info['text_solo'])) {
			$text=$info['text_solo'];
			}
		else {
			$text=max(1,round($value*100 / $composition_sum)) . "% ${text}";
			}
		$composition_array[$key]=array($attrname,$text);
		}

	if (!empty($attrs['nr_of_tires'])) {
		$composition_array[]=array('tires',t('@nr_of_tires tires',
							array('@nr_of_tires' => $attrs['nr_of_tires']),
							$language_code));
		}

	$composition=_waste_point_html_section('composition',
				t('Composition',array(),$language_code),$composition_array);

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
		return _waste_point_html_section('cluster_nodes',
						t('Cluster',array(),$language_code),
						array(t('@nr_of_points waste points',array(
							'@nr_of_points' => $attrs['nr_of_nodes']),
							$language_code))) .
				_waste_point_html_separator() .
				_waste_point_html_section('volume',
							t('Total volume',array(),$language_code),
							array("${volume_formatted}m&sup3;")) .
				_waste_point_html_separator() .
				$composition;
		}

	$output='';

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

	if ($volume_formatted) {
		$output.=_waste_point_html_separator($output) .
				_waste_point_html_section('volume',
									t('Volume',array(),$language_code),
									array("${volume_formatted}m&sup3;"));
		}

	$output.=_waste_point_html_section('id',t('ID',array(),$language_code),
											array($attrs['id']));

	$output.=_waste_point_html_separator($output,$composition) . $composition;

	if (!empty($attrs['description'])) {
		$output.=_waste_point_html_separator($output) .
				_waste_point_html_section('description',
						t('Description',array(),$language_code),
						array(mb_convert_encoding($attrs['description'],
												'HTML-ENTITIES','UTF-8')));
		}

	if (!empty($attrs['geo_areas_json'])) {
		$areas_array=array();
		foreach (json_decode($attrs['geo_areas_json'],TRUE) as
													$hierarchy => $areas) {
			$areas_array[]=mb_convert_encoding("$hierarchy: $areas",
												'HTML-ENTITIES','UTF-8');
			}
		$output.=_waste_point_html_separator($output,$areas_array) .
				_waste_point_html_section('geographic_areas',
						t('Location',array(),$language_code),$areas_array);
		}

	return $output;
	}
?>
