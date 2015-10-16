// Project 1 - Modern Cryptography.
// Authors : Rahul Joshi, Ashish Tyagi and Shailesh Sayarmal Chaudhary.


#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <set>

using namespace std;

// Variable declaration

typedef map<char,int> DefFrequencyMap;
typedef map<int, char> ReverseValueMap;
DefFrequencyMap fMap;
DefFrequencyMap CharValueMap;
ReverseValueMap ReverseCharValueMap;
vector<string> finalShortList;
vector<string> shortList;
vector <string> shortList1;
vector<string> dictionary2;
vector<string> stringCombinationsTwoWords;



// Creates a map for values of alphabet. A-1,B-2,......Z-26,<SPACE>-0.
void SetDefaultValueMapping()
{
	string defaultString = " abcdefghijklmnopqrstuvwxyz";
	
	for(int i = 0 ; i < defaultString.length() ; i++ )
	{
		char ch = defaultString.at(i);
		CharValueMap.insert( make_pair(ch,i) );//add an entry
		ReverseCharValueMap.insert(make_pair(i,ch));
	}
	
} // SetDefaultValueMapping


// Derives a key by substracting first t characters of the cipher from the provided plain text
void GetKey(string &plainText,string &cipherText, vector<int>& key, int t)
{
	//cout << plainText << endl;
	int k;
	for (unsigned i =0;i < plainText.length();i++)
	{
		if ( i == 0)
		{
			k = CharValueMap[cipherText[i]] - CharValueMap[plainText[i]] ;
			//cout << "K = " << k << " shift = " << k << " prev = " << "NA" << endl;
		}
		
		
		else
		{	
			int shift = CharValueMap[cipherText[i]] - CharValueMap[plainText[i]];
			//cout << "Shift before edit " << shift << " ";
			if (shift < 0)
				shift = shift + 27;
			k = shift - CharValueMap[cipherText[i - 1]];
			//cout << "K = " << k << " shift = " << shift << " prev = " << CharValueMap[cipherText[i -1]] ;
		}
			
		if (k < 0)
		{
			key.push_back(k + 27);
			//cout << " " << "Final K after adding= " << k + 27 << endl;
		}
		else{
			key.push_back(k);
			//cout << " " << "Final K= " << k  << endl;
		}
			
		
	}
} // GetKey


// Derives key for plaintext from dictionary 2. 
// This is called several times for various combinations.
// Returns true if the key set size is <= t.
bool GetKeyCopy(string &plainText,string &cipherText, int t)
{
	
	int k;
	 std::vector<int> v;
	for (unsigned i =0;i < plainText.length();i++)
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
			{
				//cout << k + 27 << " ";
			v.push_back(k + 27);
			}
		else
			{
				//cout << k <<  " ";
				v.push_back(k);
				
			}
	}
	std::sort(v.begin(), v.end()); 
	auto last = std::unique(v.begin(), v.end());
	v.erase(last, v.end());
	
	if (v.size() <= t)
	{
		//cout << plainText << endl;
		v.clear();
		//for (const auto& i : v)
			//std::cout << i << " ";
		return true;
	
	}
	
	v.clear();
	return false;
	
} // GetKeyCopy


// Creates combinations for shortlisted plaintexts.
void permute (vector<string> & toBeCleared, vector<string> & toBeUsed,vector<string> & dictionary2,vector<string> & stringCombinationsTwoWords,string cipherText,int t)
{
	
	for (unsigned i=0; i< toBeCleared.size(); i++)
			{
				for (unsigned int k =0;k< dictionary2.size();k++)
					{
						string str = toBeCleared[i] + " " + dictionary2[k];
						//cout << str << " " << str.length() << endl;
						if (str.length() >= 100)
								{
									//finalShortList.push_back(str);
								str = 	str.substr(0,100);
								}
						bool result = GetKeyCopy(str,cipherText,t);
						if (result)
							{
								toBeUsed.push_back(str);
								if (str.length() >= 100)
								{
									finalShortList.push_back(str);
									//str.substr(0,100);
								}	
							}
					
					}
			}
		
	
} // Permute


