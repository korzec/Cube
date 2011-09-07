#!/bin/bash

if [ "$1" == pdf ] || [ "$1" == png ]; then
	comm[1]="set terminal ${1} fsize 6 enhanced"
	if [ ! -f "$2" ]; then
		comm[2]="set output \"${2}.${1}\""
	else
		comm[2]="set output \"default_output.${1}\""
	fi
elif [ "$1" == x11 ]; then 
	comm[1]="set terminal x11"
	
elif [ "$1" == ps2pdf ]; then 
	comm[1]="set terminal postscript 20 enhanced"
	comm[5]="set size 1 , 0.8"
	if [ ! -f "$2" ]; then	
		PSFILE="${2}.ps"
		comm[2]="set output \"${2}.ps\""
	else
		PSFILE="default_output.ps"
		comm[2]="set output \"default_output.ps\""
	fi	
fi


#now make plots for all inputs

for i in "$@"; do
if [ -f "$i" ]; then
	if [ ! "$command" == "" ]; then
		command="${command},"
	fi
	if [ "$command" == "" ]; then
		command="plot "
	fi
	title=$i
	if [ ! -f "$3" ]; then
		comm[3]=$3	
	fi
	#title="N = `echo $i | cut -d_ -f 5 | cut -dn -f 2`"
	#title=`echo $i | cut -d_ -f 2,3,4 | sed 's/ch/Channel = /' | sed 's/_level/, Level = /' \
	#| sed 's/_orient/, Orientation = /' | sed 's/.csv//'`
title=""
	command="${command} \"${i}\" using (\$2):(\$3) with points title \"${title}\"" 
fi
done

#TITLE="Orientations \{x,y,t\} : LLL = 0,    HLL = 1,    LHL = 2,    HHL = 3,\\n    LLH = 4,    HLH = 5,    LHH = 6,    HHH = 7"

comm[4]="set xlabel \"Coefficient value\"; set ylabel \"Number of occurences\"; set title \"${TITLE}\""

#theta(t) = theta0 + a * exp(-t / tau) * sin(2 * pi * t / T + phi)
#a = 40
#tau = 15
#phi = -0.5
#T = 15
#theta0 = 10
#fit theta(x) "${i}" using 1:2:3 via a, tau, phi, T, theta0
#, theta(x)

gnuplot -persist <<EOF

set logscale y
set format y "10^{%L}"

${comm[1]}
${comm[2]}

${comm[4]}
${comm[5]}


${command}


EOF


if [ ! -z "$PSFILE" ]; then
	ps2pdf $PSFILE
	PDFFILE=`echo $PSFILE | sed 's/.ps/.pdf/'` 
	pdfcrop $PDFFILE $PDFFILE
fi