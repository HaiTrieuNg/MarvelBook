#include <iostream>
#include <iomanip>
#include "List.h"
#include "Users.h"

#ifndef HASH_INTEREST_H_
#define HASH_INTEREST_H_

using namespace std;

template<class hashdata>
class HashTable_I {
public:
    /**Constructors*/

    HashTable_I(){}
    //constructor

    ~HashTable_I(){}
    //destructor


    /**Access Functions*/

    int hash(string key) const;


    int countBucket(int index) const;

    List<hashdata>& getBucket(int index);

    int search(hashdata b) const;

    void insert(hashdata b);


    void remove(hashdata b);

    void printBucket(ostream& out, int index) const;


    hashdata UserToAdd(int index, int num);

private:
    static const int SIZE = 60;
    List<hashdata> Table[SIZE];
};


template<class hashdata>
int HashTable_I<hashdata>::hash(string key) const{
	int sum = 0;
	int size=key.size();
	for(int i = 0; i < size;i++)
	{
		sum += (int)key[i];
	}
	return (sum%SIZE);
}
template<class hashdata>
int HashTable_I<hashdata>::search(hashdata b) const{
	int index = hash(b.get_listofinterest());
	return Table[index].linearSearch(b);
}



template<class hashdata>
void HashTable_I<hashdata>::insert(hashdata b){
	List<string> interests(b.get_listofinterest()); //make a copy of list of interest
	interests.startIterator(); //start on the list of interest
	while(! interests.offend()) {
		string interest = interests.getIterator();
		int index = hash(interest);
		Table[index].insertLast(b);
		interests.advanceIterator();
	}
}

template<class hashdata>
void HashTable_I<hashdata>::remove(hashdata b){
	int index = hash(b.get_listofinterest());
	 int result = Table[index].linearSearch(b);
	 Table[index].advanceToIndex(result);
	 Table[index].removeIterator();
}

template<class hashdata>
int HashTable_I<hashdata>::countBucket(int index) const{
	return Table[index].getLength();
}

template<class hashdata>
List<hashdata>& HashTable_I<hashdata>::getBucket(int index) {
	return Table[index];
}

template<class hashdata>
void HashTable_I<hashdata>::printBucket(ostream& out, int index) const{
	assert(0 <= index && index < SIZE);
	Table[index].printList(out);

}

template<class hashdata>
hashdata HashTable_I<hashdata>::UserToAdd(int index, int num)
{
	Table[index].startIterator();
	for(int i=1;i<num; i++)
	{
	Table[index].advanceIterator();
	}
	return Table[index].getIterator();
}


#endif /* HASH_INTEREST_H_ */

 
