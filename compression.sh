#!/bin/sh
#file=$1

#filename without path

for file in $@
do
for cubed in 16
do
	for level in 3 
	do
		for subd in  1 2 4
		do 
			for subwh in 32 16 
			do 
				datafile="CR_cd${cubed}_L${level}_sd${subd}_shw${subwh}_${file##*/}.csv"
				if [ -f $datafile ]; then
					mv $datafile old_$datafile
				fi
				
				#wcbfile="cd${cubed}_L${level}_sd${subd}_shw${subwh}_${file##*/}"
				wcbfile=compressiontest
				
				#for skip in  0.2 0.4 0.5 0.6 0.7 0.8 0.9 0.95 0.97 0.99
				#do
					echo $cubed $level $subd $subwh $skip $file
					
					./cube -width 704 -height 576 -depth $cubed \
					-sd $subd -sh $subwh -sw $subwh  \
					-levels $level \
					-compressor ac \
					-analysis2 \
					 $file out/$wcbfile \
					 | grep PSNRDATACODE >> $datafile
					 #-nofile -analysis -skip $skip \
				#done
			done
		done
	done
done

cat CR_cd16_L3_sd*shw16*${file##*/}* > CRfile16_${file##*/}.csv
cat CR_cd16_L3_sd*shw32*${file##*/}* > CRfile32_${file##*/}.csv

done

sh compressiongraph.sh ps2pdf test_compression16 CRfile16*
sh compressiongraph.sh ps2pdf test_compression32 CRfile32*

#open test_scalability.pdf