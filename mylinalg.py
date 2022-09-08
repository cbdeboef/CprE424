def gaussElimination(A,b):
        import numpy as np
        A_Aug = np.column_stack((A,b))

        for i in range(len(A)):
                A_Aug[i,:] = 1 / A_Aug[i,i] * A_Aug[i,:]

                for j in range(len(A)):
                        if (i != j):
                                A_Aug[j,:] = A_Aug[j,:] - A_Aug[j,i] * A_Aug[i,:]
                        else:
                                pass
        return A_Aug

def getPolyCoef(A_Aug):
	
        size = np.shape(A_Aug)
        return A_Aug[:,size[1]-1]

def calcPoly(a,b,c,d,x):
	y = np.zeros(len(x))
	for i in range(len(x)):
		y[i] = a * x[i]**3 + b * x[i]**2 + c * x[i] + d 
	return y

if __name__ == "__main__":
	
	import numpy as np 

	X = np.array([-0.1, -0.02, 0.02, 0.1])

	A = np.array([[X[0]**3, X[0]**2, X[0], 1], [X[1]**3, X[1]**2, X[1], 1], [X[2]**3, X[2]**2, X[2], 1], [X[3]**3, X[3]**2, X[3], 1]])
	b = np.cos(X)
	print(A)
	print(b)

	A_Aug = gaussElimination(A,b)
	
	polyCoef = getPolyCoef(A_Aug)
	a = polyCoef[0]
	b = polyCoef[1]
	c = polyCoef[2]
	d = polyCoef[3]
	
	x = np.arange(-100,100)
	x = x / 100.
	out = calcPoly(a,b,c,d,x)
	

	import matplotlib.pyplot as plt

	plt.plot(x,out,'r',x,np.cos(x))
	plt.show()
