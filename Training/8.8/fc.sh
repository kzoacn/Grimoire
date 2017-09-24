while true;do
	./C_gen >C.in
	./C <C.in >C.out
	./_C <C.in >C.ans
	if ./spj C.out C.ans;then
		echo AC
	else
		echo WA
		break
	fi
done
