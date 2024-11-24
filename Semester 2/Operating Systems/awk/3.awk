BEGIN {
	sum = 0
	sumMed = 0
	contor = 0
}

{
	 if (NF % 2 == 0){
       		sum += ($1 + $NF)
	}
	else{
		sumMed += ($(NF / 2 + 1))
		contor++
	}			
}
END {
	print "Suma 1: "sum
	print "Media: "sumMed/contor	
}
