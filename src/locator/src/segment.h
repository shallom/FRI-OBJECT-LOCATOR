#ifndef SEGMENT
#define SEGMENT

#include <cstdio>
#include <cstdlib>
#include <string>
#include "image.h"
#include "misc.h"
#include "pnmfile.h"
#include "segment-image.h"

int numberOfComponents(const char* pic){
  float sigma=.8;
  float k=400;
  int min_size=200;
  
  image<rgb> *input = loadPPM(pic);

  int components;

  image<rgb> *seg = segment_image(input, sigma, k, min_size, &components);

 delete seg;
 return components;
	
}

#endif
