#!/usr/bin/bash


# current keyboard layout
current=$(setxkbmap -query | grep 'layout' | awk '{print $2}')

if [ "${current}" == 'us' ]; then
	setxkbmap -layout de
elif [ "${current}" == 'de' ]; then
	setxkbmap -layout tr
elif [ "${current}" == 'tr' ]; then
	setxkbmap -layout us
else
	# unknown layout
fi
