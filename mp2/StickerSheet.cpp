#include "StickerSheet.h"

StickerSheet::StickerSheet():max_(3),maxcnt_(0){
    stickers_ = new Image[max_];
    Basepic_ = new Image;
    x_ = new unsigned[max_];
    y_ = new unsigned[max_];
    valid_ =new unsigned[max_];
}

StickerSheet::StickerSheet (const Image &picture, unsigned max):max_(max),maxcnt_(0){
    stickers_ = new Image[max_];
    Basepic_ = new Image;
    *Basepic_ = picture;
    x_ = new unsigned[max_];
    y_ = new unsigned[max_];
    valid_ = new unsigned[max_];
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
    unsigned* newv_ = new unsigned[max];
    if(max<maxcnt_) maxcnt_ = max;
    for(unsigned i=0; i<maxcnt_; i++){
        newsti[i] = stickers_[i];
        newx_[i] = x_[i];
        newy_[i] = y_[i];
        newv_[i] = valid_[i];
    }
    delete[] stickers_;
    delete[] x_;
    delete[] y_;
    delete[] valid_;
    stickers_ = newsti;
    x_ = newx_;
    y_ = newy_;
    valid_ = newv_;
    max_ = max;
}

int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){
    //check valid
    unsigned i;
    for(i=0; i<maxcnt_; i++){
        if(valid_[i]!=1) break;
    }
    //nothing avaliable
    if(i==maxcnt_&&maxcnt_>=max_) return -1;
    //index i avaliabel
    if(i!=maxcnt_){
        stickers_[i] = sticker;
        x_[i] = x;
        y_[i] = y;
        valid_[i] = 1;
        return i;
    }
    //all valid
    stickers_[maxcnt_] = sticker;
    x_[maxcnt_] = x;
    y_[maxcnt_] = y;
    valid_[maxcnt_] = 1;
    maxcnt_++;
    return maxcnt_-1;
}

bool StickerSheet::translate (unsigned index, unsigned x, unsigned y){
    if(index>=maxcnt_) return false;
    if(valid_[index]!=1) return false;
    x_[index] = x;
    y_[index] = y;
    return true;
}

void StickerSheet::removeSticker (unsigned index){
    if(index>=maxcnt_||maxcnt_==0) return;
    valid_[index] = 0;
}

Image* StickerSheet::getSticker (unsigned index) const{
    if(index>=maxcnt_) return nullptr;
    else if(valid_[index]!=1) return nullptr;
    else return &stickers_[index];
}

Image StickerSheet::render () const{
    Image newdrawn(*Basepic_);
    for(unsigned i = 0; i<maxcnt_; i++){
        if(valid_[i]!=1) continue;
        if(stickers_[i].width()+x_[i]>newdrawn.width()) newdrawn.resize(stickers_[i].width()+x_[i],newdrawn.height());
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
    maxcnt_ = other.maxcnt_;
    stickers_ = new Image[other.max_];
    Basepic_ = new Image;
    *Basepic_ = *(other.Basepic_);
    x_ = new unsigned[other.max_];
    y_ = new unsigned[other.max_];
    valid_ = new unsigned[other.max_];
    for(unsigned i=0; i<maxcnt_; i++){
        stickers_[i] = other.stickers_[i];
        x_[i] = other.x_[i];
        y_[i] = other.y_[i];
        valid_[i] = other.valid_[i];
    }
}

void StickerSheet::_destroy(){
    delete Basepic_;
    delete[] stickers_;
    delete[] x_;
    delete[] y_;
    delete[] valid_;
}