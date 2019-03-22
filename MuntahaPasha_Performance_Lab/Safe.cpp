#include <stdio.h>
#include "cs1300bmp.h"
#include <iostream>
#include <fstream>
#include "Filter.h"

using namespace std;

#include "rdtsc.h"

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
  //Daclare sample outside of loop to prevent stack from pushing and popping in each iteration of for loop.
  double sample;

  //Initialize values outside of loops. Memory allocation is expensive, so we don't wanna do it in each iteration so we take it out of the for loop, and then reuse those memory allocations instead of allocating every single time. 
  struct cs1300bmp *input = new struct cs1300bmp;
  struct cs1300bmp *output = new struct cs1300bmp; 
 
  for (int inNum = 2; inNum < argc; inNum++) {
    string inputFilename = argv[inNum];
    string outputFilename = "filtered-" + filterOutputName + "-" + inputFilename;

    //Replace ok variable with direct function call
    if ( cs1300bmp_readfile( (char *) inputFilename.c_str(), input)) {

      sample = applyFilter(filter, input, output);
      sum += sample;
      samples++;
      cs1300bmp_writefile((char *) outputFilename.c_str(), output);
    }
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

  //Create local variables instead of dereferenced memory 
  int inWidth = output -> width = input -> width;
  int inHeight = output -> height = input -> height;

  //Calculate outside of loop 
  int inWidthM = inWidth - 1;
  int inHeightM = inHeight - 1;

  //Move call to getSize() outside of loop
  int filterSize = filter -> getSize();

  //Array to hold filter x, y values
  int filterXY[filterSize][filterSize];

  //Moved call to getDivisor out of loop
  int divisor = filter -> getDivisor();

  //New loop to process x, y values outside of main loop
  //get value of row and column from the filter and save it in the array
  for(int i = 0; i < filterSize; i++)
    for(int j = 0; j < filterSize; j++)
      filterXY[i][j] = filter -> get(i, j);

  //Values for each plane in the image, by defining them outsidfe we allocate less space in the strack as opposed to if they were in the for loop.
  int plane1Val, plane2Val, plane3Val,
      plane1Val2, plane2Val2, plane3Val2,
      plane1Val3, plane2Val3, plane3Val3;

  //Switched order of variables from Stride-N^2 to Stride-1
  //Removed outer loop and processed each plane within the current structure
  //Step two rows and columns at a time to reduce iterations
  for(int row = 1; row <= inHeightM; row+=2) {
    for(int col = 1; col <= inWidthM; col+=2) {

      //Reinitialize plane values to 0
      plane1Val = 0;
      plane2Val = 0;
      plane3Val = 0;
      plane1Val2 = 0;
      plane2Val2 = 0;
      plane3Val2 = 0;
      plane1Val3 = 0;
      plane2Val3 = 0;
      plane3Val3 = 0;      
 
      //Switched order of variables from Stride-N to Stride-1
      for (int i = 0; i < filterSize; i++) {

 	//Reinitialize temp variables to 0
	int temp1 = 0;
	int temp2 = 0;
	int temp3 = 0;
	int temp4 = 0;
	int temp5 = 0;
	int temp6 = 0;
	int temp7 = 0;
	int temp8 = 0;
	int temp9 = 0;

	//Initialize row variable outside column loop	
	int r = row + i - 1;
	int r2 = r + 1;

	for (int j = 0; j < filterSize; j++) {
	   
          //Initialize temporary variables to save calculation time that is done below in the temp variables. Like instead of having color[0][r][col+j-1] and doing that over and over, we have c represent [col+j]
	  int xy = filterXY[i][j];
	  int c = col + j - 1;
	  int c2 = c + 1;
	  
	  //Process each plane individually instead of looping.
        //Instead of looping and iterating over it, they manually store the color, row, and column for each pixel value given by xy that was returned in the above function which is responsible for giving us a location to apply that change to.
	  temp1 += input -> color[0][r][c] * xy;
	  temp2 += input -> color[1][r][c] * xy; 
	  temp3 += input -> color[2][r][c] * xy;
	  temp4 += input -> color[0][r][c2] * xy;
	  temp5 += input -> color[1][r][c2] * xy; 
	  temp6 += input -> color[2][r][c2] * xy;
	  temp7 += input -> color[0][r2][c] * xy;
	  temp8 += input -> color[1][r2][c] * xy; 
	  temp9 += input -> color[2][r2][c] * xy;
	}

	//Add temp values to plane values
	plane1Val += temp1;
	plane2Val += temp2;
	plane3Val += temp3;
 	plane1Val2 += temp4;
	plane2Val2 += temp5;
	plane3Val2 += temp6;
  	plane1Val3 += temp7;
	plane2Val3 += temp8;
	plane3Val3 += temp9;
      }
        
        //In the new code they are processing 9 pixels at a time whereas in the old code, they were only processing 1 at a time.

      //Use local divisor variable instead of function call
      //Do not calculate if divisor is 1
      if(divisor != 1){
	plane1Val /= divisor;
	plane2Val /= divisor;
	plane3Val /= divisor;
	plane1Val2 /= divisor;
	plane2Val2 /= divisor;
	plane3Val2 /= divisor;
	plane1Val3 /= divisor;
	plane2Val3 /= divisor;
	plane3Val3 /= divisor;
      }

      //Use nested conditionals instead of if statements
      plane1Val = plane1Val < 0 ? 0 : plane1Val > 255 ? 255 : plane1Val;
      plane2Val = plane2Val < 0 ? 0 : plane2Val > 255 ? 255 : plane2Val;
      plane3Val = plane3Val < 0 ? 0 : plane3Val > 255 ? 255 : plane3Val;
      plane1Val2 = plane1Val2 < 0 ? 0 : plane1Val2 > 255 ? 255 : plane1Val2;
      plane2Val2 = plane2Val2 < 0 ? 0 : plane2Val2 > 255 ? 255 : plane2Val2;
      plane3Val2 = plane3Val2 < 0 ? 0 : plane3Val2 > 255 ? 255 : plane3Val2;
      plane1Val3 = plane1Val3 < 0 ? 0 : plane1Val3 > 255 ? 255 : plane1Val3;
      plane2Val3 = plane2Val3 < 0 ? 0 : plane2Val3 > 255 ? 255 : plane2Val3;
      plane3Val3 = plane3Val3 < 0 ? 0 : plane3Val3 > 255 ? 255 : plane3Val3;
        
    //

      output -> color[0][row][col] = plane1Val;
      output -> color[1][row][col] = plane2Val;
      output -> color[2][row][col] = plane3Val;
      output -> color[0][row][col+1] = plane1Val2;
      output -> color[1][row][col+1] = plane2Val2;
      output -> color[2][row][col+1] = plane3Val2;
      output -> color[0][row+1][col] = plane1Val3;
      output -> color[1][row+1][col] = plane2Val3;
      output -> color[2][row+1][col] = plane3Val3;

    }
  }

  cycStop = rdtscll();
  double diff = cycStop - cycStart;
  double diffPerPixel = diff / (output -> width * output -> height);
  fprintf(stderr, "Took %f cycles to process, or %f cycles per pixel\n",
	  diff, diff / (output -> width * output -> height));
  return diffPerPixel;
}