def flip(a, pos):
	if a[pos] == "1":
		a[pos] = "0"
	else:
		a[pos] = "1"

cnt = 1
while True:
	a, b = input().split()
	if (a == "0") and (b == "0"):
		break
	if cnt != 1:
		print()
	sa = "{0:b}".format(int(a))
	sb = "{0:b}".format(int(b))
	limit = max(len(sa), len(sb))
	sa = "0" * (limit - len(sa)) + sa
	sb = "0" * (limit - len(sb)) + sb
	lista = []
	listb = []
	lista[:0] = sa
	listb[:0] = sb
	imp = ans = 10e100
	# case 1	
	tmp = 0
	for i in range(1, limit, 1):
		if (lista[i-1] != listb[i-1]):
			tmp += (1 << (limit - i - 1))
			flip(lista, i-1)	
			flip(lista, i)	
			if i + 1 < limit :
				flip(lista, i+1)
	if lista[limit-1] == listb[limit-1] :	
		ans = min(ans, tmp)
#	print("this {} is new ans".format(ans))
	
	tmp = (1 << (limit - 1))
	lista[:0] = sa
	flip(lista, 0)
	flip(lista, 1)
	for i in range(1, limit, 1):
		if (lista[i-1] != listb[i-1]):
			tmp += (1 << (limit - i - 1))
			flip(lista, i-1)	
			flip(lista, i)	
			if i + 1 < limit :
				flip(lista, i+1)
	if lista[limit-1] == listb[limit-1] :	
		ans = min(ans, tmp)
	if(ans != imp):
		print("Case Number {cnt}: {ans}".format(cnt=cnt, ans=ans))
	else:
		print("Case Number {cnt}: {ans}".format(cnt=cnt, ans="impossible"))
	cnt+=1



