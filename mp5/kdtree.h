/**
 * @file kdtree.h
 * KDTree implementation using Points in k-dimensional space.
 *
 * @author Zesheng Wang
 * @author Wade Fagen-Ulmschneider
 * @author Cinda Heeren
 * @author Jack Toole
 * @author Sean Massung
 */

#ifndef _KDTREE_H_
#define _KDTREE_H_

#include <vector>
#include "util/coloredout.h"
#include "point.h"

using std::vector;
using std::string;
using std::ostream;
using std::cout;
using std::endl;

/**
 * KDTree class: implemented using Points in Dim dimensional space (given
 * by the template parameter).
 */
template <int Dim>
class KDTree
{
  private:
    /**
     * Internal structure for a node of KDTree.
     * Contains left, right children pointers and a K-dimensional point
     */
    struct KDTreeNode
    {
      Point<Dim> point;
      KDTreeNode *left, *right;

      KDTreeNode() : point(), left(NULL), right(NULL) {}
      KDTreeNode(const Point<Dim> &point) : point(point), left(NULL), right(NULL) {}
    };

  public:
    /**
     * Determines if Point a is smaller than Point b in a given dimension d.
     * If there is a tie, break it with Point::operator<().
     *
     * For example:
     *
     *     Point<3> a(1, 2, 3);
     *     Point<3> b(3, 2, 1);
     *     cout << smallerDimVal(a, b, 0) << endl; // should print true
     *     cout << smallerDimVal(a, b, 2) << endl; // should print false
     *     cout << smallerDimVal(a, b, 1) << endl; // based on operator<, this should be true
     *
     * @todo This function is required for MP 5.1.
     * @param first Point to compare.
     * @param second Second point to compare.
     * @param curDim Dimension these points are being compared in.
     * @return A boolean value indicating whether the first Point is smaller
     *  than the second Point in the curDim dimension.
     */
    bool smallerDimVal(const Point<Dim>& first, const Point<Dim>& second,
                       int curDim) const;

    /**
     * Determines if a Point is closer to the target Point than another
     * reference Point. Takes three points: target, currentBest, and
     * potential, and returns whether or not potential is closer to
     * target than currentBest.
     *
     * We are using Euclidean distance to compare k-dimensional
     * points: \f$\sqrt{(p_1-q_1)^2+(p_2-q_2)^2+\ldots+(p_n-q_n)^2} =
     * \sqrt{\sum_{i=1}^n (p_i-q_i)^2}\f$. Note, however, that
     * **minimizing distance is the same as minimizing squared
     * distance**, so you can **avoid invoking the square root** and
     * just compare squared distances in your code.
     *
     * For example:
     *
     *     Point<3> target(1, 3, 5);
     *     Point<3> currentBest1(1, 3, 2);
     *     Point<3> possibleBest1(2, 4, 4);
     *     Point<3> currentBest2(1, 3, 6);
     *     Point<3> possibleBest2(2, 4, 4);
     *     Point<3> currentBest3(0, 2, 4);
     *     Point<3> possibleBest3(2, 4, 6);
     *     cout << shouldReplace(target, currentBest1, possibleBest1) << endl; // true
     *     cout << shouldReplace(target, currentBest2, possibleBest2) << endl; // false
     *     cout << shouldReplace(target, currentBest3, possibleBest3) << endl;
     *      // based on operator<, this should be false
     *
     * @todo This function is required for MP 5.1.
     * @param target The Point we want to be close to.
     * @param currentBest The Point that is currently our closest Point
     *    to target.
     * @param potential Our Point that is a candidate to replace
     *    currentBest (that is, it may be closer to target than
     *    currentBest).
     * @return A boolean value indicating whether potential is closer
     *  to target than currentBest. Ties should be broken with
     *  Point::operator<().
     */
    bool shouldReplace(const Point<Dim>& target, const Point<Dim>& currentBest,
                       const Point<Dim>& potential) const;

    /**
     * Constructs a KDTree from a vector of Points, each having dimension Dim.
     *
     * You need to handle the case that the vector has no Point in it. It should
     * build the tree using recursive helper functions.
     *
     * Since we know the size of the KDTree at construction, we can
     * represent the tree as a linear structure and building the tree nodes
     * based off this structure efficiently. For testing, we **require**
     * the following:
     *
     * 1.  The median node of n nodes is calculated as the cell
     *     \f$\left\lfloor\frac{n-1}{2}\right\rfloor\f$. That is, the
     *     middle node is selected if there are an odd number, and the
     *     item before the middle if there are an even number. **If there
     *     are ties (two points have equal value along a dimension), they
     *     must be decided using Point::operator<().** Although this is
     *     arbitrary and doesn't affect the functionality of the KDTree,
     *     it is required to be able to grade your code.
     *
     * KD-trees are created recursively; at any stage of the construction,
     * the median value in the current dimension is selected and a node is
     * created based on it. Then, all the elements in the current subtree are divided
     * up into elements which are less than the median, or greater than
     * the median, and then the subtrees are created recursively.
     * The children pick the median in the next dimension, and repeat
     * until the entire set of inputs has been processed. Successive
     * levels of the tree split on increasing dimensions, modulo the
     * total number: a 3D tree will have levels split by dimension 0, 1, 2,
     * 0, 1, 2, etc.
     *
     * You will probably want to write a helper function which performs the
     * median selection and partitioning. Maybe you can use a function you
     * already wrote...
     *
     * @see Here is a reference that should help you create concise,
     * efficient code: [Partition-based General Selection
     * Algorithm](http://en.wikipedia.org/wiki/Selection_algorithm). Note
     * that "select pivotIndex between left and right" means that you
     * should choose a midpoint between the left and right indices.
     *
     * @todo This function is required for MP 5.1.
     * @param newPoints The vector of points to build your KDTree off of.
     */
    KDTree(const vector<Point<Dim>>& newPoints);


