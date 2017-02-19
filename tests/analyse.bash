#!/bin/bash
echo "Bash version ${BASH_VERSION}..."
g++ ../main.cpp -o ../bin/HullGenerator
for ((i=30;i<=100;i+=10))
do 
	echo "$i"
	echo -n "$i">"sampleInput.txt"
	for((j=0;j<i;j++))
	do
		echo "">>"sampleInput.txt"
		echo -n "$RANDOM $RANDOM">>"sampleInput.txt"  
	done
	START=$(date +%s.%N)
	../bin/HullGenerator "sampleInput.txt"
	END=$(date +%s.%N)
	DIFF=$(echo "$END - $START" | bc)
	echo "Diff=$DIFF"
done