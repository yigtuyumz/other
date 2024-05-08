#!/usr/bin/env bash


: <<'USAGE'
echo -n "eth tx  : " ; general "eth"  "tx"
echo -n "eth rx  : " ; general "eth"  "rx"
echo -n "wlan tx : " ; general "wlan" "tx"
echo -n "wlan rx : " ; general "wlan" "rx"
USAGE

# transmitted NR==6
# recieved    NR==4
general() {
	local interface_name

	if [ "${1}" == "wlan" ]; then
		interface_name="wlp3s0"
	elif [ "${1}" == "eth" ]; then
		interface_name="enp2s0"
	else
		echo "!!!no_interface!!!"
		return 1
	fi

	local mode
	local report
	report=$(ip -s link show "${interface_name}" 2>/dev/null)

	if [ "${2}" == "tx" ]; then
		mode="6"
		echo "${report}" | awk -v MODE=$mode 'NR==MODE {print $1}' |
			numfmt --to iec --format "%8.2f" | xargs
	elif [ "${2}" == "rx" ]; then
		mode="4"
		echo "${report}" | awk -v MODE=$mode 'NR==MODE {print $1}' |
			numfmt --to iec --format "%8.2f" | xargs
	else
		echo "!!!no_mode!!!"
		return 1
	fi
}

general "${1}" "${2}"

