#!/bin/sh
#file=$1

#filename without path

for file in $@
do
for cubed in 16
do
	for level in 1 2 3
	do
		for subd in 2
		do 
			for subwh in 32 
			do 
				datafile="psnr_cd${cubed}_L${level}_sd${subd}_shw${subwh}_${file##*/}.csv"
				if [ -f $datafile ]; then
					mv $datafile old_$datafile
				fi
				#ALLDATA[$file]=datafile
				wcbfile="cd${cubed}_L${level}_sd${subd}_shw${subwh}_${file##*/}"
				
				for skip in  0.2 0.4 0.5 0.6 0.7 0.8 0.9 0.95 0.97 0.99
				do
					echo $cubed $level $subd $subwh $skip $file
					
					./cube -width 704 -height 576 -depth $cubed \
					-sd $subd -sh $subwh -sw $subwh  \
					-levels $level \
					-compressor lzo \
					-nofile -analysis -skip $skip \
					 $file out/$wcbfile \
					 | grep PSNRDATACODE >> $datafile
				done
			done
		done
	done
done
done
sh levelsgraph.sh ps2pdf levels_src7 psnr_*src7*
sh levelsgraph.sh ps2pdf levels_harbour psnr_*harbour*
sh levelsgraph.sh ps2pdf levels_soccer psnr_*soccer*
sh levelsgraph.sh ps2pdf levels_crew psnr_*crew*


#sh psnrgraph.sh pdf test_scalability psnr_cd*soccer*.yuv.csv
#open test_scalability.pdf