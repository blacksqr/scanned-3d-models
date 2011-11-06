#!gmake
root_dir  := $(shell pwd | sed -e 's=^/tmp_mnt/=/=')

vrip_dir = ${root_dir}/vrip
scanalyze_dir = ${root_dir}/scanalyze
volfill_dir = ${root_dir}/volfill


###################################################################
# Platform-specific definitions
###################################################################

all: scan vrip volfill
clean: clean_scan clean_vrip clean_volfill

scan::
	cd ${scanalyze_dir}; make all
vrip::
	cd ${vrip_dir}; make all
volfill::
	cd ${volfill_dir}; make 
clean_scan::
	cd ${scanalyze_dir}; make clean
clean_vrip::
	cd ${vrip_dir}; make clean
clean_volfill::
	cd ${volfill_dir}; make clean
