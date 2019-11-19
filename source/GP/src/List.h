#ifndef LIST_H_
#define LIST_H_

#include <assert.h>

#include <cstddef> //for NULL
#include <iostream>

using namespace std;

template < class listdata >  // List stores generic listdata, not only specific C++ type
class List {

private:
    struct Node {
        listdata data;
        Node* next;
        Node* prev;


        Node(listdata newData){
            data = newData;
            next = NULL;
            prev = NULL;

        }
    };

    Node* first;
    Node* last;
    int length;
    Node* iterator;

    void reversePrint(Node* node) const;
    // Helper function for the public reverse function

    bool isSorted(Node* node) const;
    // Helper function for the public isSorted function

    int binarySearch(int low, int high, listdata data) const;
    // Helper function for the public binarySearch function



public:

    /**Constructors and Destructors*/

    List();
    //Default constructor; initializes and empty list
    //Postcondition: initializes the parameters and create an empty list

    List(const List &list); // this is a copy constructer which do a deep copy

    ~List();
    //Destructor. Frees memory allocated to the list
    //Postcondition: Free any memory allocated to the list

    /**Accessors*/

    listdata getFirst() const ;// can return generic data
    //Returns the first data in the list
   //Precondition: Length is not equal to zero

    listdata getLast() const; // can return generic data
    //Returns the last data in the list
   	//Precondition: Length is not equal to zero

    bool isEmpty() const;  // don't need to alter to generic data
    //Determines whether a list is empty.

    int getLength() const; // don't need to alter to generic data since length is always a number
    //Returns the size of the list

    listdata getIterator () const; //Returns the element currently pointed at by the iterator

    bool offend () const; 			//Reruns whether the iterator is off the end of the list
    bool isSorted () const;		//Wrapper function that calls the isSorted helper function
    int getIndex () const;		//Indicates the index of the Node where the iterator is currently pointing
    int linearSearch(listdata data) const; 	//Search the list, element by element, from the start of the List to the end of the List
    int binarySearch(listdata data) const;   //Returns the index where data is located in the List

    /**Manipulation Procedures*/

    void removeFirst();
    //Removes the value stored in first node in the list
   	//Precondition: Length is not equal to zero
    //Postcondition: remove the first node from the list

    void removeLast();
    //Removes the value stored in the last node in the list
 	//Precondition: Length is not equal to zero
    //Postcondition: remove the last node from the list

    void insertFirst (listdata data); // this function can now get generic data
    //Inserts a new data at the beginning of the list
    //If the list is empty, the new data becomes both first and last
    //Postcondition: new data added to the front of the list

    void insertLast(listdata data); // this function can now get generic data
    //Inserts a new data at the end of the list
    //If the list is empty, the new data becomes both first and last
    //Postcondition: new data added to the end of the list


    void startIterator ();    	// moves the iterator to the start of the list

    void removeIterator();		//remove the element which iterator is pointing to
    void insertIterator(listdata data); 	//inserts an element after the node currently pointed to by the iterator
    void advanceIterator();		// moves the iterator up by one node
    void reverseIterator(); 		//moves the iterator down by one node
    void advanceToIndex(int index); 	//Moves the iterator to the node whose index number is specified in the parameter

    /**Additional List Operations*/

    void printList(ostream& os) const;
    //Prints to the console the value of each data in the list sequentially
    //and separated by a blank space
    //Prints nothing if the list is empty
    //Prints a empty newline character if it's empty..
    void printNumberedList() const;

    bool operator==(const List &list);
    //Tests two lists to determine whether their contents are equal
    //Postcondition: returns true if lists are equal and false otherwise

    void reversePrint() const;
    // Wrapper function that calls the reverse helper function to print a list in reverse
    //postcondition: prints nothing if the list is empty


};
template < class listdata >  // will tempate the function
List<listdata>::List() {     // list is tempated and takes generic data
    first = NULL;
    last = NULL;
    length = 0;
    iterator=NULL;
}

