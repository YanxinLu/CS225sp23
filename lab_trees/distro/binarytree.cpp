/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    if(root==NULL) return;
    r_mirror(root);
}

/*helper function for mirror*/
template <typename T>
void BinaryTree<T>::r_mirror(Node* node){
    Node* tem;
    tem = node->right;
    node->right = node->left;
    node->left = tem;
    if(node->left!=NULL) r_mirror(node->left);
    if(node->right!=NULL) r_mirror(node->right);
}

/**
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{
    // your code here
    if(root==NULL) return true;
    return r_ordered(root,NULL,NULL);
}

/*helper function for isOrdered*/
template <typename T>
bool BinaryTree<T>::r_ordered(Node* node, const T* max, const T* min) const{
    if(node->left!=NULL){
        if(node->left->elem > node->elem) return false;
        if(min&&node->left->elem<(*min)) return false;
        if(!r_ordered(node->left, &(node->elem), min)) return false;
    }
    if(node->right!=NULL){
        if(node->right->elem < node->elem) return false;
        if(max&&node->right->elem>(*max)) return false;
        if(!r_ordered(node->right, max, &(node->elem))) return false;
    }
    return true;
}

/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths) const
{
    // your code here
    if(root==NULL) return;
    paths.push_back(vector<T>());
    r_paths(paths,root,0);
}

/*helper function for printPaths*/
template <typename T>
void BinaryTree<T>::r_paths(vector<vector<T> > &paths, Node* node, int curr) const{
    vector<T> tem;
    paths[curr].push_back(node->elem);
    if(node->left==NULL&&node->right==NULL) return;
    if(node->left==NULL) r_paths(paths,node->right,curr);
    else if(node->right==NULL) r_paths(paths,node->left,curr);
    else{
        tem = paths[curr];
        r_paths(paths,node->left,curr);
        paths.push_back(tem);
        r_paths(paths,node->right,paths.size()-1);
    }
}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    if(root==NULL) return -1;
    return r_sumdis(root,0);
}

/*helper function for sumDistances*/
template <typename T>
int BinaryTree<T>::r_sumdis(Node* node, int subpath) const{
    int dis = 0;
    if(node->left!=NULL) dis = dis + subpath+1 + r_sumdis(node->left, subpath+1);
    if(node->right!=NULL) dis = dis + subpath+1 + r_sumdis(node->right, subpath+1);
    return dis;
}