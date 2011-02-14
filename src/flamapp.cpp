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
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>

#include <cxxtools/arg.h>

#include "types.h"
#include "ngram_storage.h"
#include "language_model.h"
#include "stringtokenizer.h"
#include "lineiterator.h"
#include "vocabulary.h"
#include "utils.h"

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
	enum TaskTypes { tBuildWordFreq, tBuildNGrams, tBuildIDNGrams, tBuildLM };
	std::map<std::string, int> taskMap;

	FLaMApp(size_t wordLenThres=20) : wordLenThres(wordLenThres) {}
	virtual ~FLaMApp() {}

	int buildNGrams(const char* input_fname, const char* output_fname, size_t n);
	int buildIDNGrams(const char* input_fname, const char* output_fname, size_t n, const char* vocab_fname);
	int buildWFreq(const char* input_fname, const char* output_fname);
	int buildLM(const char* idngram_fname, const char* vocab_fname, const char* output_fname, size_t n, int discount_method);

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

	flmchar_t *line = lineiterator.next();
	flmchar_t *tok=NULL, *normalized_tok=NULL;

	while (line) {
		tokenizer.setString(line);
		tok = tokenizer.next();
		while (tok) {
		    normalized_tok = lower_case(tok);

		    if ( vocabulary->hasKey(normalized_tok) ) {
                // term already exists in vocabulary,
                // free up memory for current term
                // and increase word frequency count
		        vocabulary->inc(normalized_tok, 1);
                delete normalized_tok;
		    } else {
		        // Add new key.
		        // NOTE: this references the pointer,
		        // so should not free up the memory
		        // pointed to!
                vocabulary->addKey(normalized_tok);
		    }

            tok = tokenizer.next();
		}

        line = lineiterator.next();
	}

	// Emit vocabulary
	HashVocabulary* hash_vocab = dynamic_cast<HashVocabulary *>(vocabulary);
    HashVocabulary::SymbolMap::iterator it = hash_vocab->begin();
    for (; it != hash_vocab->end(); ++it)
    {
        // Prune words longer than our threshold
        if ( flmstrlen(it->first) > wordLenThres ) {
            //fprintf(stderr, "Skipping long word: %s\n", it->first);
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

    // Free resources used
    delete vocabulary;
    vocabulary = hash_vocab = NULL;

    return 0;
}

/**
 * Emit all ngrams of order [min_N, max_N] from input text
 *
 */
int FLaMApp::buildNGrams(const char* input_fname, const char* output_fname, size_t n)
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
    int min_N=n, max_N=n;
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

int FLaMApp::buildIDNGrams(const char* input_fname, const char* output_fname, size_t n, const char* vocab_fname)
{
	FILE *infile=NULL, *outfile=NULL, *vocabfile=NULL;
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
    vocabfile = fopen(vocab_fname, "r");

	// Populate vocabulary ID mapping from file
    HashVocabulary* vocabulary = HashVocabulary::fromFile(vocabfile);

    // Generate ID NGrams from input stream
    StringTokenizer tokenizer;
    LineIterator lineiterator(infile);

    int i,j,N,pos,m;
    int min_N=n, max_N=n;
	flmchar_t *tok=NULL, *normalized_tok=NULL;

	std::vector<flmwid_t> ids;
    std::stringstream ngram;

	// For each line
	flmchar_t* line = lineiterator.next();
	while (line) {
	    ids.clear();
        N=0;

		// tokenize
		tokenizer.setString(line);
		tok = tokenizer.next();
		while ( tok != NULL ) {
		    normalized_tok = lower_case(tok, true);
		    flmwid_t id = vocabulary->getValue(normalized_tok);
		    ids.push_back(id);
            tok = tokenizer.next();
            ++N;
		}

		// Emit all N-Grams of order [min_N, max_N]
		m = (N < max_N) ? N : max_N;
        for (i=min_N; i<m+1; ++i) {
            for (pos=0; pos < (N-i+1); ++pos) {
                ngram.str(std::string());
                ngram << ids[pos];
                for (j=pos+1;j<pos+i; ++j) {
                    ngram << " " << ids[j];
                }
                fprintf(outfile, "%s\n", ngram.str().c_str());
            }
		}

		line = lineiterator.next();
	}

    // Free up memory
    delete vocabulary;

    // Close file handles
	if ( infile != stdin ) {
		fclose(infile);
	}
	if ( outfile != stdout ) {
		fclose(outfile);
	}
	fclose(vocabfile);

	return 0;
}

/**
 * Build language model based on vocabulary
 * and (id) ngrams input stream
 *
 */
int FLaMApp::buildLM(const char* idngram_fname, const char* vocab_fname, const char* output_fname, size_t n, int discount_method)
{
	FILE *idngramfile=NULL, *outfile=NULL, *vocabfile=NULL;
	if ( !strcmp(idngram_fname, "-") ) {
		idngramfile = stdin;
	}
	else {
		idngramfile = fopen(idngram_fname, "r");
	}
	if ( !strcmp(output_fname, "-") ) {
		outfile = stdout;
	}
	else {
		outfile = fopen(output_fname, "w");
	}
    vocabfile = fopen(vocab_fname, "r");

    printf("Reading vocabulary...\n");
    Vocabulary* vocabulary = HashVocabulary::fromFile(vocabfile);

    LanguageModel *lm = new BackoffLanguageModel(n, vocabulary);

    // Create the n-gram model tree from ngram data

    flmngram_t curr_ngram;
    curr_ngram.n = n;
    curr_ngram.id_array = static_cast<flmwid_t *>(calloc(n, sizeof(flmwid_t)));

    printf("Reading ngrams...\n");
    while ( !feof(idngramfile) ) {

        // Read current ngram
        get_ngram(idngramfile, curr_ngram);

        // Add to model
        //lm->addNGram(curr_ngram);
    }

    // Calculate discounted counts

    // Perform any additional smoothing

    // Calculate backoff weights

    // Write out to file
    lm->save(outfile);

    // Free up resources
    delete lm;

    // Close file handles
	if ( idngramfile != stdin ) {
		fclose(idngramfile);
	}
	if ( outfile != stdout ) {
		fclose(outfile);
	}
	fclose(vocabfile);

    return 0;
}

void usage()
{
	fprintf(stderr, "Usage: flamapp --task <task> [-n <model_order>] [--vocabulary <vocab_fname>] [--discount <discount_method>] -i <input_fname> -o <output_fname>\n"
		"Options:\n"
		"    -i \t Input file to read from (Use '-' for stdin).\n"
		"    -o \t Output file to write to (Use '-' for stdout).\n"
		"    -n \t Model order (n-gram order).\n"
		"    --task \t Task to execute. Valid tasks are 'text2wfreq', 'text2wngram', 'text2idngram', 'idngram2lm'.\n"
		"    --vocabulary Vocabulary filename (as generated by wfreq2vocab/text2vocab).\n"
		"    --discount Discounting method used for LM. Valid methods are 1 - 'goodturing', 2 - 'linear', 3 - 'absolute'\n"
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
	cxxtools::Arg<int> n(argc, argv, 'n', 3);
	cxxtools::Arg<const char*> vocab(argc, argv, "--vocabulary");
	cxxtools::Arg<int> discount(argc, argv, "--discount");

    // Define maps enumerations. These are based on
    // the CMU toolkit.
	std::map<std::string, FLaMApp::TaskTypes> tasksMap;
	tasksMap["text2wfreq"] = FLaMApp::tBuildWordFreq;
	tasksMap["text2wngram"] = FLaMApp::tBuildNGrams;
	tasksMap["text2idngram"] = FLaMApp::tBuildIDNGrams;
	tasksMap["idngram2lm"] = FLaMApp::tBuildLM;

	if ( tasksMap.find(task) == tasksMap.end() || !input_fname || !output_fname ||
         (tasksMap[task] == FLaMApp::tBuildIDNGrams && !vocab) ) {
		usage();
		return EXIT_FAILURE;
	}

	FLaMApp app;

	enum FLaMApp::TaskTypes taskType = tasksMap[task];
	switch (taskType) {
		case FLaMApp::tBuildNGrams:
			cerr << "Building N-Grams file. Input file: " << input_fname << ", Output file: " << output_fname << endl;
			app.buildNGrams(input_fname, output_fname, n);
			break;
		case FLaMApp::tBuildWordFreq:
			cerr << "Building Word Frequencies file. Input file: " << input_fname << ", Output file: " << output_fname << endl;
			app.buildWFreq(input_fname, output_fname);
			break;
		case FLaMApp::tBuildIDNGrams:
			cerr << "Building ID N-Grams file. Input file: " << input_fname << ", Output file: " << output_fname << endl;
			app.buildIDNGrams(input_fname, output_fname, n, vocab);
			break;
		case FLaMApp::tBuildLM:
			cerr << "Building Language Model. Input file: " << input_fname << ", Output file: " << output_fname << endl;
			app.buildLM(input_fname, vocab, output_fname, n, discount);
			break;
	}

    return EXIT_SUCCESS;
}
