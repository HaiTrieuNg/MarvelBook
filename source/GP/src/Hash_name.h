#include <algorithm>
#include <string>
#include <iostream>
#include <iomanip>

#include "List.h"
#include "Users.h"

#ifndef HASH_NAME_H_
#define HASH_NAME_H_

using namespace std;

template<class hashdata>
class HashTable_N {
public:
    /**Constructors*/

    HashTable_N(){}
    //constructor

    ~HashTable_N(){}
    //destructor


    /**Access Functions*/

    int hash(string key) const;


    int countBucket(int index) const;


    int search(hashdata b) const;

    void insert(hashdata b);


    void remove(hashdata b);

    void printBucket(ostream& out, int index) const;

    List<hashdata> const& getBucket(int index) const;

    hashdata UserToAdd(int index,int num);

private:
    static const int SIZE = 60;
    List<hashdata> Table[SIZE];
};

template<class hashdata>
int HashTable_N<hashdata>::hash(string key) const{
	transform(key.begin(), key.end(), key.begin(), ::tolower);
	int sum = 0;
	int size=key.size();
	for(int i = 0; i < size;i++){
		sum += (int)key[i];
	}
	return (sum%SIZE);
}
template<class hashdata>
int HashTable_N<hashdata>::search(hashdata b) const{
	int index = hash(b.get_first_name()+b.get_last_name());
	return Table[index].linearSearch(b);
}

template<class hashdata>
void HashTable_N<hashdata>::insert(hashdata b){
	int index = hash(b.get_first_name()+b.get_last_name());
	Table[index].insertLast(b);
}

template<class hashdata>
void HashTable_N<hashdata>::remove(hashdata b){
	int index = hash(b.get_first_name()+b.get_last_name());
	int result = Table[index].linearSearch(b);
	Table[index].advanceToIndex(result);
	Table[index].removeIterator();
}

template<class hashdata>
int HashTable_N<hashdata>::countBucket(int index) const{
	return Table[index].getLength();
}

template<class hashdata>
void HashTable_N<hashdata>::printBucket(ostream& out, int index) const{
	assert(0 <= index && index < SIZE);
	//List<Users>* userss = (List<Users>*)&(Table[index]); // get pointer to list of "Users" objects.
	//userss->startIterator();
	//int count = 1;
	//while (! Table[index].offend()) {
	//	hashdata* d = &(userss->getIterator());
	//	out << count << ". " << *d << endl;
	//	count ++;
	//	userss->advanceIterator();
	//}
	//Table[index].printNumberedList(out);
	Table[index].printNumberedList();
}

template<class hashdata>
List<hashdata> const& HashTable_N<hashdata>::getBucket(int index) const{
	assert(0 <= index && index < SIZE);
	return Table[index];
}

template<class hashdata>
hashdata HashTable_N<hashdata>:: UserToAdd(int index,int num)
{
	Table[index].startIterator();
	for(int i=1;i<num; i++)
	{
		Table[index].advanceIterator();
	}
	return Table[index].getIterator();
}

#endif /* HASH_NAME_H_ */
