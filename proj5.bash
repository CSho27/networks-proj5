#! /bin/bash
# This script will eventually grab data
while IFS='' read -r line || [[ -n "$line" ]];
do
	echo $line
	timeout --kill-after=10 10 wget $line --save-headers --output-document=http.html --timeout=10 --append-output=logfile.txt
	./wget_parser
	rm -f http.html
	sleep .1
done < "$1"
