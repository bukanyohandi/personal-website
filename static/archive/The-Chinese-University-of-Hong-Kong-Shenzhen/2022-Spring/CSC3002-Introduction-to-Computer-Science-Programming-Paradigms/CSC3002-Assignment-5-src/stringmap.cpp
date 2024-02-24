/*
 * File: stringmap.cpp
 * -------------------
 * This file implements the stringmap.h interface using a hash table
 * with open addressing as the underlying representation.
 */

#include <iostream>
#include <string>
#include "error.h"
#include "stringmap.h"
using namespace std;


/* Constant definitions */

   const int StringMap::INITIAL_BUCKET_COUNT = 13;
   const double StringMap::REHASH_THRESHOLD = 0.7;


/*
 * Implementation notes: HashMap constructor and destructor
 * --------------------------------------------------------
 * The constructor allocates the array of buckets and initializes each
 * bucket to the empty list.  The destructor frees the allocated cells.
 */

StringMap::StringMap() {
   nBuckets = INITIAL_BUCKET_COUNT;
   buckets = new KeyValuePair[nBuckets];
   clear();
}

StringMap::~StringMap() {
   delete[] buckets;
}

/*
 * Implementation notes: get
 * -------------------------
 * The get method calls findKeyValuePair to search the linked list for the
 * matching key.  If no key is found, get returns the empty string.
 */

string StringMap::get(const string & key) const {
   int index = findKey(key);
   return (index == -1) ? "" : buckets[index].value;
}

/*
 * Implementation notes: put
 * -------------------------
 * The put method calls insertKey to search the bucket array for a matching
 * key.  If a key already exists, put simply resets the value field.  If no
 * matching key is found, put adds a new entry in the first free slot.
 */

void StringMap::put(const string & key, const string & value) {
   if ((double) count / nBuckets > REHASH_THRESHOLD) {
      rehash(2 * nBuckets + 1);
   }
   int index = insertKey(key);
   buckets[index].value = value;
}

int StringMap::size() const {
   return count;
}

bool StringMap::isEmpty() const {
   return count == 0;
}

bool StringMap::containsKey(const string & key) const {
   return findKey(key) != -1;
}

/*
 * Implementation notes: remove
 * ----------------------------
 * This implementation is tricky because removing one key can make later
 * keys inaccessible.  This implementation finds the first key that could
 * have gone in this position (if any) and moves it to this space, repeating
 * that process until an empty entry is found.  A much simpler but less
 * efficient strategy is to rehash after every deletion.
 */

void StringMap::remove(const string & key) {
   int index = findKey(key);
   if (index != -1) {
      buckets[index].occupied = false;
      count--;
      int toFill = index;
      while (true) {
         index = (index + 1) % nBuckets;
         if (!buckets[index].occupied) return;
         if (insertKey(buckets[index].key) == toFill) {
            buckets[toFill].value = buckets[index].value;
            buckets[index].occupied = false;
            toFill = index;
         }
      }
   }
}

void StringMap::clear() {
   for (int i = 0; i < nBuckets; i++) {
      buckets[i].occupied = false;
   }
   count = 0;
}

int StringMap::getNBuckets() {
   return nBuckets;
}

/*
 * Implementation notes: rehash
 * ----------------------------
 * The rehash method iterates over the existing key-value pairs, entering
 * them into a new table.
 */

void StringMap::rehash(int __nBuckets){
    KeyValuePair *tmp;

    tmp = new KeyValuePair[nBuckets];
    for(int idx = 0; idx < nBuckets; ++idx){
        tmp[idx].occupied = buckets -> occupied;
        tmp[idx].key = buckets -> key;
        tmp[idx].value = buckets -> value;
    }

    buckets = new KeyValuePair[__nBuckets];
    for(int idx = 0; idx < nBuckets; ++idx){
        buckets[idx].occupied = tmp -> occupied;
        buckets[idx].key = tmp -> key;
        buckets[idx].value = tmp -> value;
    }
    nBuckets = __nBuckets;

    return;
}


/*
 * Private method: findKey
 * Usage: int index = findKey(key);
 * --------------------------------
 * This private method looks for a key in the buckets array.  If the
 * key is found, findKey returns its index.  If no match is found, the
 * findKey returns -1.
 */

int StringMap::findKey(const std::string & key) const{
    for(int idx = 0; idx < nBuckets; ++idx){
        if(buckets[idx].occupied == true &&
                buckets[idx].key == key){
            return idx;
        }
    }

    return -1;
}

/*
 * Private method: insertKey
 * Usage: int index = insertKey(key);
 * ----------------------------------
 * This private method is identical to findKey except that it inserts the
 * key in the correct place if it is not already in the table.
 */

int StringMap::insertKey(const std::string & key){
    int idx, hash_value = hashCode_(key);

    idx = findKey(key);
    if(idx != -1) return idx;

    idx = hash_value;
    while(idx < INITIAL_BUCKET_COUNT){
        if(buckets[idx].occupied == false){
            buckets[idx].occupied = true;
            buckets[idx].key = key;
            count += 1;
            return idx;
        }
        idx++;
    }

    idx = 0;
    while(idx < hash_value){
        if(buckets[idx].occupied == false){
            buckets[idx].occupied = true;
            buckets[idx].key = key;
            count += 1;
            return idx;
        }
        idx++;
    }

    return -1;
}

/*
 * Implementation notes: hashCode
 * ------------------------------
 * This function takes a string key and uses it to derive a hash code,
 * which is nonnegative integer related to the key by a deterministic
 * function that distributes keys well across the space of integers.
 * The specific algorithm used here is called djb2 after the initials
 * of its inventor, Daniel J. Bernstein, Professor of Mathematics at
 * the University of Illinois at Chicago.
 */

const int HASH_SEED = 5381;               /* Starting point for first cycle */
const int HASH_MULTIPLIER = 33;           /* Multiplier for each cycle      */
const int HASH_MASK = unsigned(-1) >> 1;  /* The largest positive integer   */

int hashCode_(const string & str) {
   unsigned hash = HASH_SEED;
   int n = str.length();
   for (int i = 0; i < n; i++) {
      hash = HASH_MULTIPLIER * hash + str[i];
   }
   return int(hash & HASH_MASK);
}
