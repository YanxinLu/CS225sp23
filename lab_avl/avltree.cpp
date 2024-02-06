/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    if(t==nullptr) return;
    Node* newroot = t->right;
    if(newroot==nullptr) return;
    t->right = newroot->left;
    newroot->left = t;
    t = newroot;
    updateheight(t->left);
    updateheight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    if(t==nullptr) return;
    Node* newroot = t->left;
    if(newroot==nullptr) return;
    t->left = newroot->right;
    newroot->right = t;
    t = newroot;
    updateheight(t->right);
    updateheight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(subtree==nullptr) return;
    if(subtree->left==nullptr&&subtree->right==nullptr) return;
    if(subtree->left==nullptr){
        int balance = subtree->right->height+1;
        if(balance>1){
            if(subtree->right->right==nullptr&&subtree->right->left==nullptr) return;
            if(subtree->right->left==nullptr) rotateLeft(subtree);
            else if(subtree->right->right==nullptr) rotateRightLeft(subtree);
            else if(subtree->right->right->height - subtree->right->left->height>0) rotateLeft(subtree);
            else rotateRightLeft(subtree);
        }
    }
    else if(subtree->right==nullptr){
        int balance = -subtree->left->height-1;
        if(balance<-1){
            if(subtree->left->right==nullptr&&subtree->left->left==nullptr) return;
            if(subtree->left->right==nullptr) rotateRight(subtree);
            else if(subtree->left->left==nullptr) rotateLeftRight(subtree);
            else if(subtree->left->right->height - subtree->left->left->height<0) rotateRight(subtree);
            else rotateLeftRight(subtree);
        }
    }
    else{
        int balance = subtree->right->height - subtree->left->height;
        if(balance>1){
            if(subtree->right->right==nullptr&&subtree->right->left==nullptr) return;
            if(subtree->right->left==nullptr) rotateLeft(subtree);
            else if(subtree->right->right==nullptr) rotateRightLeft(subtree);
            else if(subtree->right->right->height - subtree->right->left->height>0) rotateLeft(subtree);
            else rotateRightLeft(subtree);
        }
        if(balance<-1){
            if(subtree->left->right==nullptr&&subtree->left->left==nullptr) return;
            if(subtree->left->right==nullptr) rotateRight(subtree);
            else if(subtree->left->left==nullptr) rotateLeftRight(subtree);
            else if(subtree->left->right->height - subtree->left->left->height<0) rotateRight(subtree);
            else rotateLeftRight(subtree);
        }
    }
    updateheight(subtree);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree==nullptr){
        if(root!=nullptr) return;
        Node* newnode = new Node(key,value);
        newnode->left = nullptr;
        newnode->right = nullptr;
        newnode->height = 0;
        root = newnode;
        return;
    }
    if(subtree->key==key) subtree->value = value;
    if(subtree->key>key){
        if(subtree->left==nullptr){
            Node* newnode = new Node(key,value);
            subtree->left = newnode;
            newnode->left = nullptr;
            newnode->right = nullptr;
            newnode->height = 0;
        }
        else insert(subtree->left,key,value);
    }
    if(subtree->key<key){
        if(subtree->right==nullptr){
            Node* newnode = new Node(key,value);
            subtree->right = newnode;
            newnode->left = nullptr;
            newnode->right = nullptr;
            newnode->height = 0;
        }
        else insert(subtree->right,key,value);
    }
    updateheight(subtree);
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left,key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right,key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            Node* dele = subtree;
            subtree = nullptr;
            delete dele;

        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            exchangeIOP(subtree);
            remove(subtree->left,key);
        } else {
            /* one-child remove */
            // your code here
            Node* dele = subtree;
            if(subtree->left==nullptr){
                subtree = subtree->right;
                delete dele;
            }
            else{
                subtree = subtree->left;
                delete dele;
            }
        }
        // your code here
    }
    updateheight(subtree);
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::updateheight(Node* node){
    if(node==nullptr) return;
    if(node->left==nullptr&&node->right==nullptr){
        node->height = 0;
        return;
    }
    if(node->left==nullptr){
        node->height = 1 + node->right->height;
        return;
    }
    if(node->right==nullptr){
        node->height = 1 + node->left->height;
        return;
    }
    node->height = 1 + max(node->left->height,node->right->height);
}

template <class K, class V>
void AVLTree<K, V>::exchangeIOP(Node* subtree){
    if(subtree==nullptr) return;
    if(subtree->left==nullptr) return;
    Node* curr = subtree->left;
    while(curr->right!=nullptr){
        curr = curr->right;
    }
    swap(curr,subtree);
}