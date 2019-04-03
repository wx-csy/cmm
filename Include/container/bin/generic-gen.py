#!/usr/bin/env python2
import sys
import yaml
from mangle import *

cfg = yaml.load(sys.stdin.read())
name = cfg['name']
tn = cfg['typename']
types = cfg['types']

print instancename_cdef(name, len(tn))
print

for tp in types :
    print '#include "container/{0}/{1}.inst.hh"'.format(name, mangle(tp))
print

for funcname, argc in cfg['functions'].items() :
    print '#define {0}_{1}'.format(name, funcname) + \
        '(' + ', '.join(['a' + str(aid) for aid in range(argc)]) + ') \\'
    print '    _Generic((a0) \\'
    for tp in types :
        print '        , struct ' + instancename(name, tp) + ' : ' + \
            '{0}_{1}'.format(instancename(name, tp), funcname) + \
            ' \\'
    print '    )(' + ', '.join([('&(' if aid == 0 else '(') + 'a' + str(aid) + ')' 
        for aid in range(argc)]) + ')'
    print 
