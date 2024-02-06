/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

/**
 * Determines if Point a is smaller than Point b in a given dimension d.
 * If there is a tie, break it with Point::operator<().
 */
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

/**
 * Determines if a Point is closer to the target Point than another
 * reference Point. Takes three points: target, currentBest, and
 * potential, and returns whether or not potential is closer to
 * target than currentBest.
 */
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
    //calculate the distance by adding the square of all dimensions
    for(int i=0; i<Dim; i++){
      currdist += (currentBest[i]-target[i])*(currentBest[i]-target[i]);
      potdist += (potential[i]-target[i])*(potential[i]-target[i]);
    }
    //check which point is closer
    if(potdist<currdist) return true;
    else if(potdist==currdist) return potential<target;
    else return false;
}

/**
 * Constructs a KDTree from a vector of Points, each having dimension Dim.
 */
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

/**
 * Copy constructor for KDTree.
 */
template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  /**
   * @todo Implement this function!
   */
  root = copy_rec(other.root);
  size = other.size;
}

/**
 * Assignment operator for KDTree.
 */
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

/**
 * Destructor for KDTree.
 */
template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clear_(root);
}

/**
 * Finds the closest point to the parameter point in the KDTree.
 */
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return neighborsearch(root,query,0);
}
 template <int Dim>
Point<Dim> KDTree<Dim>::quickselectKth(vector<Point<Dim>>& newPoints, int d, int left, int right, int k){
      //equal value
      if(left==right) return newPoints[left];
      //partition to find
      int index = partition(newPoints,d,left,right);
      if(index==k) return newPoints[index];
      else if(index>k) return quickselectKth(newPoints,d,left,index-1,k);
      else return quickselectKth(newPoints,d,index+1,right,k);
    }
    
template <int Dim>
    int KDTree<Dim>::partition(vector<Point<Dim>>& newPoints, int d, int left, int right){
      int i = left;
      //set the right point to be the pivot point
      Point<Dim> pivot = newPoints[right];
      for(int j=left; j<right; j++){
        //if j is smaller than the pivot, swap i and j
        if(smallerDimVal(newPoints[j],pivot,d)){
            Point<Dim> tem = newPoints[j];
            newPoints[j] = newPoints[i];
            newPoints[i] = tem;
            i++;
        }
      }
      //swap i and the right
      newPoints[right] = newPoints[i];
      newPoints[i] = pivot;
      return i;
    }

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::constructor_recur(vector<Point<Dim>>& newPoints, int d, int left, int right){
      if(left>right) return nullptr;
      Point<Dim> selectk = quickselectKth(newPoints,d,left,right,(left+right)/2);
      //alloc a new node
      KDTreeNode* subroot = new KDTreeNode();
      //set the point and its children
      subroot->point = selectk;
      subroot->left = constructor_recur(newPoints,(d+1)%Dim,left,(left+right)/2-1);
      subroot->right = constructor_recur(newPoints,(d+1)%Dim,(left+right)/2+1,right);
      return subroot;
    }

template <int Dim>
  Point<Dim> KDTree<Dim>::neighborsearch(KDTreeNode* subroot, const Point<Dim>& point, int d) const{
      //check available
      if(subroot==nullptr){
        if(root==nullptr) return Point<Dim>();
        else return root->point;
      }
      //if leaf or exactly the same point, the current point is the cloeset
      if(subroot->left==nullptr&&subroot->right==nullptr) return subroot->point;
      if(subroot->point==point) return subroot->point;
      //recurse the closest point of its children
      Point<Dim> closest;
      int indicator = 0;
      if(!smallerDimVal(point,subroot->point,d)){
        closest = neighborsearch(subroot->right,point,(d+1)%Dim);
      }
      else{
        closest = neighborsearch(subroot->left,point,(d+1)%Dim);
        indicator = 1;
      }
      //the child's closest vs. the current point
      if(shouldReplace(point,closest,subroot->point)) closest = subroot->point;
      //radius vs. distance to figure out whether the another child is needed
      double radius_sq = (subroot->point[d]-point[d])*(subroot->point[d]-point[d]);
      double dist_sq = 0;
      for(int i = 0; i<Dim; i++){
        dist_sq+=(closest[i]-point[i])*(closest[i]-point[i]);
      }
      if(dist_sq>=radius_sq){
        Point<Dim> tem;
        if(indicator) tem = neighborsearch(subroot->right, point,(d+1)%Dim);
        else tem = neighborsearch(subroot->left,point,(d+1)%Dim);
        if(shouldReplace(point,closest,tem)) closest = tem;
      }
      return closest;
    }

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy_rec(KDTreeNode* other){
      if(other==nullptr) return nullptr;
      KDTreeNode* new_root = new KDTreeNode();
      new_root->point = other->point;
      new_root->left = copy_rec(other->left);
      new_root->right = copy_rec(other->right);
      return new_root;
    }

template <int Dim>
    void KDTree<Dim>::clear_(KDTreeNode* other){
      if(other==nullptr) return;
      clear_(other->left);
      clear_(other->right);
      delete other;
      other = nullptr;
    }

