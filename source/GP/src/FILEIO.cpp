#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "FileIO.h"


using namespace std;

static string infileName = "SavedUsers.txt";
static string outfileName = "SavedUsers.txt";

void FileIO::readFromFile(List<Users> *users, HashTable_I<Users> *interest, HashTable_N<Users> *name,Graph &g)
{

    ifstream in;
    in.open(infileName);
    if (in.fail())
    {
        cout << "Fail to open the file" << endl;
        return;
    }
    while(!in.eof())
    {
        if(in.eof())
            break;
        string firstname,lastname,login,password,city,friends,interests;
        string id;
        int is;
        int fre;


        getline(in, id);
        is= atoi(id.c_str());

        //cout << "ID is " << is << endl;
        getline(in, firstname);
        //cout <<"FIRST name: "<< firstname<<endl;
        getline(in, lastname);
        //cout <<"Last name: "<< lastname<<endl;
        getline(in, login);
        //cout<<"Login: "<<login<<endl;
        getline(in, password);
        //cout<<"password: "<<password<<endl;
        getline(in, city);
        // cout<<"city: "<<city<<endl;

        BST<int> *t = new BST<int>();
        getline(in, friends);
        istringstream ss(friends);
        string f;
        while(getline(ss, f, ','))
        {
            //cout << "Friend: "<<f << '\n';
            fre = atoi(f.c_str());
            g.addEdge(is, fre);
            t->insert(fre);
        }

        List<string> *inter = new List<string>();
        getline(in, interests);
        istringstream iss(interests);
        string i;
        while(getline(iss, i, ','))
        {
            inter->insertLast(i);
        }
       // cout<<endl<<endl;
        if(is != 0)
        {
        	Users u (firstname, lastname,city, login, password, is,t,inter,-10);
        	interest->insert(u);
        	name->insert(u);
        	users->insertLast(u);
        }
       // cout << "------------" << endl;
    }
}

	void FileIO::writeToFile(List<Users> &allUser, Graph &G)
	{
		ofstream outputFile;
		outputFile.open(outfileName);
		allUser.startIterator();
		while(!allUser.offend())
		{
			Users u = allUser.getIterator();
			outputFile << u.get_id() << endl
					<< u.get_first_name() << endl
					<< u.get_last_name() << endl
					<< u.get_login() << endl
					<< u.get_password() << endl
					<< u.get_city() << endl;
			List<int> asf = G.seeFriends(u.get_id());
			asf.startIterator();
			while(!asf.offend())
			{
				outputFile << asf.getIterator();
				asf.advanceIterator();
				if(!asf.offend())
					outputFile << ",";
				else
					outputFile << endl;
			}
			List<string> interests = u.get_listofinterest();
			interests.startIterator();
			while(!interests.offend())
			{
				outputFile << interests.getIterator();
				interests.advanceIterator();
				if(!interests.offend())
					outputFile << ",";
				else
					outputFile << endl;
			}
					//<< u.get_listoffriends() << endl
			allUser.advanceIterator();
		}
		outputFile.close();
	}


