if [ -z "$1" ];then
	exit
fi

DIR=$1

cd $DIR

for ORG in $(ls | grep skip0.0 | grep $2 | grep $3)
do
	for skip in 0.5 0.9
	do
	SKIP=$(echo $ORG | sed "s/skip0.0/skip${skip}/")
	DIFF=$(echo $ORG | sed "s/skip0.0/diff_skip${skip}/")
	composite $ORG $SKIP -compose difference $DIFF
	convert $DIFF -contrast-stretch 0  max$DIFF
	convert $DIFF -negate neg$DIFF
	
	convert $ORG $(echo $ORG | sed "s/.png/.jpg/")
	convert $SKIP $(echo $SKIP | sed "s/.png/.jpg/")
	convert neg$DIFF $(echo neg$DIFF | sed "s/.png/.jpg/")
	done
done
