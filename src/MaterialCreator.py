import random

def writeData(dataName, data, file):
    file.write("   " + dataName + " : " + data + "\n")

def genID():
    return str(random.randint(1000000000, 9999999999))

obj = "Material"

f = open("../data/test.materials", "w")
f.write("{\n")
name = input(obj + " name? ")
writeData("name", name, f)
f.write("}\n")

f.close()

exit