#!/usr/bin/env bash


if [ "${EUID}" -ne 0 ]; then
  echo "This script needs superuser privileges to run."
else
  pulseaudio --kill
  killall pulseaudio
  killall -9 pulseaudio
  rm -rf ~/.pulse*
  rm -rf /tmp/pulse*
fi

# sudo -H -u wagabond12 bash -c 'pulseaudio --start' 
