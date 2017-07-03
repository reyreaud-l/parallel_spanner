#!/usr/bin/env python3

import json
import math
import matplotlib.pyplot as plt
import numpy as np

data = json.load(open('./us_cities.json'))
out = []
earth_radius = 6371
for item in data:
    lat = item["latitude"] * math.pi / 180
    lon = item["longitude"] * math.pi / 180
    x = earth_radius * math.cos(lon) * math.sin(lat)
    y = earth_radius * math.sin(lat) * math.sin(lon)
    out.append(json.dumps({"name": item["city"], "x": x, "y": y}))
json.dump(out, open('./out.json', 'w'))

fig = plt.figure()
plt.gca().invert_yaxis()

for item in out:
    point = json.loads(item)
    plt.scatter(point["x"], point["y"])

plt.show()
