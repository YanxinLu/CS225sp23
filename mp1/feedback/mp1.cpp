#include "mp1.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
    PNG input;
    input.readFromFile(inputFile);
    PNG output(input.width(),input.height());
    for(unsigned int y=0; y<input.height();y++){
        for(unsigned int x=0; x<input.width();x++){
            HSLAPixel *p_in = input.getPixel(x,y);
            HSLAPixel *p_out = output.getPixel(input.width()-x-1,input.height()-y-1);
            *p_out = *p_in;
        }
    }
    output.writeToFile(outputFile);
}
