
{
	suma = 0
	contor = 0
	for (i = 3; i <= NF; i++){
		suma += $i
		contor++	
	}
	medie = suma/contor
	print $1 " " $2 " " medie
	if (medie > 8){
		elevi = elevi "\n" $1 " " $2
	}
}
END{
	print elevi
}
