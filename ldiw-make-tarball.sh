#!/bin/sh

if [ -z "$1" ] ; then
	echo 'Missing output filename';
	exit;
fi

TMPDIR=/tmp/ldiw-make-tarball-tmpdir

get_from_git() {
	git clone $2 $1 && rm -rf $1/.git
	}

rm -rf $TMPDIR &&
mkdir -p $TMPDIR &&

pushd $TMPDIR &&

get_from_git 'geoclustering' 'git://github.com/ahtih/Geoclustering.git' &&
get_from_git 'ldiw_waste_map' 'git://github.com/ahtih/ldiw_waste_map.git' &&
get_from_git 'geo' 'git@git.drupal.org:sandbox/ahtih/1081362.git' &&
get_from_git 'views_bonus' 'git@git.drupal.org:sandbox/ahtih/1081884.git' &&

(curl http://ftp.drupal.org/files/projects/services-6.x-3.x-dev.tar.gz | tar xz) &&
(curl http://ftp.drupal.org/files/projects/openlayers-6.x-2.x-dev.tar.gz | tar xz) &&

fnames=`ls -1` &&
popd &&
tar -czf $1 -C $TMPDIR $fnames &&
rm -rf $TMPDIR
