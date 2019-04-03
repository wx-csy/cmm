#!/usr/bin/env python2
import sys
import yaml
from mangle import *

cfg = yaml.load(sys.stdin.read())
name = cfg['name']
tn = cfg['typename']
types = cfg['types']

print 'INST_TARGETS = \\'
for tp in types :
    print '    ' + mangle(tp) + '.inst.hh \\'
print
print

def gen_subst(pat, to) :
    return '-e "s/{0}/{1}/g"'.format(pat, to)

for tp in types :
    print mangle(tp) + '.inst.hh : impl.h'
    print '\t@echo [GEN] ', '"<' + ', '.join(tp) + '>"', '"($@)"'
    print '\t@echo "#line 1" \'"{0}"\''.format('container/{0}/impl.h'.format(name)), '> $@'
    print '\t@sed', ' '.join([gen_subst('@({0})'.format(tpname), t)
         for tpname, t in zip(tn, tp)] + [
            gen_subst('@(MANGLE)', instancename(name, tp))     
         ]), \
        '$<', '>> $@'
    print