// MAIN METHOD : Start Here.
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
	
	SetDefaultValueMapping();
	
	
	// Load Dictionary 1
	ifstream myfile("Dictionary1.txt");
	
	vector <int> key;
	string line;
	bool found = false;
	if(myfile.is_open())
	{
		while(getline(myfile,line))
		{	
			GetKey(line,cipherText,key,t); 
			
			std::sort (key.begin(), key.begin() + key.size()); 
			std::vector<int>::iterator it;
			it = unique (key.begin(), key.end());   
                                                         
			key.resize(distance(key.begin(),it) ); 
			
			if (key.size() <= t)
			{
				cout << "Plain text found in Dictionary 1:" <<endl << line << endl;
				found = true;
			}
			else
				key.clear();
		}
		myfile.close();
		if (found)
			exit(0);
	} // End of Dictionary 1 search
	
		// Dictionary 2 search starts here
		
		cout << endl << "Nothing found in dictionary 1...Searching in dictionary 2 now..." << endl;
		
		// Load Dictionay 2
		ifstream myfile2("Dictionary2.txt");
		if(myfile2.is_open())
		{
			while(getline(myfile2,line))
			{	
			
			dictionary2.push_back(line);
			}
			myfile2.close();
		}
	
		
		// Create three word combinations for words from Dictionary 2.
		for (unsigned i=0; i< dictionary2.size(); i++)
			for (unsigned j=0; j< dictionary2.size(); j++)
				for (unsigned k=0; k< dictionary2.size();k++)
						stringCombinationsTwoWords.push_back(dictionary2[i] + " " + dictionary2[j] + " " + dictionary2[k]);
		
		
		// Make first pass to find out potential plaint texts by checking key set.
		
		for (unsigned int i =0;i<stringCombinationsTwoWords.size();i++)
		{
			bool result = GetKeyCopy(stringCombinationsTwoWords[i],cipherText,t);
			if (result)
				shortList.push_back(stringCombinationsTwoWords[i]);
				
		}
		
		
		// Make further passess until there are no more candidate plaintexts or we have found all possible combinations.
		
		bool isShortListAcitve = true;
		
		
		while (finalShortList.size() <= 0 &&  (shortList.size() > 0 || shortList1.size() > 0))
		{
			if (isShortListAcitve)
			{
				
				permute(shortList,shortList1,dictionary2,stringCombinationsTwoWords,cipherText,t);
				isShortListAcitve = false;
				shortList.clear();
				
			}
			else
			{
				
				permute(shortList1,shortList,dictionary2,stringCombinationsTwoWords,cipherText,t);
				isShortListAcitve = true;
				shortList1.clear();
				
			}
		}
		
		
		// Check if we have found plain text or not.
		if (finalShortList.size() <= 0)
			cout << endl << "Could not find any matching plaintext for the given cipher." << endl;
		else
			cout  << endl << "Plaintext found in Dictionary 2:" << endl;
		
		
		// TODO : Find a way to shorten the number of plaint texts. Right now its gives a few options.
		// We should try to correct this. May be find the longest common substring or something....
		set<string> finalPlaintTextSet;
		pair<std::set<string>::iterator,bool> ret;
		for (unsigned i =0; i < finalShortList.size();i++)
		{
			line = finalShortList[i] ;
			
			GetKey(line,cipherText,key,t); 
			
			std::sort (key.begin(), key.begin() + key.size()); 
			std::vector<int>::iterator it;
			it = unique (key.begin(), key.end());   
                                                         
			key.resize(distance(key.begin(),it) ); 
			
			if (key.size() <= t)
			{
				ret = finalPlaintTextSet.insert(line);
				if (ret.second)
					cout <<endl << line << endl;
				//exit(0);
			}
			else
				key.clear();
		}
		
		cout << endl;
		
	return 0;
} // main

