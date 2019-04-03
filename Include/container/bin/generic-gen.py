#!/usr/bin/env python2
import sys
import yaml
from mangle import *

cfg = yaml.load(sys.stdin.read(), Loader=yaml.FullLoader)
name = cfg['name']
types = cfg['types']

for tp in types :
    print '#include "container/{0}/{1}.inst.hh"'.format(name, mangle(tp))
print

for funcname, argc in cfg['functions'].items() :
    arglist = ', '.join(['a' + str(aid) for aid in range(argc)])
    print '#define {0}_{1}'.format(name, funcname) + \
        '(' + arglist + ') \\'
    print '    _Generic((a0), \\'
    for tp in types :
        print '        ' + tp + ': ' + \
            '_{0}_{1}_{2}'.format(name, tp, funcname) + \
            ', \\'
    print '    )(' + arglist + ')'
    print 
