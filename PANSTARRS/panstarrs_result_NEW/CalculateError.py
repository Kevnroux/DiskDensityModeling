import math
import numpy as np

def funct(data, actual):
    total = 0
    
    #interpolate
    interpolated = []
    for i in range(0, len(data)-1):
        interpolated.append(data[i])
        interpolated.append((data[i] + data[i+1]) /2)
    interpolated.append(data[-1])
    
    
    vectorGaussian = [[1.2052866803926663e-10, 3.49333526582688e-07, 0.0001571114227252507, 0.01140333754568543, 0.14231048066713145, 0.3391056009949741, 0.2851457269219317, 0.15306899858635778, 0.05409854771692879, 0.012580185444477835, 0.0019232539484265385], [1.2052591708326127e-10, 3.4932555336620393e-07, 0.00015710783680151255, 0.011403077274992887, 0.14230723256128422, 0.3390980582493449, 0.2851433414201688, 0.15307389640040295, 0.054103934317084615, 0.012582632520255158, 0.0019238637128806274],[1.205190932375891e-10, 3.4930577551490675e-07, 0.00015709894178823935, 0.011402431664145063, 0.14229917551748375, 0.3390793481124942, 0.28513742264071956, 0.15308604410681786, 0.054117296717676545, 0.012588704005103476, 0.0019253769412132592], [1.2049887008267482e-10, 3.4924716185775983e-07, 0.00015707258051923776, 0.011400518331280127, 0.1422752976555338, 0.33902389803134453, 0.28511986955137164, 0.15312203251454803, 0.05415690376647048, 0.012606709394541494, 0.0019298672894351842], [1.2042386619705418e-10, 3.4902977480538875e-07, 0.00015697481152061302, 0.011393422138823312, 0.14218673914751892, 0.3388182349099229, 0.28505460933105975, 0.15325534277579295, 0.054303879940726184, 0.012673643885755094, 0.0019465963206471925], [1.2005661834000183e-10, 3.479653642288756e-07, 0.0001564960969189093, 0.01135867645263077, 0.14175312264854562, 0.3378110212176847, 0.2847314586864725, 0.15390433464555583, 0.05502534972334591, 0.013004933412676832, 0.0020302355692876435], [1.1762900043299752e-10, 3.4092929274111296e-07, 0.000153331650572597, 0.01112899710019238, 0.13888678821672928, 0.3311445359938526, 0.28244616932675837, 0.15803347350141309, 0.05986364932896228, 0.015345043049498049, 0.00266005175236688], [1.0273114435306686e-10, 2.977501828448016e-07, 0.00013391201039610897, 0.009719496071514745, 0.1212966074395388, 0.2899499444874817, 0.2631588100437829, 0.17640424861547988, 0.09040333074044168, 0.035415723745626446, 0.010604230529488032], [8.443266387109737e-11, 2.4471489404704965e-07, 0.00011005959130776517, 0.007988258575045818, 0.09969124503713647, 0.23884207423581413, 0.229066642694846, 0.18029198894967624, 0.12083646623391317, 0.06896368392842481, 0.033514690714276665], [8.236763426278535e-11, 2.387297281333743e-07, 0.0001073677857397656, 0.007792884063334255, 0.09725302547550488, 0.23304795392455768, 0.22463222015610004, 0.17939942301865813, 0.12320525925422596, 0.07275986410821364, 0.03694896732069376],[8.231505929049892e-11, 2.3857734778455296e-07, 0.00010729925325840633, 0.007787909892747373, 0.09719094921017433, 0.2329003786621855, 0.22451796128436313, 0.17937326363174524, 0.12326204074386192, 0.07285531943381421, 0.0370379428784837], [8.231458297073454e-11, 2.3857596724608207e-07, 0.00010729863236648848, 0.0077878648276591975, 0.09719038681040902, 0.23289904164380537, 0.22451692581532098, 0.17937302585658418, 0.1232625543601839, 0.07285618394055471, 0.037038749304877085], [8.231458170386427e-11, 2.3857596357425634e-07, 0.00010729863071509884, 0.007787864707799335, 0.0971903853145913, 0.2328990380877299, 0.22451692306127102, 0.17937302522415374, 0.12326255572623261, 0.07285618623988085, 0.03703875144974157]]
    
    result = [0 for i in range(len(interpolated))]
    for i in range(0, len(interpolated)):
        for j in range(0, len(vectorGaussian[i])):
            loc = i + j - int(len(vectorGaussian[i])/2)
            if (loc >= 0 and loc < len(result)):
                result[loc] += interpolated[i] * vectorGaussian[i][j];
    
		
    #Account for selection and completeness 
    Mag_min = 16
    Mag_max = 16 + len(interpolated) / 2.
    interval = .5
    SDSS = False
    if SDSS == True:
        vectorCompleteness = [0.986088,0.972016,0.957948,0.944999,0.934449,0.927228,0.922852,0.917635,0.902512,0.861945,0.777409,0.640076,0.471073]
        s0 = .9402
        s1 = 1.6171
        s2 = 23.5877
    else:
        vectorCompleteness = [0.85222234, 0.85222234, 0.85222234, 0.85222234, 0.852222339999997, 0.852222339999806, 0.8522223399873892, 0.8522223391798939, 0.852222286666763, 0.8522188716397806, 0.8519968439031266, 0.837802165517221, 0.4021192989396328]
        s0 = 0.85222234
        s1 = 8.34976298
        s2 = 22.23649929	
        
    iterations = int((Mag_max - Mag_min)/interval)
    t = []
    for i in range(0, iterations):
        value = s0 / (math.exp(s1*(i * interval + Mag_min + (interval/2.0) - s2)) + 1)
        t.append(value)
    for i in range(0, iterations):
        t[i] *= vectorCompleteness[i]
    
    for i in range(0, len(result)):
        result[i] *= t[i]
    
    for i in range(0, len(result)):
        total += (result[i] - actual[i])**2 / actual[i]
    return total

