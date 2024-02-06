/* Your code here! */
#include "dsets.h"


/*Creates n unconnected root nodes at the end of the vector.*/
void DisjointSets::addelements(int num){
    if(num<=0) return;
    _elems.insert(_elems.end(), num, -1);
}

/*Find the representive value of the elem.*/
int DisjointSets::find(int elem){
    //if(elem<0||elem>=_elems.size()) return -1;
    if(_elems[elem]<0) return elem;
    else{
        _elems[elem] = find(_elems[elem]);
        return _elems[elem];
    }
}

/*Union two disjiont sets by size.*/
void DisjointSets::setunion(int a, int b){
    int roota = find(a);
    int rootb = find(b);
    int sizea = _elems[roota];
    int sizeb = _elems[rootb];
    if(sizea <= sizeb){
        _elems[rootb] = roota;
        _elems[roota] = sizea + sizeb;
    }
    else{
        _elems[roota] = rootb;
        _elems[rootb] = sizea + sizeb;
    }
}