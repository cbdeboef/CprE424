"""
A group of mathmatical functions to be used instead of calling numpy
"""

def sqrt(x, showIter = 0, initialGuess = 1.0, Kmax = 100, tol = 1E-14):	
	"""
	A sqrt function utilizing the newton method

	inputs: x -- The number to be square rooted
		showIter -- prints number of iterations needed to complete program
		initialGuess -- The starting number for the newton method of finding the square root
		Kmax -- Maximum number of iterations
		tol -- Tolerance of function, will beak when differences between iterations are less than tol
	"""

	s = initialGuess

	# Loop through newton method until either k iterations have occured or until the difference between iterations is < tol
	for k in range(Kmax):
		s_old = s
		s = (1 / 2) * (s + x / s)
		if abs(s - s_old) < tol:
			if showIter == 1:
				print(k)
			break
	return s


def factorial(x):
	"""
	Recursive factorial function
	"""

	# Stop multiplication by zero
	if x == 0:
		return 1

	# Recurse from x*(x-1)...1
	s = x * factorial(x - 1)
	return s


def exp(x, Kmax = 100, tol = 1E-14):
	"""
	Iteratively calculates the exponenitial function e^x using the factorial function above

	inputs: x -- The number to be exponentiated
		Kmax -- maximum number of iterations
		tol -- Tolerance of function, will beak when differences between iterations are less than tol 
	"""

	# Initialize variables to be used in function
	x0 = int(round(x))
	z = x - x0
	e = 2.7182818284590451
	s = 0

	# Apply iterative power formula to solve for s, a component of the final answer. Break on k = kmax and (s-s_old < tol)
	for k in range(Kmax):
		s_old = s
		s = s + (z ** k ) / (factorial(k))
		if abs(s - s_old) < tol:
			break

	# With S found, now solve for the answer
	s = (e ** x0) * s
	return s


def ln(x, Kmax = 100, tol = 1E-14):
	"""
	Iteratively calculates the natural log of x using the exponential function above

	inputs: x -- the number that will have the logrithm applied
		Kmax -- maximum number of iterations
                tol -- Tolerance of function, will beak when differences between iterations are less than tol 
	"""
	
	#Create dummy variable to be changed
	s = x
	
	# Loops through the ln(x) formula, breaks on s - s_old < tol or k = kmax
	for k in range(Kmax):
		s_old = s
		s = s - 1 + x * exp(-s)
		if abs(s-s_old) < tol:
			break
	return s
