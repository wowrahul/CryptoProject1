#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

typedef map<char,int> DefFrequencyMap;
typedef map<int, char> ReverseValueMap;
DefFrequencyMap fMap;
DefFrequencyMap CharValueMap;
ReverseValueMap ReverseCharValueMap;
// Creates a default frequency map for A-Z and space. The initial values are set to 0.
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


// Creates a map for values of alphabet. A-1,B-2,......Z-26,<SPACE>-27.
void SetDefaultValueMapping()
{
	string defaultString = "abcdefghijklmnopqrstuvwxyz ";
	
	for(int i = 0 ; i < defaultString.length() ; i++ )
	{
		char ch = defaultString.at(i);
		CharValueMap.insert( make_pair(ch,i + 1) );//add an entry
		ReverseCharValueMap.insert(make_pair(i + 1,ch));
	}
} // SetDefaultValueMapping


// Creates a frequency map for any string.
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



// Derives a key by substracting first t characters of the cipher from the provided plain text
void GetKey(string &plainText,string &cipherText, vector<int>& key, int t)
{
	int k;
	for (unsigned i =0;i < cipherText.length();i++)
	{
		if ( i == 0)
		{
			k = CharValueMap[cipherText[i]] - CharValueMap[plainText[i]] ;
			//cout << "K = " << k << " shift = " << k << " prev = " << CharValueMap[cipherText[i]] << endl;
		}
		
		
		else
		{	
			int shift = CharValueMap[cipherText[i]] - CharValueMap[plainText[i]];
			if (shift < 0)
				shift = shift + 27;
			k = shift - CharValueMap[cipherText[i - 1]];
			//cout << "K = " << k << " shift = " << shift << " prev = " << CharValueMap[cipherText[i -1]] << endl;
		}
			
		if (k < 0)
			key.push_back(k + 27);
		else
			key.push_back(k);
			
		
	}
} // GetKey

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
	
	//SetDefaultFMap();
	SetDefaultValueMapping();
	
	ifstream myfile("Dictionary1.txt");
	
	vector <int> key;
	string line;
	if(myfile.is_open())
	{
		while(getline(myfile,line))
		{	
			GetKey(line,cipherText,key,t); 
			//cout << key.size() << endl;
			//for (unsigned i=0; i< key.size(); i++)
				//cout << key.at(i);
	
			std::sort (key.begin(), key.begin() + key.size()); 
			std::vector<int>::iterator it;
			it = unique (key.begin(), key.end());   
                                                         
			key.resize(distance(key.begin(),it) ); 
			//cout << endl;
			//std::ostream_iterator< int > output( cout, " " );
			//std::copy( key.begin(), it, output );

			if (key.size() <= t)
			{
				cout << "Plain text found:" <<endl << line;
				break;
			}
			else
				key.clear();
		}
		myfile.close();
	}
	return 0;
} // main