template <class listdata>
List<listdata>::List(const List<listdata> &list)
{
    if(list.first == NULL) //If the original list is empty, make an empty list for this list
    {
        first = last = iterator = NULL;
    }
    else
    {
        first = new Node(list.first->data); //calling Node constructor
        Node* temp = list.first; //set a temporary node pointer to point at the first of the original list
        iterator = first; //set iterator to point to first node of the new list
        while(temp->next != NULL)
        {
            temp = temp->next; //advance up to the next node in the original list
            iterator->next = new Node(temp->data); //using node constructor to create new node w/ copy of data
           iterator->next->prev=iterator;
            iterator = iterator->next; //advance to this new node
        }
        first->prev=NULL;
        last = iterator; //Why do I need this line of code? //iterator is at the last node, this line set the last pointer to the last node
        //last->next = NULL;
    }
    length = list.length;
}

template < class listdata> // will template function
List<listdata>::~List()    // list is templated and takes generic data
{
    Node* b = first;
    Node* a = NULL; //a stands for "after" (i.e. after b)
    while (b != NULL)
    {
        a = b->next; //move a to node after b
        delete b; //remove b (you know it is not NULL from if)
        b = a; //b "catches up" with a (both point to same place in list)
    }
}
template <class listdata > // template the function
void List< listdata >::printList(ostream& os) const{  // list is templated and can print generic data
	Node* temp = first;
	while (temp != NULL){ // This countinue the loop untill iteratore temp has the value null j
		os << temp->data << " "; // will print the value of temp which is pointing to
		temp = temp->next; // this will advance the pointer temp to the next
	}
	os << endl; // This means goes to the next line
}
template < class listdata> // template the function
void List<listdata>::insertFirst(listdata data) // List is templated and takes in a generic param
{
	Node* N = new Node(data);
    if (length == 0)
    {
        first = last = N;

    }
    else
    {
    	Node* N = new Node (data);
    		first->prev = N; // this will point to the previous node
        N->next = first;
        first = N;
    }
    length++;
}
template <class listdata> // template the function
void List<listdata>:: insertLast(listdata data){ // List is templated and takes in a generic param
	Node* N = new Node(data);
	if (length == 0){
		first = last = N;

	}
	else{

		last->next = N ; // last node is going to point the new node
		N->prev = last; // this will point to previous node
		last = N ;
	}
	length++;

}
template < class listdata> // template the function
void List< listdata >::removeFirst()  //  removeFirst function is templated and can delet generic data
{
    assert (length != 0);  // precondition
    if(length == 1) // when there is only one node, first and last node is the same so they both point to the null
    {
        delete first;
        first = last = NULL;
        length = 0;
    }
    else
    {
        Node* temp = first;
        first = first->next;
        delete temp;
        first->prev = NULL;
        length--;
    }
}
template < class listdata > // template the function
void List<listdata>::removeLast()  // removeLast function is templated and can delet generic data
{
    assert (length != 0);  // precondition: checking if the list is empty stop the program

     if (length == 1) {

    	delete last ;
    	last = first = NULL;
    	length = 0 ;

    } else {
        Node* temp = last;
        last= last->prev;
        delete temp;
        last->next = NULL; //set pointer to point at NULL rather than deallocated memory

        length--;

    }

}

template <class listdata>
bool List<listdata>::isEmpty() const
{
    return length == 0;
}
template < class listdata>
int List<listdata>::getLength() const{
	return length;
}
template <class listdata>  // template the function
listdata List<listdata>::getFirst() const // getFirst function is templated and takes generic data
{
	assert(!isEmpty());  // precondition: checking if the list is empty stop the program
	return first -> data;
}
template < class listdata > // template the funtion
listdata List<listdata>::getLast() const  // getLast function is templated and takes generic data
{
	assert(!isEmpty());	// precondition: checking if the list is empty stop the program
    return last -> data;
}

 // startIterator function
template <class listdata>
void List<listdata>::startIterator(){
	iterator = first;
}
//removeIterator function

template <class listdata>
void List <listdata>:: removeIterator(){  //removes the element currently pointed to by the iterator
	assert(iterator != NULL );		// precondition: iterator not pointing to NULL
	if(iterator == first)		// edge case: if iterator is pointing to the first
		removeFirst();
	else if(iterator == last)	//edge case: if iterator is pointing to the last
		removeLast();
	else{
		iterator->prev->next = iterator->next;
		iterator->next->prev= iterator->prev;
		delete iterator;
		length--;
	}
	iterator = NULL; 	// taking care of dangling pointer
}

// advanceIterator function
template <class listdata>
void List<listdata>::advanceIterator(){
	assert(iterator != NULL); // precondition: iterator is not pointing to null
	iterator = iterator-> next; // advancing iterator by one
}

