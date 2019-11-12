import numpy as np
import math

if __name__ == "__main__":
    fo = open("voxel.txt", "w")
    NUM=21
    rad=NUM/2
    fo.write("%d\n"%(NUM))
    for z in range(0,NUM):
        for x in range(0,NUM):
            for y in range(0,NUM):
                r=rad**2-((rad-x)**2+(rad-z)**2+(rad-y)**2)
                if r<0:
                    fo.write("255,255,255,0 ")#transparent white
                else:
                    fo.write("255,0,0,0.5 ")#semi-transparent red
            fo.write("\n")
