#ifndef HSLAPIXEL_H
#define HSLAPIXEL_H

using namespace std;

namespace cs225{
    class HSLAPixel{
        public:
        //constructor
        HSLAPixel ();
        HSLAPixel (double hue, double saturation, double luminance);
        HSLAPixel (double hue, double saturation, double luminance, double alpha);
        //hue
        double h;
        //saturation
        double s;
        //luminance
        double l;
        //alpha
        double a;
    };
}



#endif