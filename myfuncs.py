"""
Define function computing sqrt(100)
"""
def sqrt(x):
        #main loop
        s = 1.0
        for k in range(100):
                s = (1 / 2) * (s + x / s)
        return s

def factorial(x):
	if x == 0:
		return 1
	s = x * factorial(x - 1)
	return s

def exp(x):
	x0 = int(round(x))
	z = x - x0
	e = 2.7182818284590451
	s = 0

	for k in range(20):
		s = s + (z ** k ) / (factorial(k))
	s = (e ** x0) * s
	return s

def ln(x):
	s = x

	for k in range(100):
		s = s - 1 + x * exp(-s)
	return s
