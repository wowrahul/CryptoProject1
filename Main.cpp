#include <iostream>
#include <string>
#include <map>
#include <vector>
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
	for (unsigned i =0;i < t;i++)
	{
		k = CharValueMap[cipherText[i]] - CharValueMap[plainText[i]] ;
		if (k < 0)
			key.push_back(k + 27);
		else
			key.push_back(k);
			
		
	}
} // GetKey

// Encrypt plaintext using the derived Key
bool EncryptandCheck(string plainText,string &cipherText,int t, vector<int>& key)
{
	cout << plainText << endl;
	int j =0;
	for (unsigned i =0 ; i < plainText.length(); i++)
	{
	char ch = plainText.at(i);
	
		int pCount = CharValueMap[ch] ;
		int sub = (pCount + key.at((i % 10)+ 1)) % 27;
		if (sub == 0)
			sub = 27;
		
		cout <<  ReverseCharValueMap[sub]  ;
	}
	
	//cout << encryptedString;
	return true;
}

// Initiates the cryptanalysis.
int BreakCipher(int &t,string &cipherText)
{
	//cout << "You entered " << t << " and cipher " << cipherText;
} // BreakCipher


// Dummy encryption for testing
void DummyEnc(string plainText)
{
	cout << plainText.length() << endl;
	
	for (unsigned i =0 ; i < plainText.length();i++)
	{
		char ch = plainText.at(i);
	
		int pCount = CharValueMap[ch] ;
		int sub = (pCount + (i + 1)) % 27;
		if (sub == 0)
			sub = 27;
		
		cout <<  ReverseCharValueMap[sub]  ;
	}
	cout << endl << "nqvxeuyojxtkngxddjsmizxvyceqgqheuuhbrplgftpexsxvoxxgm uyrdlkum kwliomhqjluhzxobzbvulrjyzhyazorfguirm";
}
int main()
{
	int t;
	string cipherText;
	string t_string;
	string plainText = "most organizations today depend on the use of data in two general ways standard business processes u";
	
	cout << "Enter the number of key symbols \n";
	getline(cin,t_string);
	t = atoi(t_string.c_str());
	cout << "Enter the cipher text \n";
	getline(cin,cipherText);
	
	
	//transform( cipherText.begin(), cipherText.end(), cipherText.begin(), ptr_fun <int, int> ( tolower ) );
	//cout << "Lowercase: " << cipherText << endl;
	//breakCipher(t,cipherText);
	SetDefaultFMap();
	SetDefaultValueMapping();
	/*for (unsigned i = 0; i < cipherText.length(); i += t) 
	{
		
		CreateFrequencyMap(cipherText.substr(i, t));
	}
	
	 for ( const auto &p : CharValueMap )
	{
		std::cout << p.first << '\t' << p.second << std::endl;
	} 
	*/
	
	//DummyEnc(plainText);
	vector <int> key;
	GetKey(plainText,cipherText,key,t);
	//cout << key.size() << endl;
	//for (unsigned i=0; i< key.size(); i++)
	//	cout << key.at(i);
	
	EncryptandCheck(plainText,cipherText,t,key);
	
	return 0;
} // main

