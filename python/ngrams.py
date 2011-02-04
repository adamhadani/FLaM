#!/usr/bin/env python
#
# Simple python-based ngram generator.
#

import os
import sys
from itertools import imap

def main(argv):
    min_N=3; max_N=3;

    for line in imap(lambda x: x.strip(), sys.stdin):
        tokens = line.split(" ")
        N = len(tokens)
        max_NN = min(N, max_N)
        for i in xrange(min_N, max_NN+1):
            for pos in xrange(0, N-i+1):
                print " ".join(tokens[pos:pos+i])

if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))

