/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode * current;
  ListNode * temp;
  current = head_;

  while(current != NULL){
    temp = current;
    current = current->next;
    delete temp;
  }

  head_ = NULL;
  tail_ = NULL;
  temp = NULL;
  length_= 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  //@todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);

  if (length_ == 0) {
    head_ = newNode;
    tail_ = newNode;
    newNode->next = NULL;
    newNode->prev = NULL;
  } else {
    newNode->next = head_;
    head_->prev = newNode;
    head_ = newNode;
    newNode->prev = NULL;
  }

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);

  if (length_ == 0) {
    head_ = newNode;
    tail_ = newNode;
    length_++;
  } else {
    tail_->next = newNode;
    newNode->prev = tail_;
    //tail_ = newNode;
    tail_ = tail_->next;
    length_++;
  }
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  //@todo Graded in MP3.1

  if (splitPoint >= length_) {
    return tail_->next;
  }

  if (splitPoint <= 0) {
    return head_;
  }

  ListNode * curr = start;

	for (int i = 0; i < splitPoint && curr != NULL; i++) {
		curr = curr->next;
		if (curr == NULL) {
			return start;
		}
	}


  if (curr != NULL) {
    tail_ = curr->prev;
    curr->prev->next = NULL;
    curr->prev = NULL;
  }
	return curr;

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
template <typename T>
void List<T>::waterfall() {
  // @todo Graded in MP3.1

  ListNode * current = head_;
  ListNode * temp;
  int index = 0;

  while (current != tail_) {
    temp = current->next;

    if (index % 2 == 1) {
      current->prev->next = current->next;
      current->next->prev = current->prev;

      tail_->next = current;
      current->prev = tail_;
      current->next = NULL;
      tail_ = current;
    }

    index++;
    current = temp;
  }

}

/**
 * Reverses the current List.
 */
template <typename T>
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
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if (startPoint == endPoint) {
    return;
  }

  if (startPoint == NULL || endPoint == NULL) {
    return;
  }

  ListNode * current = startPoint;
  ListNode * temp;
  ListNode * start = startPoint->prev;
  ListNode * end = endPoint->next;

  ListNode * originalStartPoint = startPoint;
  ListNode * originalEndPoint = endPoint;

  while (current != endPoint) {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    current = current->prev;
  }

  endPoint->next = endPoint->prev;
  endPoint->prev = start;
  startPoint->next = end;

  if (end == NULL) {
    tail_ = startPoint;
  } else {
    end->prev = startPoint;
  }

  if (start == NULL) {
    head_ = endPoint;
  } else {
    start->next = endPoint;
  }

  startPoint = originalEndPoint;
  endPoint = originalStartPoint;

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  ListNode * start = head_;
  ListNode * end = head_;
  int count = 1;

  while (start != NULL) {
    while (count <= n - 1) {
      if (end->next == NULL) {
        break;
      }
      end = end->next;
      count++;
    }
    reverse(start, end);
    start = end->next;
    end = start;
    count = 1;
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
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
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  // return NULL;
  ListNode * list_head;

  if (first->data < second->data) {
		list_head = first;
		first = first->next;
	} else {
		list_head = second;
    second = second->next;
  }

	ListNode * current = list_head;

	while (first != NULL && second != NULL) {

		if (first->data < second->data) {
			current->next = first;
			first->prev = current;
			first = first->next;
		} else {
			current->next = second;
			second->prev = current;
			second = second->next;
		}
		current = current->next;
	}

	if (first == NULL && second != NULL) {
		current->next = second;
		second->prev = current;
	}
	if (second == NULL && first != NULL) {
		current->next = first;
		first->prev = current;
	}

  return list_head;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  // return NULL;

  if (chainLength == 0 || chainLength == 1) {
    start->prev = NULL;
    start->next = NULL;
    return start;
  }

  int splitPoint;
  splitPoint = (chainLength / 2);

  ListNode * temp = start;

  for(int i = 1; i <= splitPoint; i++){
    temp = temp->next;
  }

  if (temp != NULL){
    temp->prev->next = NULL;
    temp->prev = NULL;
  }

  start = mergesort(start, splitPoint);

  temp = mergesort(temp, chainLength - splitPoint);

  start = merge(start, temp);

  return start;
}