def error_num_helper(data, i, j, dir1, dir2, delta):
    temp = [i for i in data]
    temp[i] = temp[i] + dir1*delta
    temp[j] = temp[j] + dir2*delta
    return temp

def error_num(data, actual, i, j, chi_sq):
    delta = 1
    if i == j:
        f1 = [i for i in data]
        f1[i] = f1[i] + delta
        f2 = [i for i in data]
        f2[i] = f1[i] - delta
        return ((funct(f1, actual) - 2 * funct(data, actual) + funct(f2, actual)) / (delta**2 ))
    else:
        f1 = error_num_helper(data, i, j, 1, 1, delta)
        f2 = error_num_helper(data, i, j, 1, -1, delta)
        f3 = error_num_helper(data, i, j, -1, 1, delta)
        f4 = error_num_helper(data, i, j, -1, -1, delta)
        
        return (funct(f1, actual) - funct(f2, actual) - funct(f3, actual) + funct(f4, actual))/(4*delta**2)

def calc_error(data, actual, chi_sq):
    err_mat = [[0 for y in range(0,len(data))] for x in range(0,len(data))]
    for i in range(0,len(data)):
        for j in range(0,len(data)):
            err_mat[i][j] = error_num(data,actual,i,j,chi_sq)
    #print("Error Mat")    
    #print(np.array(err_mat))
    final = np.linalg.inv(np.array(err_mat))
    #print("FINAL")
    #print(final)
    return [(abs(final[i][i]))**.5 for i in range(0, len(final))]

def write_error(filename):
    f = open(filename, "r")
    result = open("Calc_"+filename, "w")
    first = True 
    for line in f:
        if first:
            result.write(line)
            first = False
            continue
        temp = [float(a) for a in line.split(",")]
        if len(temp) <= 15:
            result.write(line)
            continue
        
        chi_sq = temp[-1]
        angle = temp[0]

        data = temp[1:8]
        actual = temp[8:-1]
        
        e = calc_error(data,actual,chi_sq)
        error_string = str(angle) + ","
        for i in e:
            error_string += str(i) + ","
        error_string += str(chi_sq) + "\n"
        result.write(error_string)
        
        
        #print("\n\n")
    f.close()
    result.close()



if __name__ == "__main__":
    side = ["North", "South"]
    degree = ["7.5", "12.5", "17.5", "22.5", "27.5"]
    
    for s in side:
        for d in degree:
            f = "Error_Galactic" + str(s) + "Latitude" + str(d) + ".csv" 
            write_error(f)
            print("DONE: " + f)

