import random

count = 200

with open("penafiel_full_nodes_latlng.txt", "r") as f:
    l = f.readlines()
    novos = []
    for s in l[1:]:
        t = s.split(",")
        id = t[0][1:]
    
        novos.append(id)

    with open("tal.txt", "w") as g:
        ids = []
        for _ in range(count):
            index = random.randint(0, len(novos))
            ids.append(novos[index])
            novos.pop(index)
        
        g.write(str(count) + "\n")
        g.write("\n".join(ids))