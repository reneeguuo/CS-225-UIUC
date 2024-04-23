#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traversal = NULL;
  isEnd = false;
}

//My constructor
ImageTraversal::Iterator::Iterator(PNG image, Point startPoint, double tolerance, ImageTraversal* traversal) {
  /** @todo [Part 1] */
  this->image = image;
  this->startPoint = startPoint;
  realStart = startPoint;
  tolerance_ = tolerance;
  this->traversal = traversal;

  for (unsigned i = 0; i < image.width() * image.height(); i++) {
    isVisited.push_back(false);
  }

  isEnd = false;

  if (canBeVisited(startPoint)) {
    isVisited[(startPoint.x) + (startPoint.y * image.width())] = true;
    path.push_back(startPoint);
  } else {
    isEnd = true;
  }
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */

  Point p1 = Point(startPoint.x + 1, startPoint.y);
  Point p2 = Point(startPoint.x, startPoint.y + 1);
  Point p3 = Point(startPoint.x - 1, startPoint.y);
  Point p4 = Point(startPoint.x, startPoint.y - 1);

  if (canBeVisited(p1)) {
    traversal->add(p1);
  }
  if (canBeVisited(p2)) {
    traversal->add(p2);
  }
  if (canBeVisited(p3)) {
    traversal->add(p3);
  }
  if (canBeVisited(p4)) {
    traversal->add(p4);
  }
  if (traversal->empty()) {
    setEnd(true);
    return *this;
  }

  Point point = traversal->pop();

  while (isVisited[point.x + point.y * image.width()]) {
    if (traversal->empty()) {
      setEnd(true);
      return *this;
    }

    point = traversal->pop();
  }

  startPoint = point;
  isVisited[startPoint.x + startPoint.y * image.width()] = true;
  path.push_back(startPoint);
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return startPoint;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return (isEnd != other.isEnd);
}

bool ImageTraversal::Iterator::canBeVisited(Point point) {
  if (point.x >= image.width() || point.y >= image.height()) {
    return false;
  }

  HSLAPixel start = (image.getPixel(realStart.x, realStart.y));
  HSLAPixel desired = (image.getPixel(point.x, point.y));

  if (calculateDelta(start, desired) >= tolerance_) {
    return false;
  }

  return true;
}

void ImageTraversal::Iterator::setEnd(bool end){
  isEnd = end;
}
