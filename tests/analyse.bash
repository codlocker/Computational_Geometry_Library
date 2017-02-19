#!/bin/bash
echo "Bash version ${BASH_VERSION}..."
g++ ../main.cpp -o ../bin/HullGenerator
echo -n "" > ./analysis/runtime.txt
for ((i=30;i<=1000;i+=10))
do 
	echo "$i"
	echo -n "" > "./outputs/output$i.txt"
	echo -n "$i">"./inputs/input$i.txt"
	for((j=0;j<i;j++))
	do
		echo "">>"./inputs/input$i.txt"
		randomX=$(echo "-1^$RANDOM * $RANDOM" | bc)
		randomY=$(echo "-1^$RANDOM * $RANDOM" | bc)
		echo -n "$randomX $randomY">>"./inputs/input$i.txt"  
	done
	START=$(date +%s.%N)
	../bin/HullGenerator "./inputs/input$i.txt" >> "./outputs/output$i.txt"
	END=$(date +%s.%N)
	DIFF=$(echo "$END - $START" | bc)
	echo "$i $DIFF" >> "./analysis/runtime.txt"
done