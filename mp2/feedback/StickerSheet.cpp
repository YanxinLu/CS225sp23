#include "StickerSheet.h"

StickerSheet::StickerSheet():max_(3),curr_(0){
    stickers_ = new Image[max_];
    Basepic_ = new Image;
    x_ = new unsigned[max_];
    y_ = new unsigned[max_];
}

StickerSheet::StickerSheet (const Image &picture, unsigned max):max_(max),curr_(0){
    stickers_ = new Image[max_];
    Basepic_ = new Image;
    *Basepic_ = picture;
    x_ = new unsigned[max_];
    y_ = new unsigned[max_];
}

StickerSheet::~StickerSheet(){
    _destroy();
}

StickerSheet::StickerSheet(const StickerSheet& other){
    _copy(other);
}

const StickerSheet& StickerSheet::operator= (const StickerSheet &rhs){
    if (this == &rhs) return *this;
    _destroy();
    _copy(rhs);
    return *this;
}

void StickerSheet::changeMaxStickers (unsigned max){
    Image* newsti = new Image[max];
    unsigned* newx_ = new unsigned[max];
    unsigned* newy_ = new unsigned[max];
    for(unsigned i=0; i<max; i++){
        newsti[i] = stickers_[i];
        newx_[i] = x_[i];
        newy_[i] = y_[i];
    }
    if(max<curr_) curr_ = max;
    delete[] stickers_;
    delete[] x_;
    delete[] y_;
    stickers_ = newsti;
    x_ = newx_;
    y_ = newy_;
    max_ = max;
}

int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){
    if(curr_ >= max_) return -1;
    stickers_[curr_] = sticker;
    x_[curr_] = x;
    y_[curr_] = y;
    curr_++;
    return curr_-1;
}

bool StickerSheet::translate (unsigned index, unsigned x, unsigned y){
    if(index>=curr_) return false;
    x_[index] = x;
    y_[index] = y;
    return true;
}

void StickerSheet::removeSticker (unsigned index){
    curr_--;
    for(unsigned i=index; i<curr_; i++){
        stickers_[i] = stickers_[i+1];
        x_[i] = x_[i+1];
        y_[i] = y_[i+1];
    }
}

Image* StickerSheet::getSticker (unsigned index) const{
    if(index>=curr_) return nullptr;
    else return &stickers_[index];
}

Image StickerSheet::render () const{
    Image newdrawn(*Basepic_);
    for(unsigned i = 0; i<curr_; i++){
        if(stickers_[i].width()+x_[i]>newdrawn.width()) newdrawn.resize(stickers_[i].width()+x_[i],newdrawn.width());
        if(stickers_[i].height()+y_[i]>newdrawn.height()) newdrawn.resize(newdrawn.width(),stickers_[i].height()+y_[i]);
        for(unsigned x=0; x<stickers_[i].width(); x++){
            for(unsigned y=0; y<stickers_[i].height(); y++){
                cs225::HSLAPixel* basepix = newdrawn.getPixel(x+x_[i],y+y_[i]);
                cs225::HSLAPixel* stickerpix = stickers_[i].getPixel(x,y);
                if(stickerpix->a!=0) *basepix = *stickerpix;
            }
        }
    }
    return newdrawn;
}

//heler functions
void StickerSheet::_copy(const StickerSheet& other){
    max_ = other.max_;
    curr_ = other.curr_;
    stickers_ = new Image[other.max_];
    Basepic_ = new Image;
    *Basepic_ = *(other.Basepic_);
    x_ = new unsigned[other.max_];
    y_ = new unsigned[other.max_];
    for(unsigned i=0; i<curr_; i++){
        stickers_[i] = other.stickers_[i];
        x_[i] = other.x_[i];
        y_[i] = other.y_[i];
    }
}

void StickerSheet::_destroy(){
    delete Basepic_;
    delete[] stickers_;
    delete[] x_;
    delete[] y_;
}