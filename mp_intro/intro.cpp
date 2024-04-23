#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>

using cs225::PNG;
using cs225::HSLAPixel;


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  PNG image;
  image.readFromFile(inputFile);
  int height_ = image.height();
  int width_ = image.width();

  for (int x = 0; x < (width_)/2; x++) {
    for (int y = 0; y < height_; y++) {
      HSLAPixel & pixel1 = image.getPixel(x, y);
      HSLAPixel & pixel2 = image.getPixel(width_ - x - 1, height_ - y - 1);
      HSLAPixel temp = pixel1;
      pixel1 = pixel2;
      pixel2 = temp;
    }
  }

  if (width_ % 2 != 0) {
    for (int i = 0; i < height_/2; i++) {
      HSLAPixel & pixel1 = image.getPixel(width_/2, i);
      HSLAPixel & pixel2 = image.getPixel(width_/2, height_ - i - 1);
      HSLAPixel temp = pixel1;
      pixel1 = pixel2;
      pixel2 = temp;
    }
  }
  image.writeToFile(outputFile);
}


cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3

  for(unsigned int y = 0; y < png.height()/7; y++) {
    unsigned int i = 0;
    unsigned int j = y;
    while(j < png.height()) {
      cs225::HSLAPixel & pixel = png.getPixel(i, j);
      pixel.h = 0;
      pixel.s = 0.87;
      pixel.l = 0.31;
      pixel.a = 1;
      i++;
      j++;
    }
  }

  for(unsigned int x = 0; x < png.width()/7; x++) {
    unsigned int i = x;
    unsigned int j = 0;
    while(i < png.width()) {
      cs225::HSLAPixel & pixel = png.getPixel(i, j);
      pixel.h = 0;
      pixel.s = 0.87;
      pixel.l = 0.31;
      pixel.a = 1;
      i++;
      j++;
    }
  }

  for(unsigned int y = png.height()/7; y < png.height()/4; y++) {
    unsigned int i = 0;
    unsigned int j = y;
    while(j < png.height()) {
      cs225::HSLAPixel & pixel = png.getPixel(i, j);
      pixel.h = 0;
      pixel.s = 1;
      pixel.l = 0;
      pixel.a = 1;
      i++;
      j++;
    }
  }

  for(unsigned int x = png.width()/7; x < png.width()/4 ; x++) {
    unsigned int i = x;
    unsigned int j = 0;
    while(i < png.width()) {
      cs225::HSLAPixel & pixel = png.getPixel(i, j);
      pixel.h = 0;
      pixel.s = 1;
      pixel.l = 0;
      pixel.a = 1;
      i++;
      j++;
    }
  }

    for(unsigned int y = png.height()/4; y < png.height()/3; y++) {
      unsigned int i = 0;
      unsigned int j = y;
      while(j < png.height()) {
        cs225::HSLAPixel & pixel = png.getPixel(i, j);
        pixel.h = 360;
        pixel.s = 0;
        pixel.l = 1;
        pixel.a = 1;
        i++;
        j++;
      }
    }

  for(unsigned int x = png.width()/4; x < png.width()/3; x++) {
    unsigned int i = x;
    unsigned int j = 0;
    while(i < png.width()) {
      cs225::HSLAPixel & pixel = png.getPixel(i, j);
      pixel.h = 360;
      pixel.s = 0;
      pixel.l = 1;
      pixel.a = 1;
      i++;
      j++;
    }
  }

  for(unsigned int y = png.height()/3; y < png.height()/2.6; y++) {
    unsigned int i = 0;
    unsigned int j = y;
    while(j < png.height()) {
      cs225::HSLAPixel & pixel = png.getPixel(i, j);
      pixel.h = 0;
      pixel.s = 1;
      pixel.l = 0;
      pixel.a = 1;
      i++;
      j++;
    }
  }

  for(unsigned int x = png.width()/3; x < png.width()/2.6; x++) {
    unsigned int i = x;
    unsigned int j = 0;
    while(i < png.width()) {
      cs225::HSLAPixel & pixel = png.getPixel(i, j);
      pixel.h = 0;
      pixel.s = 1;
      pixel.l = 0;
      pixel.a = 1;
      i++;
      j++;
    }
  }

  for(unsigned int y = png.height()/2.6; y < png.height()/2; y++) {
    unsigned int i = 0;
    unsigned int j = y;
    while(j < png.height()) {
      cs225::HSLAPixel & pixel = png.getPixel(i, j);
      pixel.h = 0;
      pixel.s = 0.87;
      pixel.l = 0.31;
      pixel.a = 1;
      i++;
      j++;
    }
  }

  for(unsigned int x = png.width()/2.6; x < png.width()/2; x++) {
    unsigned int i = x;
    unsigned int j = 0;
    while(i < png.width()) {
      cs225::HSLAPixel & pixel = png.getPixel(i, j);
      pixel.h = 0;
      pixel.s = 0.87;
      pixel.l = 0.31;
      pixel.a = 1;
      i++;
      j++;
    }
  }

  for(unsigned int y = png.height()/2; y < png.height()/1.82; y++) {
    unsigned int i = 0;
    unsigned int j = y;
    while(j < png.height()) {
      cs225::HSLAPixel & pixel = png.getPixel(i, j);
      pixel.h = 0;
      pixel.s = 1;
      pixel.l = 0;
      pixel.a = 1;
      i++;
      j++;
    }
  }

  for(unsigned int x = png.width()/2; x < png.width()/1.82; x++) {
    unsigned int i = x;
    unsigned int j = 0;
    while(i < png.width()) {
      cs225::HSLAPixel & pixel = png.getPixel(i, j);
      pixel.h = 0;
      pixel.s = 1;
      pixel.l = 0;
      pixel.a = 1;
      i++;
      j++;
    }
  }

  for(unsigned int y = png.height()/4; y < png.height()/3; y++) {
    unsigned int i = 0;
    unsigned int j = y;
    while(j < png.height()) {
      cs225::HSLAPixel & pixel = png.getPixel(i, j);
      pixel.h = 360;
      pixel.s = 0;
      pixel.l = 1;
      pixel.a = 1;
      i++;
      j++;
    }
  }

  for(unsigned int x = png.width()/4; x < png.width()/3; x++) {
    unsigned int i = x;
    unsigned int j = 0;
    while(i < png.width()) {
      cs225::HSLAPixel & pixel = png.getPixel(i, j);
      pixel.h = 360;
      pixel.s = 0;
      pixel.l = 1;
      pixel.a = 1;
      i++;
      j++;
    }
  }

  for(unsigned int y = png.height()/1.5; y < png.height()/1.2; y++) {
    unsigned int i = 0;
    unsigned int j = y;
    while(j < png.height()) {
      cs225::HSLAPixel & pixel = png.getPixel(i, j);
      pixel.h = 0;
      pixel.s = 1;
      pixel.l = 0;
      pixel.a = 1;
      i++;
      j++;
    }
  }

  for(unsigned int x = png.width()/1.5; x < png.width()/1.2; x++) {
    unsigned int i = x;
    unsigned int j = 0;
    while(i < png.width()) {
      cs225::HSLAPixel & pixel = png.getPixel(i, j);
      pixel.h = 0;
      pixel.s = 1;
      pixel.l = 0;
      pixel.a = 1;
      i++;
      j++;
    }
  }

  for(unsigned int y = png.height()/1.42; y < png.height()/1.25; y++) {
    unsigned int i = 0;
    unsigned int j = y;
    while(j < png.height()) {
      cs225::HSLAPixel & pixel = png.getPixel(i, j);
      pixel.h = 0;
      pixel.s = 0.87;
      pixel.l = 0.31;
      pixel.a = 1;
      i++;
      j++;
    }
  }

  for(unsigned int x = png.width()/1.42; x < png.width()/1.25; x++) {
    unsigned int i = x;
    unsigned int j = 0;
    while(i < png.width()) {
      cs225::HSLAPixel & pixel = png.getPixel(i, j);
      pixel.h = 0;
      pixel.s = 0.87;
      pixel.l = 0.31;
      pixel.a = 1;
      i++;
      j++;
    }
  }
  return png;
}
