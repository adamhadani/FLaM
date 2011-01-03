//
// flamapp.cpp
//
// Main runnable application code for FLaM framework
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>

#include <cxxtools/arg.h>

#include "lineiterator.h"
#include "tokenstream.h"


#define MAX_BUF_SZ 1024


using std::string;
using std::cout;
using std::endl;

using cxxtools::Arg;

//using flam::line_iterator;
//using flam::ngram_iterator;


class FLaMApp 
{
  public:
	enum TaskTypes { tBuildVocabulary, tBuildNGrams };
	std::map<std::string, int> taskMap;

	FLaMApp() {}
	virtual ~FLaMApp() {}

	int buildNGrams(const char* input_fname, const char* output_fname, int min_N=1, int max_N=3);
	int buildVocabulary(const char* input_fname, const char* output_fname);
};

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

	char buf[MAX_BUF_SZ];
	while ( fgets(buf, MAX_BUF_SZ, infile) != NULL ) {
		// tokenize and generate all n-grams
		//while (it = ngramStream.ngram_iter(tokenStream.token_iter(buf)); it != it.end(); ++it) {
			//fprintf(outfile, "%s", *it);
		//}
	}	

	if ( infile != stdin ) {
		fclose(infile);
	}
	if ( outfile != stdout ) {
		fclose(outfile);
	}
	return 0;
}

void usage() {
	fprintf(stderr, "Usage: flamapp --task <task> -i <input_fname> -o <output_fname>\n"
		"Options:\n"
		"    --task \t Task to execute. Valid tasks are 'build_vocabulary', 'build_ngrams'.\n"
		"    -i \t Input file to read from (Use '-' for stdin).\n"
		"    -o \t Output file to write to (NGram model, vocabulary etc.).\n"
	);
}


int main(int argc, char* argv[]) 
{
	// Disable I/O Streams syncing by default
	std::ios_base::sync_with_stdio(false);

	cxxtools::Arg<const char*> task(argc, argv, "--task");
	cxxtools::Arg<const char*> input_fname(argc, argv, 'i', "-");
	cxxtools::Arg<const char*> output_fname(argc, argv, 'o', "-");

	if ( !task || !input_fname || !output_fname ) {
		usage();
		return EXIT_FAILURE;
	}

	FLaMApp app;

	enum FLaMApp::TaskTypes taskType = FLaMApp::tBuildNGrams;

	switch (taskType) {
		case FLaMApp::tBuildNGrams:
			cout << "Building N-Gram file. Input file: " << input_fname << ", Output file: " << output_fname << endl;
			app.buildNGrams(input_fname, output_fname);
			break;
	}

    return EXIT_SUCCESS;
}
