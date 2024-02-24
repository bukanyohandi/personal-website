/*
 * File: pqueue.h
 * --------------
 * This file exports the PriorityQueue class, a collection in which values
 * are processed in priority order.
 */

#ifndef _pqueue_h
#define _pqueue_h

#include "vector.h"
#include "error.h"
using namespace std;

/*
 * Class: PriorityQueue<ValueType>
 * -------------------------------
 * This class models a structure called a priority queue in which values
 * are processed in order of priority.  As in conventional English usage,
 * lower priority numbers correspond to higher effective priorities, 
 * so that a priority 1 item takes precedence over a priority 2 item.
 */

template <typename ValueType>
class PriorityQueue {

public:

/*
 * Constructor: PriorityQueue
 * Usage: PriorityQueue<ValueType> pq;
 * -----------------------------------
 * Initializes a new priority queue, which is initially empty.
 */

   PriorityQueue();

/*
 * Destructor: ~PriorityQueue
 * --------------------------
 * Frees any heap storage associated with this priority queue.
 */

   virtual ~PriorityQueue();



/*
 * Method: size
 * Usage: int n = pq.size();
 * -------------------------
 * Returns the number of values in the priority queue.
 */

   int size() const;

/*
 * Method: isEmpty
 * Usage: if (pq.isEmpty()) ...
 * ----------------------------
 * Returns true if the priority queue contains no elements.
 */

   bool isEmpty() const;

/*
 * Method: clear
 * Usage: pq.clear();
 * ------------------
 * Removes all elements from the priority queue.
 */

   void clear();

/*
 * Method: enqueue
 * Usage: pq.enqueue(value, priority);
 * -----------------------------------
 * Adds value to the queue with the specified priority.  
 * Lower priority numbers correspond to higher priorities, 
 * which means that all 
 * priority 1 elements are dequeued before any priority 2 elements.
 */

   void enqueue(ValueType value, double priority);

/*
 * Method: dequeue
 * Usage: ValueType first = pq.dequeue();
 * --------------------------------------
 * Removes and returns the highest priority value.  
 * If multiple entries in
 * the queue have the same priority, 
 * those values are dequeued in the same
 * order in which they were enqueued.
 */

   ValueType dequeue();

/*
 * Method: peek
 * Usage: ValueType first = pq.peek();
 * -----------------------------------
 * Returns the value of highest priority in the queue, without removing it.
 */

   ValueType peek() const;

/*
 * Method: peekPriority
 * Usage: double priority = pq.peekPriority();
 * -------------------------------------------
 * Returns the priority of the first element in the queue, 
 * without removing it.
 */

   double peekPriority() const;

/*
 * Method: toString
 * Usage: string str = pq.toString();
 * ----------------------------------
 * Converts the queue to a printable string representation.
 */

   std::string toString();

/* Private section */

/**********************************************************************/
/* Note: Everything below this point in the file is logically part    */
/* of the implementation and should not be of interest to clients.    */
/**********************************************************************/

/*
 * Implementation notes: PriorityQueue data structure
 * --------------------------------------------------
 * The PriorityQueue class is implemented using a data structure called a
 * heap.
 */

private:

/* Type used for each heap entry */

   struct HeapEntry {
      ValueType value;

      double priority;

      long sequence; 
      /* order of enqueue, which used for recording the order of which the elements are inserted, 
      /* i.e.: when two elements are of the same priority, 
       * it depends on the order of the sequence that
       * the first inserted element should be dequeued first
       */ 

   };

/* Instance variables */

   Vector<HeapEntry> heap;
   long enqueueCount; // to record the sequence
   int count;         // to record the number of elements in the PriorityQueue
   int capacity;      // capacity of the heap

/* Private function prototypes */

   void enqueueHeap(ValueType & value, double priority); 
   ValueType dequeueHeap();
   bool takesPriority(int i1, int i2);
   void swapHeapEntries(int i1, int i2);

};


template <typename ValueType>
PriorityQueue<ValueType>::PriorityQueue() {
   clear();
}

/*
 * Implementation notes: ~PriorityQueue destructor
 * -----------------------------------------------
 * All of the dynamic memory is allocated in the Vector class, so no work
 * is required at this level.
 */

template <typename ValueType>
PriorityQueue<ValueType>::~PriorityQueue() {
   /* Empty */
}

template <typename ValueType>
int PriorityQueue<ValueType>::size() const{
    return count;
}

template <typename ValueType>
bool PriorityQueue<ValueType>::isEmpty() const{
    if(count == 0)
        return true;
    else
        return false;
}

template <typename ValueType>
void PriorityQueue<ValueType>::clear(){
   heap.clear();
   count = 0;
}

template <typename ValueType>
void PriorityQueue<ValueType>::enqueue(ValueType value, double priority){
   int idx;

   if((int)heap.size() == count) heap.add(HeapEntry());
   if(floatingPointEqual(priority, 0.0, 1e-6)) priority = 0;

   idx = count;
   heap[idx] = (HeapEntry){.value = value, .priority = priority, .sequence = enqueueCount};

   count++;
   enqueueCount++;

   if(idx == 0 || takesPriority(capacity, idx)) capacity = idx;
   for(; idx > 0;){
      int parent = (idx - 1) / 2;
      if(!takesPriority(parent, idx)){
          swapHeapEntries(parent, idx);
          idx = parent;
      } else {
          break;
      }
   }
}

template <typename ValueType>
ValueType PriorityQueue<ValueType>::dequeue(){
   if (count == 0) error("[Error] queue is empty.");

   int idx, descendant;
   bool taken = false;
   if(capacity == --count){
       taken = true;
   }
   ValueType value = heap[0].value;
   swapHeapEntries(0, count);
   for(idx = 0; ; idx = descendant) {
      if(2 * idx + 1 >= count) break;
      descendant = 2 * idx + 1;
      if(   2 * idx + 2 < count
                &&
            takesPriority(2 * idx + 2, 2 * idx + 1))
          descendant = 2 * idx + 2;
      if(takesPriority(idx, descendant)) break;
      swapHeapEntries(idx, descendant);
   }
   if(taken) capacity = idx;
   return value;
}

template <typename ValueType>
ValueType PriorityQueue<ValueType>::peek() const{
    if (count == 0) error("[Error] queue is empty.");

    return heap.get(0).value;
}

template <typename ValueType>
double PriorityQueue<ValueType>::peekPriority() const{
    if (count == 0) error("[Error] queue is empty.");

    return heap.get(0).priority;
}

template <typename ValueType>
std::string PriorityQueue<ValueType>::toString(){
    std::string ret = "";

    PriorityQueue<ValueType> tmp = *this;
    int sz = tmp.size();
    for(int idx = 0; idx < sz; ++idx){
        if(idx != 0) ret += ", ";

        ostringstream os;
        os << "(" << tmp.peekPriority() << ", " << tmp.dequeue() << ")";
        ret += os.str();
    }

    return "queue contains: " + ret;
}

template <typename ValueType>
bool PriorityQueue<ValueType>::takesPriority(int i1, int i2){
    if(heap[i1].priority != heap[i2].priority)
        return heap[i1].priority < heap[i2].priority;
    return heap[i1].sequence < heap[i2].sequence;
}

template <typename ValueType>
void PriorityQueue<ValueType>::swapHeapEntries(int i1, int i2){
    swap(heap[i1], heap[i2]);
}

#endif
