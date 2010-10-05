<?php
// $Id$

class ldiw_waste_map_behavior_addpointcontent extends openlayers_behavior
{
	function options_form($defaults)
	{
		return array(
			'content_type' => array(
				'#type' => 'select',
				'#options' => node_get_types('names'),
				'#description' =>
						t('Select content type to add when map is clicked. This also determines the node form displayed in popup.'),
				'#default_value' => isset($defaults['content_type']) ? $defaults['content_type'] : NULL
				),
			'layer_to_refresh' => array(
				'#type' => 'select',
				'#options' => array(NULL => t('<Do not refresh>')) +
													$this->map['layers'],
				'#description' =>
						t('Optionally select layer to refresh when new point is added. This could be e.g. a WFS vector layer which dynamically fetches the newly added point from Drupal server.'),
				'#default_value' => isset($defaults['layer_to_refresh']) ? $defaults['layer_to_refresh'] : NULL
				),
			);
		}

	function render(&$map)
	{
		// We call drupal_render_form() and ignore its result, just to make
		//   sure the relevant drupal_add_js() calls get done

		$node_type='waste_point';
		include_once drupal_get_path('module','node') . '/node.pages.inc';
		$form_id=$node_type . '_node_form';
		$form_state=array();
		$node=array('type' => $node_type);
		$form=drupal_retrieve_form($form_id,$form_state,$node);
		drupal_prepare_form($form_id,$form,$form_state);
		drupal_process_form($form_id,$form,$form_state);
		drupal_render_form($form_id,$form);

		drupal_add_css(drupal_get_path('module','ldiw_waste_map') .
							'/ldiw_waste_map_behavior_addpointcontent.css');
		drupal_add_js(drupal_get_path('module','ldiw_waste_map') .
							'/ldiw_waste_map_behavior_addpointcontent.js');
		return $this->options;
		}
	}
