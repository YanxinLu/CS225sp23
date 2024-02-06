#include "Image.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

void Image::lighten(){
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel *pixel = getPixel(x, y);
            double newl = pixel->l + 0.1;
            if(newl>1.0) pixel->l = 1.0;
            else pixel->l = newl;
            }
    }
}

void Image::lighten(double amount){
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel *pixel = getPixel(x, y);
            double newl = pixel->l + amount;
            if(newl>1.0) pixel->l = 1.0;
            else pixel->l = newl;
            }
    }
}

void Image::darken(){
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel *pixel = getPixel(x, y);
            double newl = pixel->l - 0.1;
            if(newl<0) pixel->l = 0.0;
            else pixel->l = newl;
            }
    }
}

void Image::darken(double amount){
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel *pixel = getPixel(x, y);
            double newl = pixel->l - amount;
            if(newl<0) pixel->l = 0.0;
            else pixel->l = newl;
            }
    }
}

void Image::saturate(){
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel *pixel = getPixel(x, y);
            double news = pixel->s + 0.1;
            if(news>1.0) pixel->s = 1.0;
            else pixel->s = news;
            }
    }
}

void Image::saturate(double amount){
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel *pixel = getPixel(x, y);
            double news = pixel->s + amount;
            if(news>1.0) pixel->s = 1.0;
            else pixel->s = news;
            }
    }
}

void Image::desaturate(){
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel *pixel = getPixel(x, y);
            double news = pixel->s - 0.1;
            if(news<0.0) pixel->s = 0.0;
            else pixel->s = news;
            }
    }
}

void Image::desaturate(double amount){
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel *pixel = getPixel(x, y);
            double news = pixel->s - amount;
            if(news<0.0) pixel->s = 0.0;
            else pixel->s = news;
            }
    }
}

void Image::grayscale(){
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel *pixel = getPixel(x, y);
            pixel->s = 0.0;
            }
    }
}

void Image::rotateColor(double degrees){
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel *pixel = getPixel(x, y);
            pixel->h += degrees;
            while(pixel->h>=360) pixel->h -= 360;
            while(pixel->h<0) pixel->h += 360;
            }
    }
}

void Image::illinify(){
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel *pixel = getPixel(x, y);
            if(pixel->h>=113.5&&pixel->h<=293.5) pixel->h = 216.0;
            else pixel->h = 11.0;
            }
    }
}

void Image::scale(double factor){
    unsigned neww,newh;
    neww = width()*factor;
    newh = height()*factor;
    Image *scale_tem = new Image;
    scale_tem->resize(neww,newh);
    for (unsigned x = 0; x < neww; x++){
        for (unsigned y = 0; y < newh; y++){
            HSLAPixel *pixel_tem = scale_tem->getPixel(x, y);
            HSLAPixel *pixel_old = getPixel(x/factor, y/factor);
            *pixel_tem = *pixel_old;
        }
    }
    resize(neww,newh);
    for (unsigned x = 0; x < neww; x++){
        for (unsigned y = 0; y < newh; y++){
            HSLAPixel *pixel_temold = scale_tem->getPixel(x, y);
            HSLAPixel *pixel_new = getPixel(x, y);
            *pixel_new = *pixel_temold;
        }
    }
    delete scale_tem;
    scale_tem = nullptr;
}

void Image::scale(unsigned w, unsigned h){
    double factorw = (double)w/(double)width();
    double factorh = (double)h/(double)height();
    if(factorw<factorh) scale(factorw);
    if(factorw>=factorh) scale(factorh);
}