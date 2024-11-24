BEGIN{
	suma = 0	
}

{
	for (i = 1; i <= NF; i++)
		v[$i]++
	suma += NF
}

END{
	print "Medie: "suma/NR
	for (word in v){
		if (v[word] < suma/NR)
			print word ": "v[word]	
	}
}
