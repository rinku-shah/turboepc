import json
from pprint import pprint

with open('bmv2-s1-netcfg.json') as data_file:    
    data = json.load(data_file)
pprint(data)
