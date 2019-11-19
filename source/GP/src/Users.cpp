#include "Users.h"
#include <iostream>
#include <iomanip>

Users::Users(){}
Users::Users(const Users &users)
{
    firstname = users.firstname;
    lastname = users.lastname;
    city = users.city;
    password = users.password;
    login = users.login;
    friends = users.friends;
    interests = users.interests;
    ido = users.ido;
    rank =users.rank;
}

Users::Users(string fn, string ln, string c, string log, string pw, int id, BST<int> *f, List<string> *i,int ran)
{
    firstname = fn;
    lastname = ln;
    city = c;
    password = pw;
    login = log;
    ido = id;
    friends = f;
    interests = i;
    rank = ran;
}

/**Access Functions*/


string Users::get_first_name()
{
    return firstname;
}
int Users::get_rank()
{
    return rank;
}

string Users::get_last_name()
{
    return lastname;
}

string Users::get_city()
{
    return city;
}

string Users::get_login()
{
    return login;
}

string Users::get_password()
{
    return password;
}
int Users::get_id()
{
    return ido;
}


/**Manipulation Procedures*/

void Users::set_rank(int r)
{
    rank =r;
}
void Users::set_id(int id)
{
    ido = id;
}

void Users::set_first_name(string fn)
{
    firstname = fn;
}

void Users::set_last_name(string ln)
{
    lastname = ln;
}

void Users::set_city(string c)
{
    city = c;
}

void Users::set_login(string log)
{
    login = log;
}
void Users::set_password(string pw)
{
    password = pw ;
}

void Users::sort(List<int> d)
{
    d.startIterator();

}
/**Additional Functions*/


bool Users::operator==(const Users& users)
{
    return (firstname== users.firstname && lastname == users.lastname);
}
ostream& operator<<(ostream& os, const Users& users)
{
    os <<  users.ido << endl;
    os << users.firstname<< endl;
    os << users.lastname << endl;
    os << users.login<< endl;
    os << users.password << endl;
    os <<  users.city << endl;

    users.friends->inOrderPrint(os);
    os << endl; // added by nina

    users.interests->printList(os);

    return os;

}
bool Users::operator>(const Users& users)
{
    bool status;
    if(firstname[0] > users.firstname[0])
        status = true;
    else if (firstname == users.firstname && lastname[0] > users.lastname[0])
        status = true;
    else
        status = false;
    return status;
}

bool Users::operator <(const Users& users)
{
    bool status;
    if(firstname[0] < users.firstname[0])
        status = true;
    else if(firstname == users.firstname && lastname[0] < users.lastname[0])
        status = true;
    else
        status = false;
    return status;
}

void Users::add_bst(Users user)
{
    friends->insert(user.get_id());
}

void Users::add_interest(string interest)
{
    //interests->insertLast(interest);
}

bool Users::searchBst(Users user)
{
    if(friends->search(user.get_id()))
        ;
    return true;

    return false;
}

void Users::remove_bst(Users user)
{
    //friends->remove(user);
}

List<string> Users::get_listofinterest()
{
    List<string> listofinterest;
    interests->startIterator();
    while (! interests->offend())
    {
        string interest = interests->getIterator();
        listofinterest.insertLast(interest);
        interests->advanceIterator();
    }
    return listofinterest;
}

BST<int> Users::get_listoffriends()
{
    BST<int> listfriends(*friends);
    return listfriends;

}
