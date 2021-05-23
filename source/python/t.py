import random

count = 1

with open("porto_full_nodes_latlng.txt", "r") as f:
    l = f.readlines()
    novos = []
    for s in l[1:]:
        t = s.split(",")
        id = t[0][1:]
    
        novos.append(id)
        

    with open("tal.txt", "w") as g:
        g.write(str(count) + "\n")
        for _ in range(count):
            index = random.randint(0, len(novos))
            num = random.randint(0, 100)
            line = str(novos[index]) + " " + str(num)
            print(novos[index])
            g.write(line + "\n")
            novos.pop(index)
        