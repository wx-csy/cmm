def mangle(tp) :
    return '_'.join([
        'T' + int(i) + '_' + t for i, t in enumerate(tp)
    ])
