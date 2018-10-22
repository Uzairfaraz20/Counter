/*counter.h*/

//
// <<YOUR NAME>>
// U. of Illinois, Chicago
// CS 341, Fall 2018
// Project #03: Counter container
//
// The Counter container is a set with no duplicates.  However, it keeps
// a count of how many times an element was inserted, hence the name
// "Counter".  Users of the Counter container can test for set membership,
// as well as obtain an element's count.
// 
// Example:  suppose C is a Counter, and you insert the elements 3, 11, 
// 5, 11, 3, and 11.  Then C contains the elements {3, 5, 11}, where 3's 
// count is 2, 5's count is 1, and 11's count is 3.
//
// Given N elements, search operations are O(lgN), and insert is O(N); these
// are average-time complexities.  In terms of space, the container will 
// consume at most 4N space.
// 

#pragma once

#include <iostream>
#include <iterator>

using std::cout;  // for debug printing:
using std::endl;


template<typename T>
class Counter
{
private:

  class element {
	  
	  T value; //templated value because type not known
	  int count; //number of times element appears

  public:
	  //default constructor
	  element() {

	  } 

	  element(T val) {
		  value = val;
		  count = 1;
	  }

	  int getCount() {
		  return count;
	  }

	  T getValue() {
		  return value;
	  }

	  void setCount(int c) {
		  count = c;
	  }
 
  };
  class iterator
  {
	  element* elementArray;
	  int index;
	  int length;

	public:
		iterator(element* eArray, int idx,int len) {
			elementArray = eArray;
			index = idx;
			length = len;
		}

		iterator& operator++() {
			index++;
			return *this;
		}

		const T& operator*() {
			if (index >= length) {
//				index = length - 1;
				return NULL;
			}
			element temp = elementArray[index];
			
			return temp.getValue();
		}

		bool operator!=(const iterator& rhs) {
			if (index >= length) {
				index = length;
			}
			return index != rhs.index;
		}
		
		
    
  };
  
  
  int bLookup(T value, int low, int high){
	  
	  if (high >= low){
		  
		  int mid = low + (high - low) / 2;

		  if (equalTo(elementArray[mid].getValue(),value)) {
			  return mid;
		  }

		  if (value < elementArray[mid].getValue()) {
			  return bLookup(value, low, mid - 1);
		  }

		  return bLookup(value, mid + 1, high );
	  }

	  return -1;
  }
  
  int bSearch(T value, int low, int high) {
	  if (length == 0 && low == high) {
		  return low;
	  }
	  if (high <= low) {
		  if (low == length) {
			  return low;
		  }
		  if (elementArray[low].getValue() < value) {
			  return (low + 1);
		  }
		  else {
			  return low;
		  }
	  }

	  int mid = (low + high) / 2;

	  if ( equalTo(elementArray[mid].getValue(), value) )
		  return mid;

	  
	  if ( elementArray[mid].getValue() < value ) {
		  return bSearch(value, mid + 1, high);
		}

	 
	  return bSearch(value, low, mid - 1);

  }


  void insertInOrder(T value)
 {
	  if (length == 0) {
		  elementArray[0] = element(value);
		  length++;
		  return;
	  }

	  int index; int j = 0;
	  index = bSearch(value, 0, length);
	  if (index < length) {
		  element curr = elementArray[index];
		  if ( equalTo(curr.getValue(), value) ) {
			  curr.setCount(curr.getCount() + 1);
			  elementArray[index] = curr;
			  return;
		  }
		  j = length;



		  while (j >= index) {
			  elementArray[j + 1] = elementArray[j];
			  j--;
		  }

		  elementArray[j + 1] = element(value);
		  length++;
	  }
	  else {
		  elementArray[index] = element(value);
		  length++;
	  }
	  
  }

  bool equalTo(T x, T y) {
	  return (!(x < y)) && (!(y < x));
  }

 ////////////////Dynamic Array///////////////////
  
  int length; //how much is filled up
  int capacity; //how much it can hold
  element* elementArray;
 
////////////////////////////////////////////////

  //function to increase array size by a factor of 4
  void growArray() {	  
	  capacity *= 4;
	  element* temp = new element[capacity]; //new array of size 4n
	  for (int i = 0; i < length; i++){
		  temp[i] = elementArray[i];
	  }
	  
	  elementArray = temp;
	 

  }
  
  //set to default values
  void initialize() {
	  length = 0;
	  capacity = 4;
	  delete[] elementArray;
	  elementArray = new element[capacity];
  }

public:
  
  // constructor:
  Counter()
  {
	  initialize();
  }
  
  
  
  // copy constructor (deep copy)
  Counter(const Counter& other)
  {
	 
	  length = other.length;
	  capacity = other.capacity;
	  elementArray = new element[capacity];
	  
	  for (int i = 0; i < length; i++) {
		  element temp = other.elementArray[i];
		  element lhsTemp = element(temp.getValue());
		  lhsTemp.setCount(temp.getCount());
		  elementArray[i] = lhsTemp;
	  }

  }
  
  
  
