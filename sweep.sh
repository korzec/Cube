#file=$1

#filename without path

for file in $@
do
for cubed in 16
do
	for level in 3 #1 2
	do
		for subd in  4 #2
		do 
			for subwh in 32  # 16
			do 
				datafile="psnr_cd${cubed}_L${level}_sd${subd}_shw${subwh}_${file##*/}.csv"
				#if [ -f $datafile ]; then
				#	mv $datafile old_$datafile
				#fi
				
				wcbfile="cd${cubed}_L${level}_sd${subd}_shw${subwh}_${file##*/}"
				
				
					echo $cubed $level $subd $subwh $skip
					
				#	./cube -width 704 -height 576 -depth $cubed \
				#	-sd $subd -sh $subwh -sw $subwh  \
				#	-levels $level \
				#	-compressor lzo \
				#	 $file out/$wcbfile \
					#-nofile -analysis -skip $skip \
										#  | grep PSNRDATACODE >> $datafile
				for skip in 0.5 0.9 0.95
				do
				   ./cube -decode -skip $skip out/${wcbfile}.wcb out/skip${skip}_${wcbfile}
				   if [ ! -e "out/${file##*/}" ] ;then
				   		mkdir "out/${file##*/}"
				   	fi
				   		yuv2avi.sh out/skip${skip}_${wcbfile}.yuv
				   		getframe.sh out/skip${skip}_${wcbfile}.avi 0 999
				   
				done
			done
		done
	done
done
done