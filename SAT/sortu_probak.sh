#!/bin/bash

SAVE_PATH='sarrerak/'

for NV in 5 10 15 20; do
	for NC in 5 10 15 20 25 30 35 40 45 50; do
		for D in $(seq 1 $NV); do
			for i in 1 2 3 4 5; do
				./sortu "$SAVE_PATH$NC-$NV-$D-$i.txt" $NC $NV $D
			done
		done
	done
done
