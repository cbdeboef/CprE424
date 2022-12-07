import numpy as np
import matplotlib

# Needed for GUI to interface with WSL
matplotlib.use('tkAgg')

import matplotlib.pyplot as plt

# Import data as 2D matrix
data = np.loadtxt("./outputDataOpenMP.txt", delimiter = "\t")

# Determine data Length for Omega computation
N = len(data)


# Pull out Omega and magnitude data
omega = data[:,0] / N 
X_mag = data[:,3]

# Create plot with data
fig, ax = plt.subplots()
ax.stem(omega, X_mag)

# Set Labels
ax.set_xlabel("Frequency in Hz")
ax.set_ylabel("Magnitude")
fig.suptitle("DFT Magnitude Plot")

# Create GUI of plot
plt.show()
