
/*
Copyright (C) 2015 Shallom Onoja

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/

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
