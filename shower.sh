#!/bin/bash

for i in *
do
	sed -i 's/  /\t/g' $i
done
