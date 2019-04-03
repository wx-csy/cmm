#!/usr/bin/env python2
import sys
import yaml
from mangle import *

def mangle(tp) :
    return '_'.join([
        'T' + int(i) + '_' + t for i, t in enumerate(tp)
    ])

cfg = yaml.load(sys.stdin.read(), Loader=yaml.FullLoader)
name = cfg['name']
types = cfg['types']

print 'INST_TARGETS = \\'
for tp in types :
    print '    ' + mangle(tp) + '.inst.hh \\'
print
print

for tp in types :
    print magle(tp) + '.inst.hh'
