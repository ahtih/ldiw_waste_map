<?php
// $Id

function ldiw_api_get_api_base_url()
{
	//!!! remove hardcoding of this data
	print json_encode(array(
			'api_base_url' => 'http://api.letsdoitworld.org/api',
			'safe_bbox' => '-180,-90,180,90',
			));
	}

function _ldiw_api_create()
{
	global $user;

	if (!$user->uid) {
		//!!! If there is a SESSxxx cookie, return 401 Invalid session
		}

	return array($user->uid,func_get_args());	//!!!
	}

function _ldiw_api_retrieve($id,$max_width)
{
	$attrs=array('id' => $id);
	$photos=array();

	$cluster_info=geoclustering_get_cluster_info('ldiw_waste_map',$id);
	if ($cluster_info) {
		foreach ($cluster_info[1] as $key => $value) {
			$attrs[preg_replace('/^field_(..*)$/','$1',$key)]=$value;
			}
		$attrs['nr_of_nodes']=$cluster_info[0];
		}
	else {
		$node=node_load($id);

		if (!$node || $node->type != 'waste_point') {
			throw new ServicesException("No node/cluster with ID '$id'",404);
			}

		$photos=ldiw_waste_map_list_photos($node);

		foreach (content_fields(NULL,'waste_point') as $key => $field) {
			if (!empty($node->{$key}[0]['value'])) {
				$attrs[preg_replace('/^field_(..*)$/','$1',$key)]=
												$node->{$key}[0]['value'];
				}
			}

		if (!empty($node->body)) {
			$attrs['description']=$node->body;
			}
		}

	require_once(dirname(__FILE__) . '/waste_point_html.inc');
	return _waste_point_html($attrs,$photos,$max_width);
	}