// reverseIterator function
template <class listdata>
void List<listdata>:: reverseIterator(){
	assert(iterator != NULL);		// precondition: iterator is not pointing to null
	iterator = iterator->prev;		// reversing iterator by one

}

// insertIterator function
template <class listdata>
void List<listdata>::insertIterator(listdata data){  // adds element after the node currently pointed by iterator
	assert(iterator != NULL);	// precondition: iterator not pointing to NULL
	if (iterator == last){
		insertLast(data);		// calling insertLast function
	}
	else{
		Node* N = new Node(data);
		N->next = iterator->next;
		N->prev = iterator;
		iterator->next = N;
		N->next->prev = N;
		length++;


	}
}
// offEnd function
template <class listdata>
bool List<listdata>::offend() const{
	return iterator == NULL; // checking if iterator is equal to NULL

}

// printNumberedList function
template < class listdata>
void List<listdata>::printNumberedList() const{
	assert(length != 0);
	Node* temp = first;
	int counter = 1;
		while (temp != NULL){ // This countinue the loop untill iteratore temp has the value null j

			cout << counter<<"."<<temp->data << endl; // will print the value of temp which is pointing to
			counter++;
			temp = temp->next; // this will advance the pointer temp to the next
		}
		cout << endl; // This means goes to the next line


}

// getIterator function
template <class listdata>
listdata List<listdata>::getIterator() const{
	assert(iterator != NULL);
	return iterator->data;
}
// == function to check if both lists are equal
template <class listdata>
bool List<listdata>::operator==(const List& list)
{
    if(length != list.length)  // checking if their length is not equal
        return false;
    Node* temp1 = first;
    Node* temp2 = list.first;
    while(temp1 != NULL)
    {
        if(temp1->data != temp2->data)
            return false;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return true;
}

template<class listdata>
void List<listdata>::reversePrint() const{
	if( isEmpty()) // this is the base case which prints nothing if the list is empty
		cout << endl;
	reversePrint(first); // this is the wrapper function which calls the helper function
}
template<class listdata>
void List<listdata>::reversePrint(Node* node) const{
	if(node == NULL)
		return;

	reversePrint(node->next);   // this line recursively calling itself until the base condition is meet
	cout<< node->data << " " ;
}

template <class listdata>
bool List< listdata>::isSorted(Node* node) const{
	if(node->next == NULL)
		return true;
	else if (node->data > node->next->data){
		return false;
	}
	return (isSorted(node->next));
}

template <class listdata>
bool List< listdata>::isSorted() const{
	if ( isEmpty())
		return true;

	return (isSorted(first)); 	// this is the wrapper function which call helper function

}

template <class listdata>
int List < listdata>::getIndex() const{
	assert(!offend());
	Node* temp = first;
	int counter = 1 ;
	while(temp != iterator){
		temp = temp->next;
		counter ++;
	}
	return counter;

}
template <class listdata>
void List <listdata>::advanceToIndex(int index){
	assert(!isEmpty());
	assert(index<=length);
	startIterator();
	int counter = 1;
	while(counter < index){
		advanceIterator();
		counter++;
	}

}

template <class listdata>
int List<listdata>::linearSearch(listdata data) const{ 	// this function will search element by element until it finds the element that is assign to it
	assert (length != 0);				// precondition : length is not equal zero
	Node* temp = first;
	for (int i = 0 ; i < length ;  i++){
		if(temp->data == data){			// if the element is found will print the index of element
			return i +1;

		}
		temp= temp->next;
	}
	return -1;							// will print -1 if the element was not found

}

template <class listdata>
int List<listdata>::binarySearch(listdata data) const{		// this is the wrapper function
	assert(length != 0);
	assert(isSorted());
	return binarySearch(0 , getLength() , data);

}

template <class listdata>
int List<listdata>::binarySearch(int low, int high, listdata data) const{ 	// this is the helper function
	if (high < low)
	        return -1;
	  int mid = low + (high-low)/2;
	  Node* temp = first;
	  int counter = 0;
	  while(counter != mid){
		  temp = temp->next;
		  counter++;}
	  if( temp->data == data)
		  return mid;
	  else if( data < temp->data){  	// search for the left half
		  return (binarySearch(data, low , (mid -1)));
	  }
	  else{						// search for the right half
		  return (binarySearch(data, mid+1 ,high));

	  }
}

#endif /* LIST_H_ */
