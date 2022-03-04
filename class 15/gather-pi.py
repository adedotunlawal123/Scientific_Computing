import sys
import os
import math

if len(sys.argv) != 3:
    print("Usage: python3 gather-pi.py #threads #samples", file=sys.stderr)
    sys.exit(1)

thr = int(sys.argv[1])
sam = int(sys.argv[2])

os.system("test -e tmp.dat && rm tmp.dat");

for i in range(0,100):
    os.system("./pi-mp --thread "+str(thr)+" --samples "+str(sam)+" >> tmp.dat")

with open("tmp.dat", "r") as myfile:
    A = myfile.read().splitlines()
vals = [float(a) for a in A]

print("Data set:")
print("{}, {}, ..., {}".format(vals[1],vals[2],vals[-1]))
ave = sum(vals)/len(vals)
var = math.sqrt(sum(map(lambda x: (x-ave)*(x-ave), vals)))/len(vals)

print("pi = {} +/- {}".format(ave,var));

