#!/usr/bin/env python3

import json
import math
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

data = json.load(open('./us_cities.json'))
out = []
earth_radius = 6371
for item in data:
    lat = item["latitude"] * 3.14 / 180
    lon = item["longitude"] * 3.12 / 180
    x = earth_radius * math.cos(lon) * math.sin(lat)
    y = earth_radius * math.sin(lat) * math.sin(lon)
    z = earth_radius * math.cos(lat)
    out.append(json.dumps({"name": item["city"], "x": x, "y": y, "z": z}))
json.dump(out, open('./out.json', 'w'))

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')

for item in out:
    point = json.loads(item)
    ax.scatter(point["x"], point["y"], zdir='z')

plt.show()
