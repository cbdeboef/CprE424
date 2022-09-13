"""
Gaussian Elimination of matrix Ax = B,to solve for x where
    -2  0  1      -4           x_1
A = -1  7  1, B = -50, and x = x_2
     5 -1  1      -26          x_3

Code built to be used on any array with no modifications 

Could be looped, made as proof of concept and may play around with loops later, however it now works;
"""
from numpy import *

A = array([[-2,0,1],[-1,7,1],[5,-1,1]])
b = array([-4,-50,-26])
A_Aug = array([[-2.,0,1,-4],[-1,7,1,-50],[5,-1,1,-26]])

# R_1 = R_1 * -1 / 2
A_Aug[0,:] = 1 / A_Aug[0,0] * A_Aug[0,:]

# R_2 = R_2 + R_1
# R_3 = R_3 - 5 * R_1

A_Aug[1,:] = A_Aug[1,:] - A_Aug[1,0] * A_Aug[0,:]
A_Aug[2,:] = A_Aug[2,:] - A_Aug[2,0] * A_Aug[0,:]

# R_2 = R_2 * 1/7
A_Aug[1,:] = 1 / A_Aug[1,1] * A_Aug[1,:]

# R_1 = R_1 
# R_3 = R_3 + R_2

A_Aug[0,:] = A_Aug[0,:] - A_Aug[0,1] * A_Aug[1,:]
A_Aug[2,:] = A_Aug[2,:] - A_Aug[2,1] * A_Aug[1,:]

# R_3 = R_3 * 1/1
A_Aug[2,:] = 1 / A_Aug[2,2] * A_Aug[2,:]

# R_1 = R_1 + 1/2 * R_3
# R_2 = R_2 - 1/14 * R_3

A_Aug[0,:] = A_Aug[0,:] - A_Aug[0,2] * A_Aug[2,:]
A_Aug[1,:] = A_Aug[1,:] - A_Aug[1,2] * A_Aug[2,:]

print('x_1 =',A_Aug[0,3],', x_2 =',A_Aug[1,3],', x_3 = ',A_Aug[2,3])

x = array([A_Aug[0,3],A_Aug[1,3],A_Aug[2,3]])

# Calculate Error
error = max(sum(A[0,:] * x) - A_Aug[0,3], sum(A[1,:] * x) - A_Aug[1,3], sum(A[2,:] * x) - A_Aug[2,3])

print('max Error by Backfill is ',error)