  // destructor:
  ~Counter()
  { 
	  delete[] elementArray;
  }


  // DONE
  // size()
  // 
  // Returns the # of elements in the set.
  // 
  // Time complexity: O(1).
  // 
  int size() const
  {
    return length;
  }
  
  
  // DONE
  // empty()
  //
  // Returns true if the set is empty, false if not.
  // 
  // Time complexity: O(1).
  // 
  bool empty() const
  {
    return (length == 0);
  }
  
  
  //DONE
  // clear()
  //
  // Empties the set, deleting all elements and counts.
  //
  void clear()
  {
	  initialize();
  }
  
  
  //
  // [e]
  //
  // Returns true if set contains e, false if not.
  //
  // NOTE: since the type of e is unknown, elements are compared using <. 
  // This implies 2 elements x and y are equal if (!(x<y)) && (!(y<x)).
  // 
  // Time complexity: average-case O(lgN).
  //
  bool operator[](const T& e)
  {
    
	  int index;
	  index = bLookup(e, 0, length);
	  if (index >= 0) {
		  return true;
	  }
    
    return false;
  }


  //
  // (e)
  // 
  // Returns a count of how many times e has been inserted into the set;
  // the count will be 0 if e has never been inserted.
  // 
  // NOTE: since the type of e is unknown, elements are compared using <. 
  // This implies 2 elements x and y are equal if (!(x<y)) && (!(y<x)).
  // 
  // Time complexity: average-case O(lgN).
  // 
  int operator()(const T& e) 
  {
    
	  int index;
	  index = bLookup(e, 0, length);
	  if (index == -1) {
		  return -1;

	  }
	  else {
		  return elementArray[index].getCount();
	  }


  
  }
  
  
  // DONE
  // insert(e)
  // 
  // If e is not a member of the set, e is inserted and e's count set to 0.
  // If e is already in the set, it is *not* inserted again; instead, e's
  // count is increased by 1.  Sets are unbounded in size, and elements are
  // inserted in order as defined by T's < operator; this enables in-order 
  // iteration.
  // 
  // NOTE: since the type of e is unknown, elements are compared using <. 
  // This implies 2 elements x and y are equal if (!(x<y)) && (!(y<x)).
  // 
  // Time complexity: worst-case O(N).
  // Space complexity: 4N.
  //
  void insert(const T& e)
  {
	  if (length == capacity-1) {
		  growArray();
	  }

	  insertInOrder(e);
  }
  
  
  // 
  // += e
  //
  // Inserts e into the set; see insert.
  //
  // Time complexity: worst-case O(N).
  // Space complexity: 4N.
  // 
  Counter& operator+=(const T& e)
  {
    //
    // insert e into "this" set:
    //
    this->insert(e);

    // return "this" updated set:
    return *this;
  }
  
  
  //
  // lhs = rhs;
  //
  // Makes a deep copy of rhs (right-hand-side) and assigns into
  // lhs (left-hand-side).  Any existing elements in the lhs
  // are destroyed *before* the deep copy is made.
  // 
  // NOTE: the lhs is "this" object.
  //
  Counter& operator=(const Counter& rhs)
  {
    //
    // NOTE: where is the lhs in the function call?  The lhs operand is 
    // hidden --- it's "this" object.  So think this->operator=(rhs).  
    //

    // check for self-assignment:
    if (this == &rhs)  // S = S;
      return *this;

	//clear lhs
	delete[] elementArray;
	length = 0;
	capacity = 0;

	//assign rhs properties.
	length = rhs.length;
	capacity = rhs.capacity;
	elementArray = new element[capacity];
	for (int i = 0; i < length; i++) {
		element temp = rhs.elementArray[i];
		element lhsTemp = element(temp.getValue());
		lhsTemp.setCount(temp.getCount());
		elementArray[i] = lhsTemp;
	}

    // return "this" updated set:
    return *this;
  }
  

  //
  // begin()
  // 
  // Returns an iterator denoting the first element of the set.  If the 
  // set is empty, begin() == end().  The iterator will advance through
  // the elements in order, as defined by T's < operator.
  //
  iterator begin()
  {
    return iterator(elementArray, 0, length);
  }
  
  
  //
  // end()
  // 
  // Returns an iterator denoting the end of the iteration space --- i.e.
  // one past the last element of the set.  If the set is empty, then
  // begin() == end().
  // 
  iterator end()
  {
    return iterator(elementArray, length, length);
  }

  void print() {
	  
	  for (int i = 0; i < length; i++) {
		  cout << elementArray[i].getValue() << " - "<< elementArray[i].getCount() << endl;
	  }
  }



};
