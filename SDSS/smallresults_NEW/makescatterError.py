import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from uncertainties import ufloat
def convert_deg_to_rad(deg):
    rad = np.pi * deg/180 
    return rad
def dist(mag):
    exponent = (mag - 4.2)/5.
    lhs = 10**exponent
    lhs = float(lhs) / 100.
    return lhs
def volSphere(radius):
    return 4./3. * np.pi * radius**3
def vol(magSmall, magLarge):
    distSmall = dist(magSmall)
    volSmall = volSphere(distSmall)
    
    distLarge = dist(magLarge)
    volLarge = volSphere(distLarge)
    
    volDiff = volLarge - volSmall
    solidAngleVol = (convert_deg_to_rad(5))*(convert_deg_to_rad(2.5)) / (4 * np.pi)
    return solidAngleVol*volDiff
def interpolate(data):
    val = []
    for i in range(0, len(data)-1):
        val.append(data[i])
        if (data[i].s == 0):
            val.append(data[i])
        else:
            val.append((data[i] + data[i+1])/2)
    val.append(data[-1])
    return val

if __name__ == "__main__":
    parta = "smallsdss"
    partb = ["12.5", "17.5", "22.5", "27.5"]
    neg = ["", "neg"]
    end = ".csv"
    error = ["Error_"]
    
    temp = []
    for a in error:
        for b in neg:
            for c in partb:
                temp.append(a+parta+b+c+end)
    name = temp
    t = ["Calc_"+i for i in name]
    name = name + t
    for filename in name:
        isError = "Calc" in filename
        f = open(filename)
        #print(filename)
        radial_points = []
        flag = 0
        for line in f:
            if flag == 0:
                flag+= 1
                
            else:
                split = line.split(",")
                split = [float(i) for i in split]
                l = split[0]
                split = split[1:8]
                r = 16
                for weight in split:
                    density = weight #/ (vol(r-.25, r+.25))
                    radial_points.append((r, l, density))
                    r += 1
        f.close()
        print(radial_points)
        # Compute areas and colors
        r = [radius for (radius, a, b) in radial_points]
        theta = [convert_deg_to_rad(angle) for (a, angle, b) in radial_points]
        colors = [shade for (a, b, shade) in radial_points]
        
        #print(r)
        #print(theta)
        #print(colors)        
        area = 10
        fig = plt.figure()
        if filename[0] == "C":
            fig.suptitle("SDSS: Final Hypothesis " + filename[0:-4])
        else:
            fig.suptitle("SDSS: Final Hypothesis " + filename[6:-4])
        #print("PanStarrs: Final Hypothesis " + filename[0:-4])
        ax = fig.add_subplot(111, projection='polar')
        ax.set_ylim(15,23)
        index = 0
        c = ax.scatter(theta, r, c=colors, s=area, cmap='inferno_r', alpha=1)
        plt.colorbar(c)
        print("pic Pre_interpolation" + filename[5:-4] + ".png")
        fig.savefig("pic Pre_interpolation" + filename[5:-4] + ".png")
        plt.close()
        
        
        if isError:
            f2 = open(filename)
            #print(filename)
            radial_points = []
            flag = 0
            for line in f2:
                if flag == 0:
                    flag+= 1
                    
                else:
                    split = line.split(",")
                    split = [float(i) for i in split]
                    l = split[0]
                    split = [ufloat(0, x) for x in split[1:8]]
                    split = interpolate(split)
                    r = 16
                    for weight in split:
                        density = weight / (vol(r-.25, r+.25))
                        r += .5
                        radial_points.append((r, l, density.s))
            f2.close()
            print(radial_points)
            # Compute areas and colors
            r = [radius for (radius, a, b) in radial_points]
            theta = [convert_deg_to_rad(angle) for (a, angle, b) in radial_points]
            colors = [shade for (a, b, shade) in radial_points]
            
            #print(r)
            #print(theta)
            #print(colors)        
            area = 10
            fig = plt.figure()
            if filename[0] == "C":
                fig.suptitle("SDSS: Stellar Density " + filename[0:-4])
            else:
                fig.suptitle("SDSS: Stellar Density " + filename[6:-4])
            #print("PanStarrs: Final Hypothesis " + filename[0:-4])
            ax = fig.add_subplot(111, projection='polar')
            ax.set_ylim(15,23)
            index = 0
            c = ax.scatter(theta, r, c=colors, s=area, cmap='inferno_r', alpha=1)
            plt.colorbar(c)
            print("pic Post_interpolationError" + filename[5:-4] + ".png")
            fig.savefig("pic Post_interpolationError" + filename[5:-4] + ".png")  
            plt.close()
