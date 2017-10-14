while true;do
	./A_gen >in
	if ./A <in;then
		echo AC
	else
		echo RE
		break
	fi
done
