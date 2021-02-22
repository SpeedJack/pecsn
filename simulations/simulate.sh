#!/bin/bash
set -e
RUNNER=opp_runall
SCAVETOOL=scavetool
RESULTDIR=results
ANALYSISDIR=../analysis
EXPDATAFOLDER=exported_data

VECTORS=true
INIFILE=simulations.ini
REPEAT=
OUTNAME=data
while getopts s:c:o:r:tn flag
do
	case "${flag}" in
		s) SCENARIO=${OPTARG};;
		c) CONFIGNAME=${OPTARG};;
		o) OUTNAME=${OPTARG};;
		r) REPEAT=--repeat=${OPTARG};;
		t) INIFILE=tests.ini;;
		n) VECTORS=false;;
	esac
done

if [ -z "$SCENARIO" ] || [ -z "$CONFIGNAME" ]; then
	echo '-c and -s parameters are required.'
	exit
fi

rm -rf $RESULTDIR/$CONFIGNAME

$RUNNER -j $(nproc) ../src/pecsn -n .:../src -c $CONFIGNAME -f $INIFILE -u Cmdenv $REPEAT

mkdir -p $ANALYSISDIR/$SCENARIO/$EXPDATAFOLDER
if [ "$VECTORS" = true ]; then
	$SCAVETOOL x $RESULTDIR/$CONFIGNAME/*.{sca,vec} -o $ANALYSISDIR/$SCENARIO/$EXPDATAFOLDER/$OUTNAME.csv
else
	$SCAVETOOL x $RESULTDIR/$CONFIGNAME/*.sca -o $ANALYSISDIR/$SCENARIO/$EXPDATAFOLDER/$OUTNAME.csv
fi
