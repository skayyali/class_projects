#!/bin/bash

for i in {0..100}
do
	curl http://localhost:10056/complex.html > /dev/null 2>1
	echo "Request $i";
done
