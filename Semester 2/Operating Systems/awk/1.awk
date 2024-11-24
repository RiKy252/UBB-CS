BEGIN{
	sumaLiniiPare = 0
	sumaImpare = 0
	nrImpare = 0
}

{
	print "NF="NF
	for (i = 1; i <= NF; i++){
		if (NR % 2 == 0){
			sumaLiniiPare += $i
		}
		print "sumPare = "sumaLiniiPare
		if ($i % 2 == 1){
			sumaImpare += $i
			nrImpare++	
		}	
	}	
}

END{
	print "Suma numerelor de pe liniile pare: "sumaLiniiPare
	print "Media numerelor impare:" sumaImpare/nrImpare
}
