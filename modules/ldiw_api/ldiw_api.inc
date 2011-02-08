<?php
// $Id

function ldiw_api_get_api_base_url()
{
	//!!! remove hardcoding of this data
	print json_encode(array(
			'api_base_url' => 'http://intranet.letsdoitworld.org/api',
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

function _ldiw_api_retrieve($id,$format)
{
	if ($format != 'html') {
		throw new ServicesException("Unsupported format '$format'",403);
		}

	//!!! Support also cluster IDs

	$node=node_load($id);
	return $node->title;		//!!!
	}
