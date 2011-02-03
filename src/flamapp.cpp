/*
 *
 * Main runnable application code for FLaM framework
 *
 * @author Adam Ever-Hadani <adamhadani@videosurf.com>
 *
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <math.h>

#include <cxxtools/arg.h>

#include "stringtokenizer.h"
#include "lineiterator.h"
#include "vocabulary.h"


using std::string;
using std::vector;
using std::map;
using std::cout;
using std::cerr;
using std::endl;

using cxxtools::Arg;
using namespace FLaM;

class FLaMApp
{
  public:
	enum TaskTypes { tBuildWordFreq, tBuildVocabulary, tBuildNGrams, tBuildIDNGrams };
	std::map<std::string, int> taskMap;

	FLaMApp(size_t wordLenThres=20) : wordLenThres(wordLenThres) {}
	virtual ~FLaMApp() {}

	int buildNGrams(const char* input_fname, const char* output_fname, int min_N=1, int max_N=3);
	int buildIDNGrams(const char* input_fname, const char* output_fname, int min_N=1, int max_N=3);
	int buildWFreq(const char* input_fname, const char* output_fname);

  private:
    const size_t wordLenThres;
};

/**
 * Build word frequencies from input text.
 *
 */
int FLaMApp::buildWFreq(const char* input_fname, const char* output_fname)
{
	FILE *infile=NULL, *outfile=NULL;
	if ( !strcmp(input_fname, "-") ) {
		infile = stdin;
	}
	else {
		infile = fopen(input_fname, "r");
	}
	if ( !strcmp(output_fname, "-") ) {
		outfile = stdout;
	}
	else {
		outfile = fopen(output_fname, "w");
	}

    StringTokenizer tokenizer(" \t");
	LineIterator lineiterator(infile);

	Vocabulary* vocabulary = new HashVocabulary();

	flmchar_t *line = lineiterator.next(), *tok=NULL;
	while (line) {
		tokenizer.setString(line);
		tok = tokenizer.next();
		while ( tok != NULL ) {
            vocabulary->inc(tok, 1);

            tok = tokenizer.next();
		}

        line = lineiterator.next();
	}

	// Emit vocabulary
	HashVocabulary* hash_vocab = dynamic_cast<HashVocabulary *>(vocabulary);
    HashVocabulary::SymbolMap::iterator it = hash_vocab->begin();
    for (; it != hash_vocab->end(); ++it)
    {
        // Prune words with length above a certain threshold
        if ( flmstrlen(it->first) > wordLenThres ) {
            fprintf(stderr, "Skipping long word: %s\n", it->first);
            continue;
        }

        fprintf(outfile, "%i\t%s\n", it->second, it->first);
    }

	if ( infile != stdin ) {
		fclose(infile);
	}
	if ( outfile != stdout ) {
		fclose(outfile);
	}
    return 0;
}

/**
 * Emit all ngrams of order [min_N, max_N] from input text
 *
 */
int FLaMApp::buildNGrams(const char* input_fname, const char* output_fname, int min_N, int max_N)
{
	FILE *infile=NULL, *outfile=NULL;
	if ( !strcmp(input_fname, "-") ) {
		infile = stdin;
	}
	else {
		infile = fopen(input_fname, "r");
	}
	if ( !strcmp(output_fname, "-") ) {
		outfile = stdout;
	}
	else {
		outfile = fopen(output_fname, "w");
	}

    StringTokenizer tokenizer;
    LineIterator lineiterator(infile);

    int i,j,N,pos,m;
	flmchar_t* line = NULL;
	flmchar_t* tok = NULL;

	std::vector<std::string> tokens;
    std::string ngram;

	// For each line
	line = lineiterator.next();
	while (line) {
	    tokens.clear();
        N=0;

		// tokenize
		tokenizer.setString(line);
		tok = tokenizer.next();
		while ( tok != NULL ) {
		    tokens.push_back(tok);
            tok = tokenizer.next();
            ++N;
		}

		// Emit all N-Grams of order [min_N, max_N]
		m = (N < max_N) ? N : max_N;
        for (i=min_N; i<m+1; ++i) {
            for (pos=0; pos < (N-i+1); ++pos) {
                ngram.clear();
                ngram = tokens[pos];

                for (j=pos+1;j<pos+i; ++j) {
                    ngram += " " + tokens[j];
                }
                fprintf(outfile, "%s\n", ngram.c_str());
            }
		}

		line = lineiterator.next();
	}

	if ( infile != stdin ) {
		fclose(infile);
	}
	if ( outfile != stdout ) {
		fclose(outfile);
	}
	return 0;
}

int FLaMApp::buildIDNGrams(const char* input_fname, const char* output_fname, int min_N, int max_N)
{
    return 0;
}

void usage()
{
	fprintf(stderr, "Usage: flamapp --task <task> -i <input_fname> -o <output_fname>\n"
		"Options:\n"
		"    --task \t Task to execute. Valid tasks are 'text2wfreq', 'text2wngram', 'text2idngram'.\n"
		"    -i \t Input file to read from (Use '-' for stdin).\n"
		"    --min_N \t Used with text2wngram, minimal order of ngrams to extract.\n"
		"    --max_N \t Used with text2wngram, maximal order of ngrams to extract.\n"
		"    -o \t Output file to write to (NGram model, vocabulary etc.).\n"
	);
}

int main(int argc, char* argv[])
{
	// Disable I/O Streams syncing by default
	std::ios_base::sync_with_stdio(false);

	// Parse command line options
	cxxtools::Arg<std::string> task(argc, argv, "--task");
	cxxtools::Arg<const char*> input_fname(argc, argv, 'i', "-");
	cxxtools::Arg<const char*> output_fname(argc, argv, 'o', "-");
	cxxtools::Arg<int> min_N(argc, argv, "--min_N", 1);
	cxxtools::Arg<int> max_N(argc, argv, "--max_N", 3);

    // Define maps enumerations. These are based on
    // the CMU toolkit.
	std::map<std::string, FLaMApp::TaskTypes> tasksMap;
	tasksMap["text2wfreq"] = FLaMApp::tBuildWordFreq;
	tasksMap["text2wngram"] = FLaMApp::tBuildNGrams;
	tasksMap["text2idngram"] = FLaMApp::tBuildIDNGrams;

	if ( tasksMap.find(task) == tasksMap.end() || !input_fname || !output_fname ) {
		usage();
		return EXIT_FAILURE;
	}

	FLaMApp app;

	enum FLaMApp::TaskTypes taskType = tasksMap[task];

	switch (taskType) {
		case FLaMApp::tBuildNGrams:
			cerr << "Building N-Grams file. Input file: " << input_fname << ", Output file: " << output_fname << endl;
			app.buildNGrams(input_fname, output_fname, min_N, max_N);
			break;
		case FLaMApp::tBuildWordFreq:
			cerr << "Building Word Frequencies file. Input file: " << input_fname << ", Output file: " << output_fname << endl;
			app.buildWFreq(input_fname, output_fname);
			break;
		case FLaMApp::tBuildIDNGrams:
			cerr << "Building ID N-Grams file. Input file: " << input_fname << ", Output file: " << output_fname << endl;
			app.buildIDNGrams(input_fname, output_fname);
			break;
	}

    return EXIT_SUCCESS;
}
