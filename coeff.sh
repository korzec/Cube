for i in $(ls out | grep stats_ch0_level1_orient)
do
 sh coeffstats.sh ps2pdf stats_$i out/$i
done 

