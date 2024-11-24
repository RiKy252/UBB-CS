{
	for(i = 1; i <= NF; i++)
		v[$i]++	
}

END{
	for (field in v){
		print "Field: "field " frecventa: "v[field]	
	}	
}
