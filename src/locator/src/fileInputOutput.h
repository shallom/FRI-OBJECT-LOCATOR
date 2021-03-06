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

#ifndef FILE_INPUT_OUPUT
#define FILE_INPUT_OUTPUT

#include <iostream>
#include <fstream>
#include <string>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

class file_error { };

	string readFromFile(const char* outputFileLoc){
		ifstream outputFile (outputFileLoc);
		string line;
	
		if(outputFile.is_open()){
			getline(outputFile, line);
			outputFile.close();
			return line;
		}else
			throw file_error();
	}


	bool writeToFile(const char* input, const char* inputFileLoc){
		ofstream inputFile (inputFileLoc);
	
		if(inputFile.is_open()){
			inputFile << input;
			inputFile.close();
			return true;
		}else
			throw file_error();
		return false;
	}

	string getToken(){
		ifstream outputFile ("../object_locator/src/locator/src/text_files/token.txt");
		string line;
		char lineArr[1024];
		string token;
	
		if(outputFile.is_open()){
			while(getline(outputFile, line)){
				string first (line.begin(), line.begin()+1);
				if(first.compare("{")==0){
					strncpy(lineArr, line.c_str(), sizeof(lineArr));
					break;
				}
			}
		
			int start=0, end=0;
			bool canTerm=false;
		
			while(!canTerm){
				if(lineArr[end]==':'){
					end++;
					start=++end;
					canTerm=true;
				}
				while(canTerm){
					if(lineArr[end]=='"'){
						end=end-start;
						string tok (line, start, end);
						return tok;
					}
					end++;
				}
				end++;
			}
			return token;
		}else 
			throw file_error();
	}



#endif
