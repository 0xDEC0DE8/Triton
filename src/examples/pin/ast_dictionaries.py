#!/usr/bin/env python2
## -*- coding: utf-8 -*-
##
## $ ./triton ./src/examples/pin/ast_dictionaries.py ./src/samples/crackmes/crackme_xor elite
##

import sys

from operator   import itemgetter
from pintool    import *
from triton     import *


def cb_fini():
    l = getAstDictionariesStats().items()
    l.sort(key=itemgetter(1), reverse=True)
    print '============================================================='
    print 'AST Dictionaries Stats'
    print '============================================================='
    for i in l:
        if i[1] > 0:
            print '%s: %s' %(i[0], '{:,}'.format(i[1]))
    print '============================================================='
    return


if __name__ == '__main__':
    # Set arch
    setArchitecture(ARCH.X86_64)

    # Start JIT at the entry point
    startAnalysisFromEntry()

    # Use AST Dictionaries
    enableSymbolicOptimization(OPTIMIZATION.AST_DICTIONARIES, True)

    # Add callbacks
    addCallback(cb_fini, CALLBACK.FINI)

    # Run Program
    runProgram()

