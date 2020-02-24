import random

def writeData(dataName, data, file):
    file.write("   " + dataName + " : " + data + "\n")

def genID():
    return str(random.randint(1000000000, 9999999999))

obj = "Creature"

f = open("../data/test.creatures", "w")
f.write("{\n")
name = input(obj + " name? ")
writeData("name", name, f)
f.write("}\n")

f.close()