#!/usr/bin/env python3

import json
import math
import sys

data = json.load(open(sys.argv[1]))
out = []
earth_radius = 6371
file = open("out.csv", "w")

i = 0
for item in data:
    try:
        arr = item["ll"].split(',')
        lat = float(arr[0]) #* math.pi / 180
        lon = float(arr[1]) #* math.pi / 180
    except:
        continue
    x = int(earth_radius * math.cos(lon) * math.sin(lat))
    y = int(earth_radius * math.sin(lat) * math.sin(lon))
    file.write(''.join(item["city"].split(',')) + "," + str(x) + "," + str(y) + "\n")
    i += 1
    if i == 1000:
        break;

file.close()
