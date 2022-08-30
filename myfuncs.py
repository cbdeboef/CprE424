"""
Define function computing sqrt(100)
"""
def sqrt(x, Kmax = 100, tol = 1E-14):
	#main loop
	s = 1.0
	for k in range(Kmax):
		s_old = s
		s = (1 / 2) * (s + x / s)
		if abs(s - s_old < tol):
			break
	return s

def factorial(x):
	if x == 0:
		return 1
	s = x * factorial(x - 1)
	return s

def exp(x,Kmax = 100, tol = 1E-14):
	x0 = int(round(x))
	z = x - x0
	e = 2.7182818284590451
	s = 0

	for k in range(Kmax):
		s_old = s
		s = s + (z ** k ) / (factorial(k))
		if abs(s - s_old < tol):
			break
	s = (e ** x0) * s
	return s

def ln(x, Kmax = 100, tol = 1E-14):
	s = x

	for k in range(Kmax):
		s_old = s
		s = s - 1 + x * exp(-s)
		if abs(s-s_old < tol):
			break
	return s
