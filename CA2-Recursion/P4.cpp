#include <functional>
#include <iostream>
#include <string>

using namespace std;

void decrypt_Hash(string word,const unsigned long int hashed,bool& found);
void finding_All_words(const string alphabet, string word,const unsigned long int hashed,bool& found,int plain_Text_length);

int main(){
	int plain_Text_length;
	string alphabet;
	char ch;
	unsigned long int hashed;
	bool found=false;
	cin>>plain_Text_length;
	cin>>alphabet;
	cin>>hashed;
	finding_All_words(alphabet,"\0",hashed,found,plain_Text_length);
	if(!found)
			cout << "NOT_FOUND\n";
}

void finding_All_words(const string alphabet, string word,const unsigned long int hashed,bool& found,int plain_Text_length){
	if (plain_Text_length == 0){
	decrypt_Hash(word,hashed,found);
		return;
	}
	for (int alphabet_Index = 0; alphabet_Index < alphabet.size(); alphabet_Index++){
		string new_word;
		new_word = word + alphabet[alphabet_Index];
		finding_All_words(alphabet, new_word,hashed,found,plain_Text_length-1);
	}
}

void decrypt_Hash(string word,const unsigned long int hashed,bool& found){
	if (hash<string>()(word) == hashed) {
		cout<<word<<endl;
		found=true;
	}
}

