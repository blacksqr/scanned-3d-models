#!/bin/sh
#set -x
CWD=`pwd`
dirName=$(dirname $0)
cd ${dirName}
SCANNED_DIR=$(pwd)/scanned
SCANNED_BIN=${SCANNED_DIR}/scanned
ulimit -c unlimited

# Set SCANALYZE_DIR
SCANALYZE_DIR=$(pwd)/scanalyze
VRIP_DIR=$(pwd)/vrip/src/vrip
export SCANALYZE_DIR VRIP_DIR

if [ -f ${SCANNED_BIN} ]
then
	cd ${SCANNED_DIR}; ./scanned
else
	make
	if [ $? -ne 0 ]
	then
		echo "Compilation failed!"
		exit 1
	else 
		cd ${SCANNED_DIR}; ./scanned
	fi
fi	
cd ${PWD}
