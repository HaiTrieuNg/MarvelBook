#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ctype.h>

#include <algorithm>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "Users.h"
#include "BST.h"
#include "List.h"
#include "Hash_name.h"
#include "Hash_interest.h"
#include "FileIO.h"


using namespace std;

void printMenu(Users& currentUser)
{

	cout << endl<<endl;

	cout<<"*****************************************************************"<<endl;
	cout<<endl<<"MENU"<<endl<<endl;
	cout << "1. View My Friends " << endl;
	cout << "2. Search by name" << endl;
	cout << "3. Search by interest" << endl;
	cout << "4. Get Friend Recommendation" << endl;
    cout << "5. Quit" << endl;
    cout<< "6. View my profile "<<endl;
 	cout << endl;
	cout << "Enter your choice: ";
}

void interactWithUser(Users&currentUser,List<Users>&allUser,HashTable_I<Users>& HI,HashTable_N<Users>& HN, Graph &G)
{

    string choice;
	bool quit = false;
	while (! quit)
    {
		printMenu(currentUser);

		cin >> choice;
		while (!isdigit(choice[0]))
        {
			cout << "\n\nPlease enter numbers not letters\n" << endl;
			printMenu(currentUser);
			cin >> choice;
		}
		int num = stoi(choice);
		while (!(0 < num) || !(num < 7))
        {
			cout << "\n\nInvalid input.\n" << endl;
			printMenu(currentUser);
			cin >> num;
		}
		if (num == 5)
        {
			FileIO::writeToFile(allUser, G);
			break;
		}


		if(num ==1)
            {
                int choi1;
                cout << "1. View all friends" << endl;
                cout << "2. View a friend's profile " << endl;
                cout << "3. Remove a friend" << endl << endl;
                cout << "Enter your choice " << endl;
                cin >> choi1;
                while (cin.fail() || choi1 > 3 || choi1 < 1)
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << endl << endl;
                    cout << " Please enter correct input" << endl;
                    cout << "1. View all friends" << endl;
                    cout << "2. View a friend's profile " << endl;
                    cout << "3. Remove a friend" << endl << endl;

                    cin >> choi1;

                }
                cin.ignore();
                List<int> asf = G.seeFriends(currentUser.get_id());

                if(choi1 == 1)
                {
                while(!asf.isEmpty())
                {
                    int x = asf.getFirst();
                    asf.removeFirst();
                    allUser.startIterator();
                    for(int i=1;i<x;i++)
                    {
                        allUser.advanceIterator();
                    }
                    Users viewFriend = allUser.getIterator();
cout << "*** Your Friends ***" << endl << endl;

                    cout <<viewFriend.get_id() << " " <<   viewFriend.get_first_name() << " " << viewFriend.get_last_name() << endl;
                }
                }
                else if (choi1 == 2)
                {
                    cout << "Enter the ID of your friend: ";
                    int ch;
                    cin >> ch;
                    allUser.startIterator();
                    for(int l=0;l<ch;l++)
                    {
                        allUser.advanceIterator();
                    }
                    Users viewFriend1 = allUser.getIterator();
                    cout << "First Name: " << viewFriend1.get_first_name() << endl;
                    cout << "Last Name: " << viewFriend1.get_last_name() << endl;
                    cout << "City: " << viewFriend1.get_city() << endl;
                }
                else if(choi1==3)
                {
                    cout << "Enter the ID you want to remove: ";
                        int r;
                        cin >> r;
                       G.removeFriend(currentUser.get_id(), r);
                    allUser.startIterator();
                    for (int k=1; k<r; k++)
                    {
                        allUser.advanceIterator();
                    }
                    Users UserRemove = allUser.getIterator();
                    cout << UserRemove.get_first_name() << " removed!" << endl;
                }
		}
		else if (num == 2)
        {
			string fn, ln;
			cout << "Enter the first name of the User: ";
			cin >> fn;
			cout << "Enter the last name of the User: ";
			cin >> ln;
			transform(fn.begin(), fn.end(), fn.begin(), ::tolower);
			transform(ln.begin(), ln.end(), ln.begin(), ::tolower);

			int index = HN.hash(fn + ln);

			if (HN.countBucket(index) == 0||HN.countBucket(index) == -1)
            {
				cout << fn << " is not a User of Marvel Book" << endl;
			}
            else
            {
				List<Users> usersWithName;
				cout << endl << "This's a list of users whose name is " << fn
					 << " " << ln << endl << endl;
				List<Users>& bucket = (List<Users>&)HN.getBucket(index);
				bucket.startIterator();
				int count = 1;
				while (! bucket.offend())
                {
					Users user = (Users)bucket.getIterator();
					// check actual lowercase names are correct to avoid hash collisions
					string user_fn = user.get_first_name();
					string user_ln = user.get_last_name();
					transform(user_fn.begin(), user_fn.end(), user_fn.begin(), ::tolower);
					transform(user_ln.begin(), user_ln.end(), user_ln.begin(), ::tolower);


					if (fn == user_fn && ln == user_ln)
                    {
						cout << count << "." << endl;
						cout <<"First name: "<< user.get_first_name() << endl;
						cout <<"Last name: "<< user.get_last_name() << endl;
						cout <<"Login ID: " <<user.get_login() << endl;
						cout <<"City: "<< user.get_city() << endl<<endl;
						usersWithName.insertLast(user);
						count ++;
					}
					bucket.advanceIterator();
				}
				if (! usersWithName.isEmpty())
                {
					char choice;

					cout << "Would you like to add a user from the searched list? Enter Y if you do: ";

					cin >> choice;
					if (choice == 'Y' || choice == 'y')
                    {
						cout << endl << "Choose number of user listed to add: ";
						int numU;

						cin >> numU;
						int index = 0;
						Users userToAdd;
						usersWithName.startIterator();
						while (index < numU && ! usersWithName.offend())
                        {
							Users user = usersWithName.getIterator();
							if (index == numU - 1)
                            {
								userToAdd = user;
								break;
							}
							usersWithName.advanceIterator();
						}

						cout <<endl<< "The user to be added is: " << endl << endl;
						cout <<"First name: "<< userToAdd.get_first_name() << endl;
						cout <<"Last name: "<< userToAdd.get_last_name() << endl;
						cout <<"Login ID: " <<userToAdd.get_login() << endl;
						cout <<"City: "<< userToAdd.get_city() << endl<<endl;
						// add user to currentUsers' friends
                        G.addEdge1(currentUser.get_id(), userToAdd.get_id());
                       // G.printGraph(cout);
						currentUser.add_bst(userToAdd);

						cout << endl << userToAdd.get_first_name()
						     << " is added to your friend list, " << currentUser.get_first_name()
							 << "." << endl<<endl;
					}
                    else
                    {
						cout << endl;
					}
				}
			}

		}
		else if(num==3)
        { // search by interest
			const int interest_count = 17;
			string possibleInterests[interest_count] =
            {
				"Technology",
				"Money",
				"Fighting Evil",
				"Working out",
				"Old movies",
				"Studies",
				"Combat",
				"Biology",
				"Street fighting",
				"Hammer",
				"Stealing",
				"Tricks",
				"Physics",
				"Photography",
				"Pranks",
				"Killing",
				"Fashion Design"
			};

			cout << "*** All Possible Marvel Book Interests ***" << endl;
			for (int i = 0; i < interest_count; i++)
            {
				cout << "  " << i + 1 << ". " << possibleInterests[i] << endl;
			}
			cout << "******************************************" << endl;

			int num;
			cout << "Please choose an interest to search for (1 -- " << interest_count << "): ";
			cin >> num;
			while (cin.fail() || num <= 0 || num > 17)
            {
                cin.clear();
                cin.ignore(1000, '\n');
				cout << "Invalid input.  Please enter a number (1 -- " << interest_count << "): ";
				cin >> num;
			}
			string searchInterest = possibleInterests[num - 1];
			cout << "Searching for users with " << searchInterest << " as an interest." << endl;
			int inde = HI.hash(searchInterest);
			if (HI.countBucket(inde) == 0)
            {
				cout << "No User matched" << endl << endl;
			}
            else
            {
				cout << endl
				     << "This is a list of users with interest as searched: "
					 << endl << endl;

				List<Users>& bucket = HI.getBucket(inde);
				List<Users> usersWithInterest;
				int count = 1;
				bucket.startIterator();
				while (! bucket.offend())
                {
					Users        user            = bucket.getIterator();
					bool         userHasInterest = false;
					List<string> userInterests   = user.get_listofinterest();
					userInterests.startIterator();
					while (! userInterests.offend())
                    {
						string userInterest = userInterests.getIterator();
						if (userInterest == searchInterest)
                        {
							userHasInterest = true;
							break;
						}
						userInterests.advanceIterator();
					}
					if (userHasInterest)
                    {
						cout << count << "." << endl;
						cout <<"First name: "<< user.get_first_name() << endl;
						cout <<"Last name: "<< user.get_last_name() << endl;
						cout <<"Login ID: " <<user.get_login() << endl;
						cout <<"City: "<< user.get_city() << endl<<endl;

						usersWithInterest.insertLast(user);
						count ++;
					}
					bucket.advanceIterator();
				}

				if (! usersWithInterest.isEmpty())
                {
					char choice;
					cout << endl
							<< "Would you like to add a user from the searched list? Enter Y if you do : ";

					cin >> choice;
					if (choice == 'Y' || choice == 'y')
                    {
						cout << endl << "Chose number of user listed to add: ";
						int numU;
						cin >> numU;

						Users userToAdd;
						bool foundUser = false;
						int count = 1;
						usersWithInterest.startIterator();
						while (! usersWithInterest.offend())
                        {
							Users user = usersWithInterest.getIterator();
							if (count == numU) {
								userToAdd = user;
								foundUser = true;
								break;
							}
							count ++;
							usersWithInterest.advanceIterator();
						}
						if (! foundUser)
                        {
							cout << "Could not find user" << endl;
						}
                        else
                        {
							cout <<endl<< "The user to be added is: " << endl;
							cout <<"First name: "<< userToAdd.get_first_name() << endl;
							cout <<"Last name: "<< userToAdd.get_last_name() << endl;
							cout <<"Login ID: " <<userToAdd.get_login() << endl;
							cout <<"City: "<< userToAdd.get_city() << endl<<endl;
							// add user to currentUsers' friends
							currentUser.add_bst(userToAdd);
                            G.addEdge(currentUser.get_id(), userToAdd.get_id());
                           // G.printGraph(cout);


							cout << endl << userToAdd.get_first_name()
							     << " is added to your friend list, " << currentUser.get_first_name()
								 << "." << endl<<endl;
						}
					}
				}
			}

		}
                else if(num == 4)
                {
                     List<int> Table[15];
            List<Users> ud;
            cout << "Friend recommendation: " << endl;
            //cout << "FFFfffffffffff"<< endl;
            List<int> rec = G.BFS(currentUser.get_id());
            if(rec.isEmpty())
                cout << "**************************" << endl;
            cout<< "Friend recommendation not available" << endl;


            rec.startIterator();
            while(!rec.offend())
            {
                int p =0;
                cout << "Hh";
                int x = rec.getIterator();
                cout << "FFF";
                rec.advanceIterator();
                allUser.startIterator();
                for(int i =1; i < x; i++)
                {
                    allUser.advanceIterator();
                }
                Users recUser = allUser.getIterator();


                ud.insertLast(recUser);
                List<string> rec = recUser.get_listofinterest();
                List<string> cur = currentUser.get_listofinterest();
                cur.startIterator();
                while (!cur.offend())
                {
                    string q = cur.getIterator();

                    cur.advanceIterator();
                    if(rec.linearSearch(q)!= -1)
                        p++;
                }

                int rank;
                rank =  G.getDistance(x)-p;
                cout << "Adding " << x << "at index " << rank << endl;
                //recUser.set_rank(rank);

                cout << "Matches are " << p << endl;
                cout << "The rank is " << rank << endl;
                if(rank == -1)
                {
                    Table[0].insertLast(x);
                }
                else
                {
                 Table[rank].insertFirst(x);

                }

            }

            cout << endl << endl;
            cout << "---------------------------------------------------" << endl << endl;
            for(int i = 0 ;i<4;i++)
            {
                Table[i].startIterator();
                while(!Table[i].offend())
                {
                    int l = Table[i].getIterator();
                                           allUser.startIterator();
                                        for(int i =1; i < l; i++)
                                           {
                                             allUser.advanceIterator();
                                        }
                                          Users recUser1 = allUser.getIterator();
                                          Table[i].advanceIterator();
                    cout << "Stores at index" << i << endl;
                    cout << recUser1.get_first_name() << " " << recUser1.get_last_name() << " and ID is " << recUser1.get_id() << endl;
                    cout << "Would u like to add (y/n): ";
                    string re;
                    cin >> re;
                    if (re == "Y" || re == "y")
                    {
                        G.addEdge1(currentUser.get_id(), recUser1.get_id());
                        cout << recUser1.get_first_name() << " added!" << endl;
                    }
                }


            }


                }



		else if (num == 5)
        {
			FileIO::writeToFile(allUser, G);
			quit = true;
			break;
		}

		else if (num==6)
		{
			cout<<endl<<"This's your profile:"<<endl<<currentUser;

		}
}
    cout << "Bye " << currentUser.get_first_name() << "!" << endl;
}
int main()
{
	HashTable_I<Users>* HI  = new HashTable_I<Users>();
	HashTable_N<Users>* HN  = new HashTable_N<Users>();
	List<Users>*  allUser   = new List<Users>();
    Graph G(15);

	FileIO::readFromFile(allUser, HI, HN, G);
   // G.printGraph(cout);
    int id;
    string login, pass;

	allUser->startIterator();
    cout <<endl<< "Enter your ID: ";
    cin >> id;
    while (cin.fail() || id >15||id<=0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << endl << endl;
        cout << " Please enter correct id" << endl;

        cin >> id;

    }

    for(int i =1; i < id; i++)
    {
        allUser->advanceIterator();
    }
	Users currentUser = allUser->getIterator(); // assume current user is first for testing for now.
   do
   {
    cout << "Enter you password: ";
    cin >> pass;
   }
    while(pass != currentUser.get_password());
    if(pass == currentUser.get_password() )
    {
    	cout <<endl<< "Welcome to MarvelBook, " << currentUser.get_first_name() << "!" << endl<<endl;



    interactWithUser(currentUser, *allUser, *HI, *HN, G);
    }
    else
    {
        cout << " Password didn't match " << endl;
    }


	return 0;
}







