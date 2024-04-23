#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */

  double hue = 0 + (std::rand() % (359 + 1));
  if (hue > 360) {
    while (hue > 360) {
      hue -= 360;
    }
  }

  HSLAPixel pixel(hue, 0.8, 0.5);
  return pixel;
}
