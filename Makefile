#!gmake
root_dir  := $(shell pwd | sed -e 's=^/tmp_mnt/=/=')

vrip_dir = ${root_dir}/vrip
scanalyze_dir = ${root_dir}/scanalyze
scanned_dir = ${root_dir}/scanned
volfill_dir = ${root_dir}/volfill


###################################################################
# Platform-specific definitions
###################################################################

all: scz vrip volfill scan
clean: clean_scz clean_vrip clean_volfill clean_scan

scz::
	cd ${scanalyze_dir}; make all
vrip::
	cd ${vrip_dir}; make 
volfill::
	cd ${volfill_dir}; make 
scan::
	cd ${scanned_dir}; qmake
	# remove plvMain.o
	cd ${scanned_dir}; perl -ni -e 'print unless /Main/' ${scanned_dir}/Makefile
	cd ${scanned_dir}; make
clean_scz::
	cd ${scanalyze_dir}; make clean
clean_scan::
	cd ${scanned_dir}; rm -rf .obj .ui .moc scanned Makefile
clean_vrip::
	cd ${vrip_dir}; make clean
clean_volfill::
	cd ${volfill_dir}; make clean
