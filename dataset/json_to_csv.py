#!/usr/bin/env python3

import json
import math
import sys

data = json.load(open(sys.argv[1]))
out = []
earth_radius = 6371
file = open("out.csv", "w")

for item in data:
    try:
        lat = float(item["latitude"]) * math.pi / 180
        lon = float(item["longitude"]) * math.pi / 180
    except:
        continue
    x = int(earth_radius * math.cos(lon) * math.sin(lat))
    y = int(earth_radius * math.sin(lat) * math.sin(lon))
    file.write(item["city"] + "," + str(x) + "," + str(y) + "\n")

file.close()
