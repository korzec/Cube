for i in 00086 00087 00088 00089
do
	for skip in 0.5 0.0 0.9_
	do
		FILE=$(ls out | grep skip$skip | grep soccer | grep $i)
		convert out/$FILE $(echo out/$FILE | sed "s/.png/.jpg/")
	done
done

exit

sh diff.sh out crew 00089

sh diff.sh out soccer 00022

sh diff.sh out src7 00058

sh diff.sh out harbour 00124

