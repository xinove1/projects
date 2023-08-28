#!/usr/bin/env python3

import requests
import json

url1 = 'https://api.pi.delivery/v1/pi?start='
url2 = '&numberOfDigits=1000&radix=10'
offset = 1000

i = 1000000

f = open("test.txt", "a")

while i != 10000000:
    x = requests.get(url1 + str(i) + url2)
    j = json.loads(x.content)
    f.write(j["content"])
    i += offset

f.close()
