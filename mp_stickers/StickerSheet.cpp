#include "StickerSheet.h"
#include "Image.h"
#include "cs225/PNG.h"

StickerSheet::StickerSheet(const Image & picture, unsigned max) {

  ImageArray = new Image*[max];
  maximum = max;
  img = new Image(picture);
  xarray = new unsigned[max];
  yarray = new unsigned[max];

  for (unsigned int i = 0; i < max; i++) {
    ImageArray[i] = NULL;
    xarray[i] = 0;
    yarray[i] = 0;
  }
}

StickerSheet::~StickerSheet() {
  destroy();
}

StickerSheet::StickerSheet(const StickerSheet & other) {
  copy(other);
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other){
  if (this != &other) {
    destroy();
    copy(other);
  }
  return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {

  Image** temp = new Image*[max];
  unsigned* xtemp = new unsigned[max];
  unsigned* ytemp = new unsigned[max];

  if (maximum < max) {
    for (unsigned int i = 0; i < maximum; i++) {
      temp[i] = ImageArray[i];
      xtemp[i] = xarray[i];
      ytemp[i] = yarray[i];
    }

    for (unsigned int i = maximum; i < max; i++) {
      temp[i] = NULL;
      xtemp[i] = 0;
      ytemp[i] = 0;
    }
  }

  else {
    for (unsigned int i = 0; i < max; i++) {
      temp[i] = ImageArray[i];
      xtemp[i] = xarray[i];
      ytemp[i] = yarray[i];
    }

    for (unsigned int i = max; i < maximum; i++) {
      delete ImageArray[i];
      ImageArray[i] = NULL;
      xtemp[i] = 0;
      ytemp[i] = 0;
    }
  }

  delete [] ImageArray;
  ImageArray = temp;
  xarray = xtemp;
  yarray = ytemp;
  maximum = max;
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
  for (unsigned int i = 0; i < maximum; i++) {
    if (ImageArray[i] == NULL) {
      ImageArray[i] = new Image(sticker);
      xarray[i] = x;
      yarray[i] = y;
      return i;
    }
  }
  return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
  if (index > maximum) {
    return false;
  }
  if (ImageArray[index] == NULL) {
    return false;
  }
  xarray[index] = x;
  yarray[index] = y;
  return true;
}

void StickerSheet::removeSticker(unsigned index) {
  if (ImageArray[index] == NULL) {
    return;
  }

  if (index > (maximum - 1)) {
    return;
  }

  delete ImageArray[index];
  ImageArray[index] = NULL;
  xarray[index] = 0;
  yarray[index] = 0;
}

Image * StickerSheet::getSticker(unsigned index) {

  if (index < maximum) {
    return ImageArray[index];
  }

  return NULL;
}

Image StickerSheet::render() {
  unsigned int width = img->width();
  unsigned int imageHeight = img->height();

  for (unsigned int i = 0; i < maximum; i++){
    if (ImageArray[i] != NULL) {
      unsigned int w = xarray[i] + ImageArray[i]->width();
      unsigned int h = yarray[i] + ImageArray[i]->height();

      if (w > width) {
        width = w;
      }
      if (h > imageHeight) {
        imageHeight = h;
      }
    }
  }

  Image *output = new Image(*img);
  output->resize(width, imageHeight);

  for (unsigned int i = 0; i < maximum; i++) {
    if (ImageArray[i]!=NULL) {
      for (unsigned int x = xarray[i]; x < xarray[i] + ImageArray[i]->width(); x++){
        for (unsigned int y = yarray[i]; y < yarray[i] + ImageArray[i]->height(); y++){
          cs225::HSLAPixel & pixel1 = output->getPixel(x,y);
          cs225::HSLAPixel & pixel2 = ImageArray[i]->getPixel(x - xarray[i],y - yarray[i]);
          if (pixel2.a != 0){
            pixel1 = pixel2;
          }
        }
      }
    }
  }

  return *output;
}

void StickerSheet::destroy() {
  if (ImageArray != NULL) {
    for (unsigned int i = 0; i < maximum; i++) {
      delete ImageArray[i];
      ImageArray[i] = NULL;
    }
  }

    delete img;
    delete[] ImageArray;
    delete[] xarray;
    delete[] yarray;

    ImageArray = NULL;
    xarray = NULL;
    yarray = NULL;
}

void StickerSheet::copy(const StickerSheet &other) {
  img = new Image(*other.img);
  maximum = other.maximum;

  ImageArray = new Image*[maximum];
  xarray = new unsigned[maximum];
  yarray = new unsigned[maximum];

  for (unsigned int i = 0; i < maximum; i++) {
    if (other.ImageArray[i] != NULL) {
      ImageArray[i] = new Image(*other.ImageArray[i]);
      xarray[i] = other.xarray[i];
      yarray[i] = other.yarray[i];
    }

    else {
      ImageArray[i] = NULL;
    }
  }
}
