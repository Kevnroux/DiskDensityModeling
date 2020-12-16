import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.colors as colors


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
    

if __name__ == "__main__":
    print("Working on SDSS.\nWant linear scale (0) or log scale (1)?")
    is_log = input()
    print("Want density (0) or star counts (1)?")
    is_starcounts = input()
    parta = "smallsdss"
    partb = ["12.5", "17.5", "22.5", "27.5"]
    neg = ["", "neg"]
    end = ".csv"
    error = [""]
    
    temp = []
    for a in error:
        for b in neg:
            for c in partb:
                temp.append(a+parta+b+c+end)
    name = temp
    
    for filename in name:
        f = open(filename)
        print(filename)
        radial_points = []
        flag = 0
        for line in f:
            if flag == 0:
                flag+= 1
                
            else:
                split = line.split(",")
                split = [float(i) for i in split]
                l = split[0]
                split = split[1:-1]
                r = 16
                for weight in split:
                    density = weight / (vol(r-.25, r+.25))
                    if is_starcounts == "1":
                        radial_points.append((r, l, weight))
                    else:
                        radial_points.append((r, l, density))
                    r += .5
                
        print(radial_points)
        # Compute areas and colors
        r = [radius for (radius, a, b) in radial_points]
        theta = [convert_deg_to_rad(angle) for (a, angle, b) in radial_points]
        col = [shade for (a, b, shade) in radial_points]
        for i in range(0, len(col)):
            if col[i] == 0:
                col[i] = .1
        #colors = [1-(i) for i in colors]
        #print(r)
        #print(theta)
        #print(colors)
        
        # Fixing random state for reproducibility
        #np.random.seed(19680801)
        # Compute areas and colors
        #N = 150
        #r = 2 * np.random.rand(N)
        #theta = 2 * np.pi * np.random.rand(N)
        #area = 200 * r**2
        #colors = theta    
        
        area = 10
        
        
        fig = plt.figure()
        fig_title = "SDSS "
        if is_starcounts != "0":
            fig_title +=  "Star Counts "
        else:
            fig_title += "Density "
        if is_log != "0":
            fig_title += "Logscale: "
        else:
            fig_title += "Linearscale: "
        fig_title += filename[0:-4]
        fig.suptitle(fig_title)    
        
        
        ax = fig.add_subplot(111, projection='polar')
        ax.set_ylim(15,23)
        index = 0
    #    while index < len(r):        
    #        ax.scatter(theta[index], r[index], c= colors[index], s=area, cmap = "gray", alpha =.75)
    #        index += 1
        #vmax = 20000
        if is_log == "1":
            c = ax.scatter(theta, r, c=col, s=area,
                           norm=colors.LogNorm(vmin=min(col), vmax=max(col))
                           ,cmap='inferno_r', alpha=1)
        else:
            c = ax.scatter(theta, r, c=col, s=area, cmap='inferno_r', alpha=1)            
        plt.colorbar(c)
        print("pic" + filename[0:-4] + ".png")
        fig.savefig("pic" + filename[0:-4] + ".png")
        plt.close()
    