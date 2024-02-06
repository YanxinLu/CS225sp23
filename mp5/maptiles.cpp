/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

Point<3> convertToLAB(HSLAPixel pixel) {
    Point<3> result(pixel.h/360, pixel.s, pixel.l);
    return result;
}

/**
 * Map the image tiles into a mosaic canvas which closely
 * matches the input image.
 */
MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    if(theTiles.empty()) return nullptr;
    //alloc return MosaicCanvas
    MosaicCanvas* ret = new MosaicCanvas(theSource.getRows(),theSource.getColumns());
    //set the map and the points vector
    vector<Point<3>> source_points;
    map<Point<3>,int> tile_map;
    for(int i=0; i<(int)theTiles.size(); i++){
        TileImage tile = theTiles[i];
        HSLAPixel tile_pixel = tile.getAverageColor();
        Point<3> tile_point(tile_pixel.h/360,tile_pixel.s,tile_pixel.l);
        tile_map.insert(pair<Point<3>,int>(tile_point,i));
        source_points.push_back(tile_point);
    }
    //build kdtreeb based on the points vector
    KDTree<3> tile_kdtree(source_points);
    for(int x=0; x<theSource.getRows(); x++){
        for(int y=0; y<theSource.getColumns(); y++){
            //get source_pixel and the find the tile
            HSLAPixel source_pixel = theSource.getRegionColor(x,y);
            Point<3> source_point(source_pixel.h/360,source_pixel.s,source_pixel.l);
            Point<3> find_point = tile_kdtree.findNearestNeighbor(source_point);
            //find the index in map
            int index = tile_map.find(find_point)->second;
            ret->setTile(x,y,&theTiles[index]);
        }
    }
    return ret;
}

TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> tile_avg_map,
                                  vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToLAB(avg);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);

    // Check to ensure the point exists in the map
    map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];

}
