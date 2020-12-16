parta = "smallsdss"
partb = ["12.5", "17.5", "22.5", "27.5"]
neg = ["", "neg"]
end = ".csv"
error = ["", "Calc_Error_", "Error_"]

temp = []
for a in error:
    for b in neg:
        for c in partb:
            temp.append(a+parta+b+c+end)
print(temp)


titles = temp
positive_ang = [10,31,50,70,94,110,130,150,178,187,203]
negative_ang = positive_ang[1:]

for filename in titles:
    f = open(filename, "r")
    if "neg" in filename:
        angles = negative_ang
    else:
        angles = positive_ang
    words = []
    first = True
    index = 0
    for line in f:
        if first:
            first = False
            words.append(line)
        else:
            comma = line.find(",")
            temp = str(angles[index]) + line[comma:]
            words.append(temp)
            index += 1
    f.close()
    writer = open(filename, "w")
    for i in words:
        writer.write(i)
    writer.close()

        