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
BATCHSIZE=1000
EXPORTONLY=false

# Read cmdline args
while getopts s:c:o:r:b:tnx flag
do
	case "${flag}" in
		s) SCENARIO=${OPTARG};;
		c) CONFIGNAME=${OPTARG};;
		o) OUTNAME=${OPTARG};;
		r) REPEAT=--repeat=${OPTARG};;
		t) INIFILE=tests.ini;;
		n) VECTORS=false;;
		b) BATCHSIZE=${OPTARG};;
		x) EXPORTONLY=true;;
	esac
done

# Check required args
if [ -z "$SCENARIO" ] || [ -z "$CONFIGNAME" ]; then
	echo '-c and -s parameters are required.'
	exit
fi

# Run simulations if requested
if [ "$EXPORTONLY" = false ]; then
	rm -rf $RESULTDIR/$CONFIGNAME
	$RUNNER -j $(nproc) ../src/pecsn -n .:../src -c $CONFIGNAME -f $INIFILE -u Cmdenv $REPEAT
fi

# Create output dir
mkdir -p $ANALYSISDIR/$SCENARIO/$EXPDATAFOLDER

# Enumerate result (input) files
if [ "$VECTORS" = true ]; then
	INFILES=($RESULTDIR/$CONFIGNAME/*.{sca,vec})
else
	INFILES=($RESULTDIR/$CONFIGNAME/*.sca)
fi

# Sort result files by name
# This ensures that .sca and .vec files are alternated. Needed in order to have
# consistent CSV columns in the output of each execution of scavetool
IFS=$'\n' INFILES=($(sort <<<"${INFILES[*]}"))
unset IFS

# Clear output file if present
rm -f $ANALYSISDIR/$SCENARIO/$EXPDATAFOLDER/$OUTNAME.csv

# Extract data from result files in batches
# Needed due to a bug in scavetool that is unable to process large number of
# files :(
echo -n 'Exporting data...'
OPFILES=()
i=0
while ((${#INFILES[@]})); do
	CURFILES=("${INFILES[@]:0:$BATCHSIZE}")
	$SCAVETOOL x -F CSV-R -x columnNames=false ${CURFILES[@]} -o - > /tmp/${SCENARIO}_${OUTNAME}$i.csv
	OPFILES+=("/tmp/${SCENARIO}_${OUTNAME}$i.csv")
	i+=1
	INFILES=("${INFILES[@]:$BATCHSIZE}")
done
echo 'done!'

# Create output CSV header
if [ "$VECTORS" = true ]; then
	echo 'run,type,module,name,attrname,attrvalue,value,count,sumweights,mean,stddev,min,max,binedges,binvalues,vectime,vecvalue' > $ANALYSISDIR/$SCENARIO/$EXPDATAFOLDER/$OUTNAME.csv
else
	echo 'run,type,module,name,attrname,attrvalue,value,count,sumweights,mean,stddev,min,max,binedges,binvalues' > $ANALYSISDIR/$SCENARIO/$EXPDATAFOLDER/$OUTNAME.csv
fi

# Merge CSVs
cat ${OPFILES[@]} >> $ANALYSISDIR/$SCENARIO/$EXPDATAFOLDER/$OUTNAME.csv
rm "${OPFILES[@]}"

echo "DONE! Output written to $ANALYSISDIR/$SCENARIO/$EXPDATAFOLDER/$OUTNAME.csv"
