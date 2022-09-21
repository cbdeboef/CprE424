def PlotPoly():
    fid = open("C:/Users/caleb/CprE424/cheby.txt")
    numPts = 0;
    while True:
        line = fid.readline()
        if not line: break
        numPts = numPts + 1
    fid.close()
    numPts = 200
    import numpy as np
    import string as str
    import matplotlib.pyplot as plt

    x = np.zeros(numPts, dtype = float)
    y = np.zeros(numPts, dtype = float)
    fid = open('C:\\Users/caleb/CprE424/cheby.txt','r')
    for k in range(0,numPts):
        linestring = fid.readline()
        linelist = linestring.split()
        x[k] = float(linelist[0])
        y[k] = float(linelist[1])

    plt.rc("font", size = 12)
    plt.figure(1)
    plt.plot(x, y, marker = "o", color = "red", markersize = 10)
    plt.xlim(-1,1)
    plt.xticks([-1, -0.5, 0, 0.5, 1])
    plt.title("Chebyshev Polynomial")
    print("saving fig")
    plt.savefig('chebyPolyPlot.png', dpi = 400, bbox_inches = 'tight')
    plt.show();

if __name__ == "__main__":
    PlotPoly();
