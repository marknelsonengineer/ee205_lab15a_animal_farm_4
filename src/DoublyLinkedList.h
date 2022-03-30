///////////////////////////////////////////////////////////////////////////////
///         University of Hawaii, College of Engineering
/// @brief  ee205_lab10d_animal_farm_3 - EE 205 - Spr 2022
///
/// A generic DoublyLinkedList collection class.
///
/// @file DoublyLinkedList.h
/// @version 1.0
///
/// @author Mark Nelson <marknels@hawaii.edu>
/// @date   26_Mar_2022
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "NodeWithPrev.h"
#include "List.h"

/*
bool isEmpty()       // true if Collection is empty
void add( thing )    // Insert into the beginning
void append( thing ) // Add to the end
void addAt( index, thing )  // Add at a location
int size()   // Number of items in the collection
thing get( index ) // Get via index
thing get( key )   // Get via key
void put ( index, thing ) // Replace an existing value
void put ( thing ) // Replace an existing value
thing find( criteria ) // Find a thing (or NULL)
iterator getIterator() // Loop over a bunch of things
void delete ( index )  // Delete an index…
void delete ( key )    // by key
void delete ( thing )  // Delete the thing
 */



/// A generic DoublyLinkedList collection class.
///
class DoublyLinkedList : List {
protected:  ////////////////////// Protected Members ///////////////////////////
   NodeWithPrev* head = nullptr ;     ///< The head pointer for the collection
   NodeWithPrev* tail = nullptr ;     ///< The tail pointer for the List

public:  ///////////////////////// Public Constructors /////////////////////////
   DoublyLinkedList();        ///< Make a new DoublyLinkedList

public:  /////////////////////////// Public Methods ////////////////////////////
   void  push_front( NodeWithPrev* newNode ) ; ///< Insert `newNode` to the beginning of the List
   void  push_back( NodeWithPrev* newNode )  ; ///< Append `newNode` to the end of the List
   NodeWithPrev* pop_front() noexcept ;        ///< Remove and return the first NodeWithPrev in the List
   NodeWithPrev* pop_back() noexcept ;         ///< Remove and return the last NodeWithPrev in the List

   void insert_after( NodeWithPrev* currentNode, NodeWithPrev* newNode ) ;  ///< Insert `newNode` after `currentNode`
   void insert_before( NodeWithPrev* currentNode, NodeWithPrev* newNode ) ; ///< Insert `newNode` before `currentNode`

   void swap( NodeWithPrev* node1, NodeWithPrev* node2 ) ;  ///< Swap `node1` and `node2`

   void insertionSort() noexcept ;  ///< Runs the insertion sort algorithm on the List

   NodeWithPrev* get_last() const noexcept ;                   ///< Get the last NodeWithPrev in the List
   static NodeWithPrev* get_prev( const NodeWithPrev* currentNode ) ;  ///< Get the previous NodeWithPrev in the List

   void dump() const noexcept override ;      ///< Output the contents of this container
   bool validate() const noexcept override ;  ///< Check to see if the container is valid
} ;  // class DoubleLinkedList
