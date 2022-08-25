"""
Define function computing sqrt(100)
"""
def sqrt(x):
	#main loop
	s = 1.0
	for k in range(100):
		s = 1/2*(s+x/s)
	return s

#Now call Sqrt to do computation
z = sqrt(2)
print(z)