    /**
     * Copy constructor for KDTree.
     *
     * @param other The KDTree to copy.
     */
    KDTree(const KDTree& other);

    /**
     * Assignment operator for KDTree.
     *
     * @param rhs The right hand side of the assignment statement.
     * @return A reference for performing chained assignments.
     */
    KDTree const &operator=(const KDTree& rhs);

    /**
     * Destructor for KDTree.
     */
    ~KDTree();

    /**
     * Finds the closest point to the parameter point in the KDTree.
     *
     * This function takes a reference to a template parameter Point and
     * returns the Point closest to it in the tree. We are defining
     * closest here to be the minimum Euclidean distance between elements.
     * Again, **if there are ties (this time in distance), they must be
     * decided using Point::operator<().** Recall that an HSLAPixel is
     * defined by three components: hue, saturation, and luminance.
     *
     * The findNearestNeighbor() search is done in two steps: a search to
     * find the smallest hyperrectangle that contains the target element,
     * and then a back traversal to see if any other hyperrectangle could
     * contain a closer point, which may be a point with smaller distance
     * or a point with equal distance, but a "smaller" point (as defined
     * by operator< in the point class). In the first step, you must
     * recursively traverse down the tree, at each level choosing the
     * subtree which represents the region containing the search element
     * (another place to save some duplicate code?). When you reach the
     * lowest bounding hyperrectangle, then the corresponding node is
     * effectively the "current best" neighbor.
     *
     * However, it may be the case that a better match exists outside of
     * the containing hyperrectangle. At then end of first step of the
     * search, we start traversing back up the kdtree to the parent node.
     * The current best distance defines a radius which contains the
     * nearest neighbor. During the back-traversal (i.e., stepping out of
     * the recursive calls), you must first check if the distance to the
     * parent node is less than the current radius. If so, then that
     * distance now defines the radius, and we replace the "current best"
     * match. Next, it is necessary to check to see if the current
     * splitting plane's distance from search node is within the current
     * radius. If so, then the opposite subtree could contain a closer
     * node, and must also be searched recursively.
     *
     * During the back-traversal, it is important to only check the
     * subtrees that are within the current radius, or else the efficiency
     * of the kdtree is lost. If the distance from the search node to the
     * splitting plane is greater than the current radius, then there
     * cannot possibly be a better nearest neighbor in the subtree, so the
     * subtree can be skipped entirely.
     *
     * You can assume that findNearestNeighbor will only be called on a
     * valid kd-tree.
     *
     * @see Here is a reference we found quite useful in writing our kd-tree:
     *  [Andrew Moore's KD-Tree Tutorial]
     * (https://courses.engr.illinois.edu/cs225/sp2018/private/mps/5/moore-tutorial.pdf).
     *
     * @see There is [an example]
     * (https://courses.engr.illinois.edu/cs225/sp2018/mps/5/) in the MP5 instruction.
     *
     * @todo This function is required for MP 5.1.
     * @param query The point we wish to find the closest neighbor to in the
     *  tree.
     * @return The closest point to a in the KDTree.
     */
    Point<Dim> findNearestNeighbor(const Point<Dim>& query) const;

    // functions used for grading:

    /**
     * You do not need to modify this function. Its implementation is in
     *  kdtree_extras.cpp.
     * Prints the KDTree to the terminal in a pretty way.
     */
    void printTree(ostream& out = cout,
                   colored_out::enable_t enable_bold = colored_out::COUT,
                   int modWidth = -1) const;

  private:

    /** Internal representation, root and size **/
    KDTreeNode *root;
    size_t size;

    /** Helper function for grading */
    int getPrintData(KDTreeNode * subroot) const;

    /** Helper function for grading */
    void printTree(KDTreeNode * subroot, std::vector<std::string>& output,
                   int left, int top, int width, int currd) const;

    /**
     * @todo Add your helper functions here.
     */
    /* Helper function for quickselect algorithm to find the kth smallest value*/
    Point<Dim> quickselectKth(vector<Point<Dim>>& newPoints, int d, int left, int right, int k){
      //equal value
      if(left==right) return newPoints[left];
      //partition to find
      int index = partition(newPoints,d,left,right);
      if(index==k) return newPoints[index];
      else if(index>k) return quickselectKth(newPoints,d,left,index-1,k);
      else return quickselectKth(newPoints,d,index+1,right,k);
    }
    /* Helper function for partition of quickselect algorithm*/
    int partition(vector<Point<Dim>>& newPoints, int d, int left, int right){
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
    /* Helper recursive function for contructor, it calls quickselectKth to find the middle point 
     * in the specific dimension and recurse to the next dimension.
     */
    KDTreeNode* constructor_recur(vector<Point<Dim>>& newPoints, int d, int left, int right){
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
    /* Helper recursive function for findNearestNeighbor*/
    Point<Dim> neighborsearch(KDTreeNode* subroot, const Point<Dim>& point, int d) const{
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
    /*copy helper*/
    KDTreeNode* copy_rec(KDTreeNode* other){
      if(other==nullptr) return nullptr;
      KDTreeNode* new_root = new KDTreeNode();
      new_root->point = other->point;
      new_root->left = copy_rec(other->left);
      new_root->right = copy_rec(other->right);
      return new_root;
    }
    /*destroy helper*/
    void clear_(KDTreeNode* other){
      if(other==nullptr) return;
      clear_(other->left);
      clear_(other->right);
      delete other;
      other = nullptr;
    }
};

#include "kdtree.cpp"
#include "kdtree_extras.cpp"
#endif
