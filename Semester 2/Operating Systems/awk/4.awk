BEGIN{
	maxCuv = 0	
	minCuv = 9999999
	cuv = 0
	idxMin = 0
	idxMax = 0
	contor = 0
}

{
	contor++
	if (NF > maxCuv){
		maxCuv = NF
		idxMax = contor
	}
	if (NF < minCuv){
		minCuv = NF
		idxMin = contor
	}
	cuv += NF
}

END {
	print "Numarul mediu de cuvinte per linie: "cuv/NR
	print "Linia cu nr max de cuvinte: "idxMax
	print "Linia cu nr min de cuvinte: "idxMin
}
