/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */


    map<Point<3>, size_t> map;
    vector<Point<3>> points;

    for (size_t i = 0; i < theTiles.size(); i++) {

      LUVAPixel pixel = theTiles[i].getAverageColor();
      Point<3> point = convertToXYZ(pixel);
      
      points.push_back(point);
      map.insert(std::pair<Point<3>, size_t>(point,i));

    }

    MosaicCanvas* Canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    KDTree<3>* kd_tree = new KDTree<3>(points);

    for (int i = 0; i < theSource.getRows(); i++) {
      for (int j = 0; j < theSource.getColumns(); j++) {

        Point<3> point = convertToXYZ(theSource.getRegionColor(i, j));
        Point<3> nearest = kd_tree->findNearestNeighbor(point);

        size_t best = map[nearest];
        Canvas->setTile(i, j, &theTiles[best]);

      }
    }

    delete kd_tree; //Added delete for memory check, remove if segfault
    return Canvas;
}
