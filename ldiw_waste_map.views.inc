<?php
// $Id

function ldiw_waste_map_views_handlers()
{
	return array(
		'handlers' => array(
			'content_handler_field_optimized' => array(
						'parent' => 'content_handler_field_multiple'),
			));
	}

/**
 * Implementation of hook_views_data().
 */
function ldiw_waste_map_views_data()
{
	$data=array();
	$data['ldiw_waste_map_smartphone_install_visitors']=array(

	'table' => array('group' => t('LDIW smartphone QR-Code'),
			'base' => array('field' => 'id',
							'title' => t('LDIW smartphone QR-Code event'),
							'help' => t('User activity events for smartphone app QR-Code.')),
			),

	'time' => array('title' => t('Time'),
		'help' => t('Time when the event happened'),
		'sort' => array('handler' => 'views_handler_sort'),
		'field' => array('dummy' => 'dummy')),

	'country_code' => array('title' => t('Country code'),
		'help' => t('User country code, from GeoIP'),
		'sort' => array('handler' => 'views_handler_sort'),
		'filter' => array('handler' => 'views_handler_filter_equality'),
		'field' => array('dummy' => 'dummy')),

	'user_agent' => array('title' => t('User-Agent'),
		'help' => t('HTTP User-Agent string'),
		'sort' => array('handler' => 'views_handler_sort'),
		'field' => array('dummy' => 'dummy')),

	'smartphone_type' => array('title' => t('Detected smartphone type'),
		'help' => t("Detected smartphone type"),
		'sort' => array('handler' => 'views_handler_sort'),
		'filter' => array('handler' => 'views_handler_filter_equality'),
		'field' => array('dummy' => 'dummy')),
	);

	return $data;
	}
