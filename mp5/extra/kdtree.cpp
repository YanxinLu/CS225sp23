/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(curDim<0||curDim>Dim) return first<second;
    if(first[curDim]<second[curDim]) return true;
    else if(first[curDim]==second[curDim]) return first<second;
    else return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double currdist = 0;
    double potdist = 0;
    for(int i=0; i<Dim; i++){
      currdist += (currentBest[i]-target[i])*(currentBest[i]-target[i]);
      potdist += (potential[i]-target[i])*(potential[i]-target[i]);
    }
    if(potdist<currdist) return true;
    else if(potdist==currdist) return potential<target;
    else return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    size = newPoints.size();
    vector<Point<Dim>> np = newPoints;
    root = constructor_recur(np,0,0,newPoints.size()-1);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  /**
   * @todo Implement this function!
   */
  root = copy_rec(other.root);
  size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */
  if(*this!=&rhs){
    clear_(root);
    root = copy_rec(rhs.root);
    size = rhs.size;
  }
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clear_(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return neighborsearch(root,query,0);
}

