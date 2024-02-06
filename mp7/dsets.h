/* Your code here! */
#ifndef _DSETS_H_
#define _DSETS_H_

#include <vector>
using std::vector;

class DisjointSets{
    public:
    /*Creates n unconnected root nodes at the end of the vector.*/
    void addelements(int num);
    /*Find the representive value of the elem.*/
    int find(int elem);
    /*Union two disjiont sets by size.*/
    void setunion(int a, int b);
    private:
    /*The vector stores the elements.*/
    vector<int> _elems;
};

#endif