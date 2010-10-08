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
						t('Content type to add when map is clicked. This also determines the node form displayed in popup.'),
				'#default_value' => isset($defaults['content_type']) ?
										$defaults['content_type'] : NULL
				),
			'features_layer' => array(
				'#type' => 'select',
				'#options' => $this->map['layers'],
				'#description' =>
						t('Vector layer containing features to be added/edited. This layer will also be refreshed after successful add/edit.'),
				'#default_value' => isset($defaults['features_layer']) ?
										$defaults['features_layer'] : NULL
				),
			);
		}

	function render(&$map)
	{
		// We call drupal_render_form() and ignore its result, just to make
		//   sure the relevant drupal_add_js() calls get done

		include_once drupal_get_path('module','node') . '/node.pages.inc';
		$form_id=$this->options['content_type'] . '_node_form';
		$form_state=array();
		$node=array('type' => $this->options['content_type']);
		$form=drupal_retrieve_form($form_id,$form_state,$node);
		drupal_prepare_form($form_id,$form,$form_state);
		drupal_process_form($form_id,$form,$form_state);
		drupal_render_form($form_id,$form);

		drupal_add_css(drupal_get_path('module','ldiw_waste_map') .
							'/ldiw_waste_map_behavior_addpointcontent.css');
		drupal_add_js(drupal_get_path('module','ldiw_waste_map') .
							'/ldiw_waste_map_behavior_addpointcontent.js');

		global $base_url;
		return array_merge($this->options,array(
				'site_base_url' => $base_url,
				'content_type_name' => node_get_types('type',
									$this->options['content_type'])->name));
		}
	}
