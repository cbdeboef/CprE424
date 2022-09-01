import myfuncs as my
import numpy as np

#print my sqrt result
print('My sqrt(3.7) results: %f' % my.sqrt(3.7,1))

#compare my sqrt function to numpy
print('numpy sqrt(3.7) vs my sqrt(3.7) error: %f'  % np.abs(my.sqrt(3.7)-np.sqrt(3.7)))

#print my e^x result
print('My exp(3.7) results:  %f' % my.exp(3.7))

#Compare my result to numpy
print('numpy exp(3.7) vs my exp(3.7) error: %f' % np.abs(my.exp(3.7)-np.exp(3.7)))

#print my ln result
print('My ln(3.7) results: %f' % my.ln(3.7))

#Compare my ln result to numpy
print('numpy log(3.7) vs my ln(3.7) error: %f' % np.abs(my.ln(3.7)-np.log(3.7)))

#print my factorial function
print('my factorial(5) results: %f' % my.factorial(5))

