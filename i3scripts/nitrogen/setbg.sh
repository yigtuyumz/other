#!/usr/bin/env bash

# what if values of --head changes??

bg_path='/usr/share/backgrounds/synthwave'
monitor_count=$(xrandr | grep '\bconnected\b' | cut -d' ' -f1 | wc -w)

# set bg for main display, always
nitrogen --head=1 --set-zoom-fill "${bg_path}/8k.jpg" 2>/dev/null

# set bg for auxilary display, if connected
if [[ "${monitor_count}" -ge 2 ]]; then
	nitrogen --head=0 --set-zoom-fill "${bg_path}/5k.jpg" 2>/dev/null
fi

