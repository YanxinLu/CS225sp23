/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
  if(empty()) return;
  ListNode* curr_ = head_;
  ListNode* node_ = NULL;
  while(curr_!=NULL){
    node_ = curr_;
    curr_ = curr_->next;
    delete node_;
  }
  length_ = 0;
  head_ = NULL;
  tail_ = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata) {
  /// @todo Graded in MP3.1
  ListNode* newnode = new ListNode(ndata);
  newnode->prev = NULL;
  newnode->next = head_;
  if(tail_==NULL) tail_ = newnode;
  if(head_!=NULL) head_->prev = newnode;
  head_ = newnode;
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata) {
  /// @todo Graded in MP3.1
  ListNode* newnode = new ListNode(ndata);
  newnode->prev = tail_;
  newnode->next = NULL;
  if(head_==NULL) head_ = newnode;
  if(tail_!=NULL) tail_->next = newnode;
  tail_ = newnode;
  length_++;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint) {
    /// @todo Graded in MP3.1
    //empty sequence
    if(startPoint==NULL||endPoint==NULL) return;
    ListNode *stprev, *ednext, *temst, *temed, *curr, *nextnode;
    //outside the sequence
    stprev = startPoint->prev;
    ednext = endPoint->next;
    temst = startPoint;
    temed = endPoint;
    //not head or tail
    if(stprev!=NULL) startPoint->prev->next = endPoint;
    if(ednext!=NULL) endPoint->next->prev = startPoint;
    //head_ or tail_
    if(stprev==NULL) head_ = temed;
    if(ednext==NULL) tail_ = temst;
    temed->next = stprev;
    temst->prev = ednext;
    //inside the sequence
    curr = temst;
    while(curr!=temed){
      nextnode = curr->next;
      curr->next = curr->prev;
      curr->prev = nextnode;
      curr = nextnode;
    }
    nextnode = temed->next;
    temed->next = temed->prev;
    temed->prev = nextnode;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  if(n>=length_){
    reverse();
    return;
  }
  if(n<=1) return;
  if(empty()||length_==1) return;
  ListNode *first, *second, *nextnode;
  first = head_;
  while(true){
    second = first;
    int i;
    if(first==tail_) return;
    for(i=1; i<n; i++){
      second = second->next;
      if(second==tail_) break;
    }
    if(i==n) nextnode = second->next;
    reverse(first,second);
    if(i!=n) break;
    first = nextnode;
  }
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  if(empty()) return;
  if(head_==tail_) return;
  ListNode *skip_, *move_;
  skip_ = head_;
  while(skip_->next!=tail_&&skip_->next!=NULL){
    move_ = skip_->next;
    //remove move_
    skip_->next = move_->next;
    move_->next->prev = skip_;
    //nextskip
    skip_ = skip_->next;
    //insertback
    move_->prev = tail_;
    move_->next = NULL;
    tail_->next = move_;
    tail_ = move_;
  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_->next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
    /// @todo Graded in MP3.2
    if(start==NULL) return NULL;
    if(splitPoint>=length_) return NULL;
    if(splitPoint==0){
      if(start!=head_){
        start->prev->next = NULL;
        start->prev = NULL;
      }
      return start;
    }
    for(int i=0; i<splitPoint; i++){
      start = start->next;
      if(start==tail_&&i<splitPoint-1) return NULL;
    }
    start->prev->next = NULL;
    start->prev = NULL;
    return start;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
  /// @todo Graded in MP3.2
  if(second==NULL) return first;
  if(first==NULL) return second;
  if(first==second){
    ListNode* cleannode;
    while(second!=NULL){
      cleannode = second;
      second = second->next;
      delete cleannode;
    }
    return NULL;
  }
  ListNode *node, *insert;
  node = first;
  while(second!=NULL){
    if(node->data < second->data){
      if(node->next!=NULL) node = node->next;
      else{
        node->next = second;
        second->prev = node;
        return first;
      }
    }
    else{
      insert = second;
      second = second->next;
      if(node->prev==NULL){
        first = insert;
      }
      else{
        node->prev->next = insert;
      }
      insert->prev = node->prev;
      node->prev = insert;
      insert->next = node;
      node = insert;
    }
  }
  return first;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength) {
    /// @todo Graded in MP3.2
    if(chainLength<=1) return start;
    ListNode* second;
    second = split(start,chainLength/2);
    start = mergesort(start,chainLength/2);
    second = mergesort(second,chainLength - chainLength/2);
    return merge(start,second);
}
