<?php
// $Id$

function theme_ldiw_waste_map_formatter_as_link($element)
{
	if (empty($element['#item']['value'])) {
		return '';
		}
	$url=$element['#item']['value'];
	return l($url,$url);
	}

function theme_ldiw_waste_map_formatter_as_twitter_link($element)
{
	if (empty($element['#item']['value'])) {
		return '';
		}
	$url=$element['#item']['value'];

	if (strpos($url,'/') == FALSE) {
		$url='http://twitter.com/' . $url;
		}

	return l($url,$url);
	}

function theme_ldiw_waste_map_formatter_as_youtube_link($element)
{
	if (empty($element['#item']['value'])) {
		return '';
		}
	$url=$element['#item']['value'];

	if (strpos($url,'/') == FALSE) {
		$url='http://www.youtube.com/' . $url;
		}

	return l($url,$url);
	}
