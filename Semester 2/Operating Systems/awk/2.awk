BEGIN{
	cuvintePare = 0
	cuvinteImpare = 0
}

{
	for (i = 1; i <= NF; i++){
		if (NR % 2 == 0)
			cuvintePare++
		else{
			cuvinteImpare++	
		}			
	}
}

END{
	if (NR % 2 == 0)
		contorImpare = NR / 2
	else
		contorImpare = NR / 2 + 0.5
	print "Nr cuvinte pe linii pare:" cuvintePare
	print "Nr mediu pe linii impare:" cuvinteImpare/contorImpare	
}
