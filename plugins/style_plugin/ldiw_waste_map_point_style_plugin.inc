<?php
// $Id$

// Define plugin for CTools
$plugin = array(
	'title' => t('Waste point style plugin'),
	'description' => t('Waste point style plugin'),
	'style_plugin' => array(
		'class' => 'openlayers_style_plugin_point_style_plugin',
		'parent' => 'openlayers_style_plugin'),
	);

//!!! hook_requirements()'is kontrollida, kas openlayers_style_plugin on olemas

class openlayers_style_plugin_point_style_plugin
										extends openlayers_style_plugin {
	function get_context_properties()
		{
			return array(
				'pointRadius' => 'calc_pointRadius',
				'fillColor' => 'calc_fillColor',
				'externalGraphic' => 'calc_externalGraphic',
				'backgroundWidth' => 'calc_backgroundWidth',
				'backgroundHeight' => 'calc_backgroundHeight',
				'backgroundXOffset' => 'calc_backgroundXOffset',
				'backgroundYOffset' => 'calc_backgroundYOffset',
				);
			}

	function render()
		{
			drupal_add_js(drupal_get_path('module','ldiw_waste_map') .
				'/plugins/style_plugin/ldiw_waste_map_point_style_plugin.js');

			$composition=array();
			foreach (variable_get('ldiw_waste_map_composition_fields',
										array()) as $fieldname => $info) {
				$info['color']=trim($info['color'],'#');
				$composition[preg_replace('/^field_/','',$fieldname)]=$info;
				}

			drupal_add_js(array(
					'ldiw_waste_map_point_style_plugin_icons_base_url' =>
							url(file_directory_path() .
										'/ldiw_waste_map/waste_point_icon/',
								array('absolute' => TRUE)),

					'ldiw_waste_map_base_url' =>
							url('ldiw_waste_map',array('absolute' => TRUE)),

					'ldiw_waste_map_composition_fields' => $composition,
					),
				'setting');
			}
	}

function ldiw_waste_map_waste_point_icon()
{
	$args=func_get_args();
	$fname=$args[0];

	//!!! validate fname (must not have invalid chars, must start with non-.)

	$cache_directory='ldiw_waste_map/waste_point_icon';
	$cache_fname=file_directory_path() . "/$cache_directory/$fname";

	if (!is_file($cache_fname)) {
		$path=file_directory_path() . "/$cache_directory";
		if (!file_check_directory($path)) {
			$path=file_directory_path();
			foreach (explode('/',$cache_directory) as $p) {
				$path.="/$p";
				if (!file_check_directory($path,FILE_CREATE_DIRECTORY)) {
					drupal_not_found();
					return;
					}
				}

			drupal_get_messages();	// clear messages set by file_check_directory()

			//!!! delete cache directory upon uninstall
			//!!! implement hook_requirements() to check for directory writability
			}

		$args=explode('_',preg_replace('/\..*$/','',$fname),20);

		$total_segments=0;
		foreach($args as $i => $value) {
			$arr=explode(':',$value,2+1);
			if (count($arr) != 2) {
				drupal_not_found();
				return;
				}
			$args[$i]=array($arr[0],(int)$arr[1]);
			$total_segments+=$args[$i][1];
			}

		ldiw_waste_map_waste_point_generate_icon(
										$cache_fname,$args,$total_segments);
		}

	$headers=array('Content-Type: image/png');
	if ($fileinfo=stat($cache_fname)) {
		$headers[]='Content-Length: ' . $fileinfo[7];

		$last_modified=gmdate('D, d M Y H:i:s',$fileinfo[9]) . ' GMT';
		$headers[]='Last-Modified: ' . $last_modified;
		$headers[]='ETag: "' . md5($last_modified) . '"';
		}

	$max_age=14*24*3600;
	$headers[]='Expires: ' .
					gmdate('D, d M Y H:i:s',time() + $max_age) . ' GMT';
	$headers[]='Cache-Control: store, public, max-age=' . $max_age;

	//!!! check if-modified-since

	file_transfer($cache_fname,$headers);
	}

function ldiw_waste_map_waste_point_generate_icon($dest_fname,
									$colors_list,$total_segments,$size=64)
{
	$im=imagecreate($size,$size);
	imagecolorallocatealpha($im,0,0,0,127);		// Fill the background

	$cur_segments=0;
	if ($total_segments) {
		foreach ($colors_list as $idx => $e) {
			$start_angle=$cur_segments           * 360 / $total_segments - 90;
			$end_angle  =($cur_segments + $e[1]) * 360 / $total_segments - 90;
			$color_r=base_convert(substr($e[0],0,2),16,10);
			$color_g=base_convert(substr($e[0],2,2),16,10);
			$color_b=base_convert(substr($e[0],4,2),16,10);

			imagefilledarc($im,$size/2,$size/2,$size,$size,
					$start_angle,$end_angle,
					imagecolorallocate($im,$color_r,$color_g,$color_b),
					IMG_ARC_PIE);
			imagearc($im,$size/2,$size/2,$size,$size,
					$start_angle,$end_angle,
					imagecolorallocatealpha($im,
											$color_r,$color_g,$color_b,64));
			$cur_segments+=$e[1];
			}
		}

	imagepng($im,$dest_fname);
	}
