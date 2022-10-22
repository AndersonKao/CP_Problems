import math

n = int(input());
if (n == 0):
	print(1)
else:
	count = int(math.log(n, 6)) - 1
	N = 6 ** count;
	
	while (True):
		if (6 ** (count+1) > n):
			break;
		count += 1;
	
	print(count+1);

