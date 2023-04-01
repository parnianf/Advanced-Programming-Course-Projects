#include<iostream>
#include<vector>

using namespace std;

void get_Product(vector<int>& list, int element_Num, int before, int& after);

int main(void){
	vector<int> vec;
	int after=0;
	int temp;
	while(cin>>temp)
	vec.push_back(temp);
	get_Product(vec,0,1,after);
	for (int index = 0; index < vec.size(); index++)
		cout << vec[index] << ' ';
		cout<<"\b";
	return 0;
}

void get_Product(vector<int>& list,int element_Num,int before,int& after) {
	if (element_Num == list.size()-1) {
		after = list[element_Num];
		list[element_Num] = before;
		return;
	}
	get_Product(list, element_Num + 1, before*list[element_Num],after);
	int temp = after*before;
	after *= list[element_Num];
	list[element_Num] = temp;
}

