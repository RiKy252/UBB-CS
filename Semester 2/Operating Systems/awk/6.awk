BEGIN{
		
}

{
	if (NF % 2 == 1)
		print $(NF / 2 + 1)
	if (NF > 2)
		indexuri = indexuri " " NR		
}

END{
	print indexuri
}
