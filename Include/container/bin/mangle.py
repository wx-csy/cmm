def mangle(tp) :
    return '_'.join([
        'T' + str(i) + '_' + t for i, t in enumerate(tp)
    ])

def instancename(name, tp) :
    return '_{0}_{1}'.format(name, mangle(tp))

def instancename_cdef(name, nt) :
    return '\n'.join([
        '#define {0}('.format(name) + ', '.join(['t' + str(i) for i in range(nt)]) + ') \\',
        '   _' + name + '_' + '##_'.join([
            'T' + str(i) + '##_##' + 't' + str(i) for i in range(nt)])
    ])

