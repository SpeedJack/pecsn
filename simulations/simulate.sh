#!/bin/bash
set -e
VECTORS=true
REPEAT=10
while getopts s:c:o:r:n flag
do
	case "${flag}" in
		s) SCENARIO=${OPTARG};;
		c) CONFIGNAME=${OPTARG};;
		o) OUTNAME=${OPTARG};;
		r) REPEAT=${OPTARG};;
		n) VECTORS=false;;
	esac
done

if [ -z "$SCENARIO" ] || [ -z "$CONFIGNAME" ]; then
	echo '-c and -s parameters are required.'
	exit
fi
if [ -z "$OUTBASENAME" ]; then
	OUTBASENAME=$CONFIGNAME
fi

rm -rf results/$CONFIGNAME
./run -c $CONFIGNAME -f simulations.ini -u Cmdenv --repeat=$REPEAT
mkdir -p ../analysis/$SCENARIO/exported_data
if [ "$VECTORS" = true ]; then
	scavetool x results/$CONFIGNAME/*.{sca,vec} -o ../analysis/$SCENARIO/exported_data/$OUTNAME.csv
else
	scavetool x results/$CONFIGNAME/*.sca -o ../analysis/$SCENARIO/exported_data/$OUTNAME.csv
fi
