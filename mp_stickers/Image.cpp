#include <iostream>
#include "Image.h"


void Image::lighten() {
  //Image image = (*this);
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      pixel.l += 0.1;
      if (pixel.l > 1) {
        pixel.l = 1;
      }
    }
  }
}

void Image::lighten(double amount) {
  //Image image = (*this);
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      pixel.l += amount;
      if (pixel.l > 1) {
        pixel.l = 1;
      }
    }
  }
}

void Image::darken() {
  //Image image = (*this);
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      pixel.l -= 0.1;
      if (pixel.l < 0) {
        pixel.l = 0;
      }
    }
  }
}

void Image::darken(double amount) {
  //Image image = (*this);
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      pixel.l -= amount;
      if (pixel.l < 0) {
        pixel.l = 0;
      }
    }
  }
}

void Image::saturate() {
  //Image image = (*this);
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      pixel.s += 0.1;
      if (pixel.s > 1) {
        pixel.s = 1;
      }
    }
  }
}

void Image::saturate(double amount) {
  //Image image = (*this);
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      pixel.s += amount;
      if (pixel.s > 1) {
        pixel.s = 1;
      }
    }
  }
}

void Image::desaturate() {
  //Image image = (*this);
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      pixel.s -= 0.1;
      if (pixel.s < 0) {
        pixel.s = 0;
      }
    }
  }
}

void Image::desaturate(double amount) {
  //Image image = (*this);
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      pixel.s -= amount;
      if (pixel.s < 0) {
        pixel.s = 0;
      }
    }
  }
}

void Image::grayscale() {
  //Image image = (*this);
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      pixel.s = 0;
    }
  }
}

void Image::rotateColor(double degrees) {
  for (unsigned x = 0; x < this->width(); x++) {
      for (unsigned y = 0; y < this->height(); y++) {
        cs225::HSLAPixel & pixel = this->getPixel(x, y);
        pixel.h += degrees;
        if (pixel.h >= 360) {
          pixel.h -= 360;
        }
        if (pixel.h < 0) {
          pixel.h += 360;
        }
    }
  }
}

void Image::Illinify() {
  // Code taken from lab_intro (My code)
  //Image image = (*this);
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel & pixel = this->getPixel(x, y);
      if (pixel.h >= 113.5 && pixel.h < 293.5) {
        pixel.h = 216.0;
      } else {
        pixel.h = 11.0;
      }
    }
  }
}

void Image::scale(double factor) {
  unsigned int newWidth = factor * this->width();
  unsigned int newHeight = factor * this->height();
  unsigned int width = this->width();
  unsigned int height = this->height();
  Image *temp = new Image();
  *temp = *this;
  this->resize(newWidth, newHeight);

  if (factor > 0) {
    for (unsigned int x = 0; x < newWidth; x++) {
      for (unsigned int y = 0; y < newHeight; y++) {
        cs225::HSLAPixel & pixel1 = this->getPixel(x, y);
        cs225::HSLAPixel & pixel2 = temp->getPixel((unsigned int)((width*x)/newWidth), (unsigned int)((height*y)/newHeight));
        pixel1 = pixel2;
      }
    }
  }
  delete temp;
}

void Image::scale(unsigned w, unsigned h) {

  if (w > 0  && h > 0) {

    double width = this->width();
    double height = this->height();
    double factor_w = w / width;
    double factor_h = h / height;
    double factor = 1.0;

    if (factor_w >= factor_h) {
      factor = factor_h;
    }
    if (factor_w < factor_h) {
      factor = factor_w;
    }

    this->scale(factor);
  }

  // double factor_w = w / this->width();
	// double factor_h = h / this->height();
  // unsigned int width = this->width();
  // unsigned int height = this->height();
  // unsigned int newWidth = factor_w * this->width();
  // unsigned int newHeight = factor_h * this->height();
  //
	// Image *temp = new Image();
  // *temp = *this;
  //
  // double factor;
  //
  // if (newWidth > w) {
  //   factor_w = factor_h;
  // }
  //
  // if (newHeight > h) {
  //   factor_h = factor_w;
  // }
  //
  // unsigned int newWidth = factor_w * this->width();
  // unsigned int newHeight = factor_h * this->height();
  //
  // for (unsigned int x = 0; x < newWidth; x++) {
  //   for (unsigned int y = 0; y < newHeight; y++) {
  //     cs225::HSLAPixel & pixel1 = this->getPixel(x, y);
  //     cs225::HSLAPixel & pixel2 = temp->getPixel((unsigned int)((width*x)/newWidth), (unsigned int)((height*y)/newHeight));
  //     pixel1 = pixel2;
  //   }
  // }
  //
  // delete temp;

}

Image::Image(const Image & pic)
:PNG::PNG(pic) {
}

Image::Image()
:PNG::PNG() {
}
