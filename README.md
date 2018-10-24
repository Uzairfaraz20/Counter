# Counter 
 An STL style implementation for a custom "Count" container
 -  This  is  a  set-like  container  of  elements  of  any  type  T.
 - Like  a  mathematical  set, the Counter does not allow  duplicates. However,  the  container  keeps  a  count,  per  element,  as  to  the  #  of  times  that  particular  element  was  inserted.    
 - **Example:**
 
 ```
   Counter<int> C;
   C.insert(3);
   C.insert(5);
   C.insert(11);
   C.insert(5);
   ```

- At  this  point  C  contains  {3,  5,  11},  where  3’s  count  is  1,  5’s  count  is  2,  and  11’s  count  is  1.
 
- The elements  of  the  set  are  ordered  to  enable  efficient  lookup.

## Implementation
   - Counter is implemented using a Dynamic Array, very similar to how std::Vector is implemented. However, elements in Counter
     are maintained in order to improve efficiency of operations.
## Time/Space Complexities 
- Overall Space: O(4n)
- Search Time: O(log N)
- Insertion Time: θ(N)

## Iterator Supoort 
- Counter provides basic iterator support. That is, only enough operations to support a range based for loop. Counter Supports Begin(),
end(), and iter++ to be able to traverse using a for-each loop.

## Misc 
- Counter was tested using the Catch Unit Testing framework. The framework files are included in the repo.
- Counter includes overloaded += and =, where += inserts element e into the Counter and = creates a deep copy of
the right hand side and assign it to the left.
- Most trivial operations such as size(), isEmpty(), etc., run in O(1).

## Issues
- Need to fix memory leaks (Tested with Valgrind).
