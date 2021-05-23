import random

acCount = 22
scCount = 3

region = "porto"

outStrong = True

with open(region + "_strong_nodes_latlng.txt", "r") as f:
    l = f.readlines()
    id_list = []
    for s in l[1:]:
        t = s.split(",")
        id = t[0][1:]
        id_list.append(id)
        

    with open(region + ("_strong" if outStrong else "")  + "_centers.txt", "w") as g:

        #Storage Centers generator
    
        g.write(str(scCount) + "\n")

        for _ in range(scCount):
            index = random.randint(0, len(id_list))
            line = str(id_list[index])
            print(id_list[index])
            g.write(line + "\n")
            id_list.pop(index)

        #Application Centers generator
    
        g.write(str(acCount) + "\n")

        for _ in range(acCount):
            index = random.randint(0, len(id_list))
            num = random.randint(0, 100)
            line = str(id_list[index]) + " " + str(num)
            print(id_list[index])
            g.write(line + "\n")
            id_list.pop(index)
        