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
  traversal_ = nullptr;
  png_ = nullptr;
  start_ = Point(0,0);
  curr_ = Point(0,0);
  tol_ = 0;
}

/**
 * iterator constructor.
 */
ImageTraversal::Iterator::Iterator(ImageTraversal* traversal, PNG* png, double tol) {
  /** @todo [Part 1] */
  traversal_ = traversal;
  png_ = png;
  tol_ = tol;
  visited.resize(png->width());
  for(unsigned int i=0; i<png->width(); i++){
    visited[i].resize(png->height());
  }
  if(traversal_!=nullptr){
    start_ = traversal_->peek();
    curr_ = traversal_->pop();
    visited[curr_.x][curr_.y] = 1;
    addneighbor(curr_);
  }
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if(traversal_==nullptr||traversal_->empty()){
    traversal_= nullptr;
    png_ = nullptr;
    curr_ = Point(0,0);
    start_ = Point(0,0);
    tol_ = 0;
  }
  else{
    curr_ = traversal_->pop();
    while(visited[curr_.x][curr_.y] == 1&&!traversal_->empty()) curr_ = traversal_->pop();
    if(traversal_->empty()){
      traversal_= nullptr;
      png_ = nullptr;
      curr_ = Point(0,0);
      start_ = Point(0,0);
      tol_ = 0;
      return *this;
    }
    visited[curr_.x][curr_.y] = 1;
    addneighbor(curr_);
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr_;
}

/**
 * Iterator inequality operator.
 * 
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if(this->traversal_==other.traversal_&&this->png_==other.png_&&
    this->tol_==other.tol_&&this->start_==other.start_&&this->curr_==other.curr_) return false;
  return true;
}

/*helper function*/
void ImageTraversal::Iterator::addneighbor(Point point){
  if(point.x+1<png_->width()&&tol_>calculateDelta(*png_->getPixel(start_.x,start_.y),*png_->getPixel(point.x+1,point.y))){
    traversal_->add(Point(point.x+1,point.y));
  }
  if(point.y+1<png_->height()&&tol_>calculateDelta(*png_->getPixel(start_.x,start_.y),*png_->getPixel(point.x,point.y+1))){
    traversal_->add(Point(point.x,point.y+1));
  }
  if(point.x>=1&&tol_>calculateDelta(*png_->getPixel(start_.x,start_.y),*png_->getPixel(point.x-1,point.y))){
    traversal_->add(Point(point.x-1,point.y));
  }
  if(point.y>=1&&tol_>calculateDelta(*png_->getPixel(start_.x,start_.y),*png_->getPixel(point.x,point.y-1))){
    traversal_->add(Point(point.x,point.y-1));
  }
}