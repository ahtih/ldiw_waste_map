<?php
// $Id$

function theme_ldiw_waste_map_formatter_as_link($element)
{
	if (empty($element['#item']['value'])) {
		return '';
		}
	return l($element['#item']['value'],$element['#item']['value']);
	}
