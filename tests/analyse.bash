#!/bin/bash
echo "Bash version ${BASH_VERSION}..."
g++ ../main.cpp -o ../bin/HullGenerator
echo -n "" > ./analysis/grahamscan.txt
echo -n "" > ./analysis/andrew.txt
echo -n "" > ./analysis/jarvismarch.txt
for ((i=30;i<=1000;i+=10))
do 
	echo "$i"
	echo -n "$i">"./inputs/input$i.txt"
	for((j=0;j<i;j++))
	do
		echo "">>"./inputs/input$i.txt"
		randomX=$(echo "-1^$RANDOM * $RANDOM" | bc)
		randomY=$(echo "-1^$RANDOM * $RANDOM" | bc)
		echo -n "$randomX $randomY">>"./inputs/input$i.txt"  
	done
	for flag in {'grahamscan','andrew','jarvismarch'}
	do
		START=$(date +%s.%N)
		COMM=$(echo "../bin/HullGenerator --$flag ./inputs/input$i.txt")
		$COMM > "./outputs/$flag/output$i.txt"
		END=$(date +%s.%N)
		DIFF=$(echo "$END - $START" | bc)
		echo "$i $DIFF" >> "./analysis/$flag.txt"
	done
done