#! /bin/bash

sqlscript="$1"

mysql -u obd mysql < "${sqlscript}"