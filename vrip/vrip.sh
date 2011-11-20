#!/bin/sh
export VRIP_DIR=$(pwd)/src/vrip
export PATH=$(pwd)/bin:$PATH
$(pwd)/src/vrip/vrip $@
