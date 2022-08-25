import myfuncs as my
import numpy as np


print('My sqrt(3.7) results: %f' % my.sqrt(3.7))
print('numpy sqrt(3.7) vs my sqrt(3.7) error: %f'  % np.abs(my.sqrt(3.7)-np.sqrt(3.7)))
print('My exp(3.7) results:  %f' % my.exp(3.7))
print('numpy exp(3.7) vs my exp(3.7) error: %f' % np.abs(my.exp(3.7)-np.exp(3.7)))
print('My ln(3.7) results: %f' % my.ln(3.7))
print('numpy log(3.7) vs my ln(3.7) error: %f' % np.abs(my.ln(3.7)-np.log(3.7)))
