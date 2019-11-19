#ifndef FILEIO_H_
#define FILEIO_H_

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "BST.h"
#include "Hash_interest.h"
#include "Hash_name.h"
#include "List.h"
#include "Users.h"
#include "Graph.h"

class FileIO
{

public:
	static void readFromFile(List<Users> *users, HashTable_I<Users> *interest, HashTable_N<Users> *name, Graph &k);
	static void writeToFile(List<Users>&allUser, Graph &G);

};

#endif /* FILEIO_H_ */
