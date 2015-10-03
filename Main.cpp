#include <iostream>
#include <string>
#include <map>
using namespace std;

typedef map<char,int> DefFrequencyMap;
DefFrequencyMap fMap;

void SetDefaultFMap() 
{
	string defaultString = " abcdefghijklmnopqrstuvwxyz";
	DefFrequencyMap fMapTemp;
	for(int i = 0 ; i < defaultString.length() ; i++ )
	{
		char ch = defaultString.at(i);
		fMap.insert( make_pair(ch,0) );//add an entry
	}
	
	
} // SetDefaultMap


void CreateFrequencyMap(string str)
{
	
	//string str ("Test string");
	map<char,int>::iterator it;
	for(int i = 0 ; i < str.length() ; i++ )
	{
		char ch = str.at(i);
		it = fMap.find(ch); //find the character in the map
		if( it == fMap.end() ) //if not present in the map
		{
			fMap.insert( make_pair(ch,1) );//add an entry
		}
		else
		{
			it->second++; //else increment the frequency
		}
	}
	
} // CreateFrequencyMap


int BreakCipher(int &t,string &cipherText)
{
	//cout << "You entered " << t << " and cipher " << cipherText;
} // BreakCipher

int main()
{
	int t;
	string cipherText;
	string t_string;
	cout << "Enter the number of key symbols \n";
	getline(cin,t_string);
	t = atoi(t_string.c_str());
	cout << "Enter the cipher text \n";
	getline(cin,cipherText);
	//breakCipher(t,cipherText);
	SetDefaultFMap();

	for (unsigned i = 0; i < cipherText.length(); i += t) 
	{
		
		CreateFrequencyMap(cipherText.substr(i, t));
	}
	
	for ( const auto &p : fMap )
	{
		std::cout << p.first << '\t' << p.second << std::endl;
	} 
	
	return 0;
} // main

