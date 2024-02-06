#ifndef STICKERSHEET_H
#define STICKERSHEET_H

#include "Image.h"

class StickerSheet{
    public:
     	StickerSheet (const Image &picture, unsigned max);
        ~StickerSheet();
        StickerSheet(const StickerSheet& other);
        const StickerSheet & operator= (const StickerSheet &rhs);
        void changeMaxStickers (unsigned max);
        int addSticker (Image &sticker, unsigned x, unsigned y);
        bool translate (unsigned index, unsigned x, unsigned y);
        void removeSticker (unsigned index);
        Image *getSticker (unsigned index) const;
        Image render () const;
    private:
        //helper function
        void _copy(const StickerSheet& other);
        void _destroy();
        //private variables
        unsigned max_;
        unsigned curr_;
        Image* stickers_;
        Image* Basepic_;
        unsigned* x_;
        unsigned* y_;
};


#endif