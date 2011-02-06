#!/usr/bin/env python
"""
Prototyping for creating a (binary) language model
from computed id ngram counts (and vocabulary)
"""

import os
import re
import sys
import csv
import logging
from itertools import imap
from optparse import OptionParser
from collections import defaultdict
from abc import ABCMeta, abstractmethod

class Node(object):
    """Represent node in a tree"""

    def __init__(self):
        self.children = {}
        self.values = {}


class Vocabulary(object):
    """Represent a model vocabulary"""

    __metaclass__ = ABCMeta

    @abstractmethod
    def add(self, term):
        """Add a term to vocabulary"""

    @abstractmethod
    def get_id(self, term):
        """Get term ID mapping"""

class HashVocabulary(object):
    """Hash-based vocabulary implementation"""

    def __init__(self):
        Vocabulary.__init__(self)
        self._sym_map = {}
        self._last_id = 1

    def add(self, term):
        idx = self._last_id+1
        self._sym_map[idx] = term
        self._last_id += 1

    def get_id(self, term):
        return self._sym_map.get(term, 0)

    @classmethod
    def from_file(cls, filename):
        vocab = HashVocabulary()
        with closing(open(filename, 'r')) as ifh:
            for line in imap(lambda x: x.strip(), ifh):
                vocab.add(line)
        return vocab

class LangModel(object):
    """Base class for language model"""

    __metaclass__ = ABCMeta

    def __init__(self, vocabulary, n):
        self._root = {}
        self._vocabulary = vocabulary
        self._n = n

    @abstractmethod
    def add_ngram(self, ngram, count, overwrite=False):
        """Add an (id) ngram to model,
        with associated given count.
        If ngram already exists, will either
        adjust count or do nothing, based on
        overwrite flag"""

    @abstractmethod
    def get_count(self, ngram):
        """Get raw count for ngram given as sequence of tokens"""

    @abstractmethod
    def get_prob(self, text):
        """Get computed probability for given text"""


class DiscountedLangModel(LangModel):
    """Base line MLE language model"""

    def __init__(self, n, disc_model=None):
        LangModel.__init__(self, n)
        self._disc_model = disc_model

    def add_ngram(ngram, count, overwrite=False):
        """Add ngram to model"""
        curr_node = self._root
        curr_idx = 0
        n = self._n
        
        # Traverse tree adding nodes as needed
        for curr_idx in xrange(n-1):
            if ngram[curr_idx] in curr_node.children:
                curr_node = curr_node[ngram[curr_idx]]
            else:
                # Add new node and link to current one
                new_node = Node()
                new_node.values.setdefault('count', 0)
                new_node.values['count'] += count
                curr_node.children[ngram[curr_idx]] = new_node

        # Add leaf node
        curr_node[ngram[-1]] = Node()
        curr_node[ngram[-1]].values['count'] = count

    def get_count(self, ngram):
        idngram = imap(lambda x: self._vocabulary.get_id(x))
        curr_node = self._root
        curr_idx = 0
        L = len(ngram)

        while curr_idx < L:
            if idngram[curr_idx] in curr_node.children:
                curr_node = curr_node.children[idngram[curr_idx]]
                curr_idx += 1
            else:
                # Could not find ngram prefix, break out
                return None 

        return curr_node.values['count']
            
        
    def get_prob(self, text):
        """Get probability of text using current language model"""
        idstream = imap(lambda x: self._vocabulary.get_id(x), text)        
        
class AbsDisc(object):
    """Discount method"""

class GoodTuringDisc(object):
    """Discount method based on 
    the Good-Turing estimator"""

def parse_args():
    usage = "%prog -i <idngram_file> [-v <vocab_file>] -o <output_file> -n <model_order>"
    parser = OptionParser(usage=usage)

    parser.add_option("-i", dest="idngram_file", help="ID Ngrams file")
    parser.add_option("-v", dest="vocab_file", help="Vocabulary file")
    parser.add_option("-o", dest="output_file", help="Output file")
    parser.add_option("-n", dest="n", type=int, help="Model order")

    options, args = parser.parse_args()

    if not options.idngram_file or \
        not options.output_file or \
        not options.n:
        parser.error("Missing arguments. See --help for usage instructions.")

    return options, args

def main():
    options, args = parse_args()
    logging.basicConfig(
        level = logging.DEBUG
    )

    # Load up vocabulary mapping
    vocabulary = HashVocabulary.from_file(options.vocab_file)
    lm = MLELangModel(vocabulary=vocabulary, n=options.n)

    ifs = open(options.idngram_file, "r")
    #ofs = open(options.output_file, "w")

    for line in imap(lambda x: x.strip(), ifs):
        row = line.split(" ")
        count = row.pop(); idngram = row

        lm.add_ngram(idngram, count=count)

    # Evaluate / sanity checks
    logging.info("C['how to'] = %s", lm.get_count(('how', 'to'))) 

    ifs.close()
    #ofs.close()    

if __name__ == "__main__":
    sys.exit(main())
