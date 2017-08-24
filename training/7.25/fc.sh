while(true);do
	python3 E_gen.py
	./E_ano  <E.in >E.out
	./_E <E.in >E.ans
	if diff E.out E.ans then
		echo AC
	else
		echo WA
		break
	fi
done
