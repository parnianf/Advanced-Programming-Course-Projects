#include<iostream>
#include<string>
#include<cmath>

using namespace std;

void reverse_The_string(string& list, int i = 0);
void encrypt(string& list,string& res);

int main() {
	string str;
	getline(cin, str);
	string res="\0";
	encrypt(str,res);
	cout << res << endl;
}

void encrypt(string& list,string &res) {
	int k = floor(list.size() / 2);
	string firstPart = list.substr(k, list.size() - 1);
	string secondPart = list.substr(0, k);
	if (k == 0) {
		res+=list;
		return;
	}
	reverse_The_string(secondPart, 0);
	reverse_The_string(firstPart, 0);
	encrypt(firstPart,res);
	encrypt(secondPart,res);
}

void reverse_The_string(string& list, int i) {
	int n = list.length();
	if (i == n / 2)
		return;
	swap(list[i], list[n - i - 1]);
	reverse_The_string(list, i + 1);
}

