#!gmake
root_dir  := $(shell pwd | sed -e 's=^/tmp_mnt/=/=')

vrip_dir = ${root_dir}/vrip
scanalyze_dir = ${root_dir}/scanalyze


###################################################################
# Platform-specific definitions
###################################################################

all: scan vrip
clean: clean_scan clean_vrip

scan::
	cd ${scanalyze_dir}; make all
vrip::
	cd ${vrip_dir}; make all
clean_scan::
	cd ${scanalyze_dir}; make clean
clean_vrip::
	cd ${vrip_dir}; make clean
