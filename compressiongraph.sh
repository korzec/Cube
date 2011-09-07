#!/bin/bash

if [ "$1" == pdf ] || [ "$1" == png ]; then
	comm[1]="set terminal ${1} fsize 6 monochrome"
	if [ ! -f "$2" ]; then
		comm[2]="set output \"${2}.${1}\""
	else
		comm[2]="set output \"default_output.${1}\""
	fi
elif [ "$1" == x11 ]; then 
	comm[1]="set terminal x11"
	
elif [ "$1" == ps2pdf ]; then 
	comm[1]="set terminal postscript 14"
	comm[5]="set size 1 , 0.8; set xtics 1"
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
	title=`echo $i | cut -d_ -f 1,2 \
					| sed 's/CRfile/ Size = /' \
					| sed 's/_L/, Transform levels = /' \
					| sed 's/_/, file = /'`
#title=""
	command="${command} \"${i}\" using (\$3):(\$14)  with linespoints title \"${title}\"" 
	#command="${command} \"${i}\" using (\$6):(\$1\>50?) pt 1 with points title \"${title}\"" 
fi
done

TITLE=""

comm[4]="set ylabel \"Compression ratio\"; set xlabel \"Subcube size in temporal dimenstion\"; set title \"${TITLE}\""

#theta(t) = theta0 + a * exp(-t / tau) * sin(2 * pi * t / T + phi)
#a = 40
#tau = 15
#phi = -0.5
#T = 15
#theta0 = 10
#fit theta(x) "${i}" using 1:2:3 via a, tau, phi, T, theta0
#, theta(x)

gnuplot -persist <<EOF

#set logscale y
#set datafile separator ","
${comm[1]}
${comm[2]}
${comm[4]}
${comm[3]}
${comm[5]}

${command}


EOF

if [ ! -z "$PSFILE" ]; then
	ps2pdf $PSFILE
	PDFFILE=`echo $PSFILE | sed 's/.ps/.pdf/'` 
	pdfcrop $PDFFILE $PDFFILE
fi