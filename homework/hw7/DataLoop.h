#ifndef __DATALOOP_H__
#define __DATALOOP_H__

#include <iostream>

/**
 * \class DataLoop
 * \defgroup DataLoop
 * \brief An integer dataloop
 */
class DataLoop {
public:
  /**
   * \brief The default constructor
   *
   * \detail The default constructor creates an empty DataLoop, i.e. start is nullptr and count is 0.
   */
  DataLoop();
  
  /**
   * \brief An alternate constructor
   *
   * \detail This alternate constructor creates a DataLoop with one node that contains the parameter value. The node is dynamically allocated and should be the start of the loop. Its next and prev fields should point to itself.
   *
   * \param[in] num The integer value to be added to the DataLoop
   */
  DataLoop(const int & num);
  
  /**
   * \brief The copy constructor
   *
   * \detail The copy constructor creates a copy of the parameter DataLoop (rhs)
   *
   * \param[in] rhs A constant reference to the function input DataLoop object
   */ 
  DataLoop(const DataLoop & rhs);
  
  /**
   * \brief Overloaded operator= to assign a DataLoop to another DataLoop
   *
   * \detail This overloaded operator assigns the input DataLoop (rhs) to the current DataLoop (*this, the current object).
   *
   * \note If the current DataLoop is not empty, this function releases formerly allocated memory as needed to avoid memory leaks. 
   *
   * \param[in] rhs A constant reference to the input DataLoop object
   *
   * \return A reference to the updated DataLoop object
   */
  DataLoop & operator=(const DataLoop & rhs); 
  
  /**
   * \brief The destructor
   *
   * \detail The destructor releases allocated memory as needed to avoid leaks.
   */
  ~DataLoop();

  
  /**
   * \brief Overloaded operator== to check if two DataLoops are the same
   *
   * \detail This operator compares the current DataLoop (*this) with the input DataLoop (rhs). It returns true if both DataLoops are the same node by node, including the starting position and count. Otherwise, it returns false.
   *
   * \param[in] rhs A constant reference to a DataLoop object to compare
   *
   * \return true if two DataLoops are the same node by node, else false
   */
  bool operator==(const DataLoop & rhs) const;
  
  /**
   * \brief Overloaded operator+= to add a value to the end of this dataloop
   *
   * \detail This operator takes an integer, creates a new _Node to hold it, and inserts that at the end of this dataloop. In other words, the new node will be immediately before the start node, but the start is not changed. 
   *
   * \param[in] num A constant reference to an integer value
   *
   * \return A reference to this updated DataLoop object with the new value added
   */
  DataLoop & operator+=(const int & num);

  /**
   * \brief Overloaded operator+ to concatenate copies of two DataLoops
   *
   * \detail This operator creates a third DataLoop by concatenating copies of the current DataLoop (*this) and the parameter DataLoop (rhs), adding the rhs copy to the end of the current DataLoop copy. The start position for the new DataLoop should mimic the start of *this and the count should be updated as well. [Note that the original DataLoops are not affected.]
   *
   * \param[in] rhs A constant reference to a DataLoop object to add to the end of *this
   *
   * \return A new DataLoop object with the concatenated result
   */
  DataLoop operator+(const DataLoop & rhs) const;
  
  
  /**
   * \brief Overloaded operator^ to shift the start position in *this DataLoop according to the parameter offset - forward for a positive value and backward for a negative value
   *
   * \detail This overloaded operator takes an integer and shifts the starting position forward (positive num) or backward (negative num) that many nodes, looping around as much as necessary. [A 0 offset does not make any changes, and no changes are made to an empty DataLoop or one with only one _Node.]
   *
   * \param[in] offset The number of nodes/positions to move the start position, positive for forward shifting, negative for backward motion
   *
   * \return A reference to the updated DataLoop object
   */
  DataLoop & operator^(int offset);


  /**
   * \brief Function splice to insert an entire DataLoop into this one
   *
   * \detail This function inserts the entire parameter DataLoop (rhs) into the current DataLoop (*this) at the indicated position (pos), where 0 would indicate the starting position of the current DataLoop and update `start` accordingly. An insert position of n would indicate that the start node of rhs comes after node n in the current DataLoop (assuming you start counting nodes with 1). The values from the input DataLoop (rhs) should be inserted in their current order, beginning with that object's starting node. The count for the current DataLoop should be updated. If the indicated position is larger than the current count, effectively loop around as much as necessary to get to the indicated spot. This function must also reset the parameter dataloop, making rhs an empty list, since both can't co-exist.
   *
   * \param[in] rhs A reference to a DataLoop object to insert into *this
   *
   * \param[in] pos The insertion position 
   *
   * \return A reference to the updated DataLoop object 
   */
  DataLoop & splice(DataLoop & rhs, size_t pos);
  

  /**
   * \brief Function length to report the number of nodes in *this DataLoop
   *
   * \return The number of nodes
   */
  int length() const { return count; }  // TODO


  /**
   * \brief Overloaded output stream operator<< to print the DataLoop
   *
   * \detail This operator prints the input DataLoop (dl) to the ostream (os) in the format 
   * "-> data1 <--> data2 <--> ... <--> datax <-" where data1 is the value in the start node
   *   e.g. if we have a DataLoop with three elements 32, 12, 20 starting at 12
   *        it will print "-> 12 <--> 20 <--> 32 <-"
   *   If the DataLoop is empty, it prints ">no values<".
   *
   * \param[in] os A reference to the output stream object
   * \param[in] q A constant reference to the DataLoop object to be printed
   *
   * \return A reference to the output stream object
   */
  friend std::ostream & operator<<(std::ostream & os, const DataLoop & dl);
  
private:
  /// friend DataLoopTest struct to allow the test struct access to the private data
  friend struct DataLoopTest;
  
  /**
   * \struct _Node
   * \brief A private structure to represent a node in a DataLoop
   */
  struct _Node {
    int data;     ///< Integer node data
    _Node *next;  ///< A pointer to the next node
    _Node *prev;  ///< A pointer to the previous node
  };

  _Node* start;   ///< a pointer to the starting node position in the DataLoop
  size_t count;   ///< the count of how many nodes/values are in the structure
};

#endif // __DATALOOP_H__
