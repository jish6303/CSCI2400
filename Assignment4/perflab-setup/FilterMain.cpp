#include <stdio.h>
#include "cs1300bmp.h"
#include <iostream>
#include <fstream>
#include "Filter.h"

using namespace std;

#include "rtdsc.h"

//
// Forward declare the functions
//
Filter * readFilter(string filename);
double applyFilter(Filter *filter, cs1300bmp *input, cs1300bmp *output);

int
main(int argc, char **argv)
{

  if ( argc < 2) {
    fprintf(stderr,"Usage: %s filter inputfile1 inputfile2 .... \n", argv[0]);
  }

  //
  // Convert to C++ strings to simplify manipulation
  //
  string filtername = argv[1];

  //
  // remove any ".filter" in the filtername
  //
  string filterOutputName = filtername;
  string::size_type loc = filterOutputName.find(".filter");
  if (loc != string::npos) {
    //
    // Remove the ".filter" name, which should occur on all the provided filters
    //
    filterOutputName = filtername.substr(0, loc);
  }

  Filter *filter = readFilter(filtername);

  double sum = 0.0;
  int samples = 0;

  for (int inNum = 2; inNum < argc; inNum++) {
    string inputFilename = argv[inNum];
    string outputFilename = "filtered-" + filterOutputName + "-" + inputFilename;
    struct cs1300bmp *input = new struct cs1300bmp;
    struct cs1300bmp *output = new struct cs1300bmp;
    int ok = cs1300bmp_readfile( (char *) inputFilename.c_str(), input);

    if ( ok ) {
      double sample = applyFilter(filter, input, output);
      sum += sample;
      samples++;
      cs1300bmp_writefile((char *) outputFilename.c_str(), output);
    }
    delete input;
    delete output;
  }
  fprintf(stdout, "Average cycles per sample is %f\n", sum / samples);

}

struct Filter *
readFilter(string filename)
{
  ifstream input(filename.c_str());

  if ( ! input.bad() ) {
    int size = 0;
    input >> size;
    Filter *filter = new Filter(size);
    int div;
    input >> div;
    filter -> setDivisor(div);
    for (int i=0; i < size; i++) {
      for (int j=0; j < size; j++) {
	int value;
	input >> value;
	filter -> set(i,j,value);
      }
    }
    return filter;
  }
}


double
applyFilter(struct Filter *filter, cs1300bmp *input, cs1300bmp *output)
{

	long long cycStart, cycStop;
	cycStart = rdtscll();
	int a=input -> height;
	int b=input -> width;
	int getdivi=filter -> getDivisor();
	int width=output -> width;
	int height=output -> height;
	width = b;
	height = a;
    int myFilter[3][3];
	for (int i=0; i<3; i++){
		for(int j=0;j<3;j++){
			myFilter[i][j]=filter->get(i,j);
		}
	}   

  for(int plane = 0; plane < 3; plane++) {
    for(int row = 1; row < a - 1 ; row = row + 1) {
      for(int col = 1; col < b - 1; col = col + 1) {         
		int pixel= 0;
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++) {	
			pixel+= (input -> color[plane][row + i - 1][col + j - 1]* myFilter[i][j] );
	  }
	}
	pixel =pixel >> getdivi;
	if ( pixel  < 0 ) {
	  pixel = 0;
	}
	if ( pixel  > 255 ) { 
		  pixel=255;
		  output->color[plane][row][col]=pixel;
		}
      }
    }
  }

  cycStop = rdtscll();
  double diff = cycStop - cycStart;
  double diffPerPixel = diff / (width * height);
  fprintf(stderr, "Took %f cycles to process, or %f cycles per pixel\n", diff, diffPerPixel);
  return diffPerPixel;
}
