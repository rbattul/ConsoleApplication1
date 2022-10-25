// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <set>
#include <map>
#include <functional>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <utility>
#include "ConsoleApplication1.h"

using namespace std;

bool addToHashTable(struct llList*, const string &, const string&);
void findInHashTable(const string&);

struct llList
{
	string str;
	llList *next;
};

std::map<string, struct llList*> HashObj;

void findInHashTable(const string& ipString)
{
	string hashKey = ipString;
	std::sort(hashKey.begin(), hashKey.end());

	try
	{
		struct llList* ptr = HashObj.at(hashKey);

		if (ptr == nullptr)
		{
			cout << endl << "Hash Bucket " << hashKey << " is Empty for ipString " << ipString;
			cout << endl << "Adding the same to bucket";
			addToHashTable(ptr, ipString, hashKey);
			return;
		}

		short count = 0;
		do
		{
			if (0 == ptr->str.compare(ipString))
			{
				cout << endl << "Found Input string at Key : " << hashKey << " at position : " << ++count;
				break;
			}
		} while (ptr->next != nullptr);

		if (ptr->next == nullptr)
		{
			cout << endl << "Not Found Input String at Key: " << hashKey;
			cout << endl << "Adding the same to bucket";
			addToHashTable(ptr, ipString, hashKey);
		}
	}
	catch (exception e)
	{
		cout << endl << "Exception occurred while finding input string " << ipString << " : " << e.what();
	}

}

bool addToHashTable(struct llList* header, const string &ipString,const string& hashKey)
{
	struct llList obj;
	obj.str = ipString;
	obj.next = nullptr;

	if (nullptr == header)
	{
		HashObj[hashKey] = &obj;
		return true;
	}

	struct llList *temp = header;

	do
	{
		temp = temp->next;
	} while (temp->next != nullptr);

	temp->next = &obj;

	return true;
}

int main()
{
		string read, write;
		cout << "Provide Input and out file: ";

		struct llList *hashtblHeader = nullptr;

		cin >> read >> write;

		ifstream ifs{ read };
		ofstream ofs{ write };

		istream_iterator<string> ii{ ifs};
		istream_iterator<string> eos{}; //inpupt sentinel

		ostream_iterator<string> oi{ ofs,"\n" };

		set <string> s{ ii,eos };

		set <string> hashKeySet;

		for (auto ite = s.begin(); ite != s.end(); ++ite)
		{
			cout << endl << " Before Sorting : " << *ite;
			string stri = *ite;
			std::sort(stri.begin(), stri.end());
			// s.erase(ite);
			hashKeySet.insert(stri);

			// HashObj.insert(std::pair<string, struct llList*>(stri, NULL));
			HashObj[stri] = nullptr;
		}

		copy(hashKeySet.begin(), hashKeySet.end(), oi);

		short ch = -1;

		do
		{
			cout << endl << "Enter choice 1 for insert and 2 for finding string ";
			cin >> ch;

			switch (ch)
			{
			case 1:
			{
				string re;
				cout << endl << "Enter the string from dictionary: ";
				cin >> re;

				struct llList *ptr = nullptr;

				try
				{
					string hashKey = re;
					std::sort(hashKey.begin(), hashKey.end());
					ptr = HashObj.at(hashKey);
					if (addToHashTable(ptr, re, hashKey))
					{
						cout << endl << "Added input string : " << re << " To HashTable at Key " << hashKey;
					}
				}
				catch (exception e)
				{
					cout << endl << " Exception Occurred for input " << re << " : " << e.what();
				}
			}
			break;

			case 2:
			{
				string re;
				cout << endl << "Enter the string to find in dictionary: ";
				cin >> re;

				findInHashTable(re);

			}
			break;

			case 3:
			{
				exit(0);
			}
			break;
			}
		} while (ch != 3);

		return 0;
}

