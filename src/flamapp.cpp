//
// flamapp.cpp
//
// Main runnable application code for FLaM framework
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <math.h>

#include <cxxtools/arg.h>

#define MIN(X,Y) ((X) < (Y) ? : (X) : (Y))
#define MAX_BUF_SZ 256
#define TCHAR wchar_t

using std::string;
using std::vector;
using std::map;
using std::cout;
using std::cerr;
using std::endl;

using cxxtools::Arg;


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

int FLaMApp::buildVocabulary(const char* input_fname, const char* output_fname)
{
    return 0;
}

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

    int i,j,N,pos,m;
	char buf[MAX_BUF_SZ];
	char *tok = NULL;

	std::vector<std::string> tokens;
    std::string ngram;

	// For each line
	while ( fgets(buf, MAX_BUF_SZ, infile) != NULL ) {
	    // strip newline
        char *nlptr = strchr(buf, '\n');
        if (nlptr) *nlptr = '\0';

	    tokens.clear();
        N=0;

		// tokenize
		tok = strtok(buf, " ");
		while ( tok != NULL ) {
		    tokens.push_back(tok);
            tok = strtok(NULL, " ");
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
	}

	if ( infile != stdin ) {
		fclose(infile);
	}
	if ( outfile != stdout ) {
		fclose(outfile);
	}
	return 0;
}

void usage()
{
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
	cxxtools::Arg<std::string> task(argc, argv, "--task");
	cxxtools::Arg<const char*> input_fname(argc, argv, 'i', "-");
	cxxtools::Arg<const char*> output_fname(argc, argv, 'o', "-");
	cxxtools::Arg<int> min_N(argc, argv, "--min_N", 1);
	cxxtools::Arg<int> max_N(argc, argv, "--max_N", 3);

	std::map<std::string, FLaMApp::TaskTypes> tasksMap;
	tasksMap["build_ngrams"] = FLaMApp::tBuildNGrams;
	tasksMap["build_vocabulary"] = FLaMApp::tBuildVocabulary;

	if ( tasksMap.find(task) == tasksMap.end() || !input_fname || !output_fname ) {
		usage();
		return EXIT_FAILURE;
	}

	FLaMApp app;

	enum FLaMApp::TaskTypes taskType = tasksMap[task];

	switch (taskType) {
		case FLaMApp::tBuildNGrams:
			cerr << "Building N-Gram file. Input file: " << input_fname << ", Output file: " << output_fname << endl;
			app.buildNGrams(input_fname, output_fname, min_N, max_N);
			break;
		case FLaMApp::tBuildVocabulary:
			cerr << "Building Vocabulary file. Input file: " << input_fname << ", Output file: " << output_fname << endl;
			app.buildVocabulary(input_fname, output_fname);
			break;
	}

    return EXIT_SUCCESS;
}
