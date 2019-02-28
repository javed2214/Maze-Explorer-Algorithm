// Maze Explorer Algorithm (C++ Code)

#include<bits/stdc++.h>
using namespace std;
#define MOD 1000000007
#define DB(x) cout<<#x<<"="<<x<<endl;
#define FASTREAD ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define ll long long int
#define SIZE 100000000

void addString(string &new_path, int k, string path){

	for(int i=k;i<path.length();i++)
		new_path+=path[i];
}

int main(){

+
	FASTREAD;
	unordered_map <string,string> Map;

	Map["LBR"]="B";
	Map["LBS"]="R";
	Map["RBL"]="B";
	Map["SBL"]="R";
	Map["SBS"]="B";
	Map["LBL"]="S";

	string path="LLLLBLSBLLBLL";
	int count=3;
	string s;

	vector <string> v;

	cout<<"Possible Combinations: ";
	for(int i=0;i<path.length()-2;i++){

		s=path.substr(i,i+count);
		cout<<s<<" ";
		if(Map.find(s)!=Map.end()){
			path.replace(i,i+count,(Map[s]));
			i=0;
			count=3;
		}
		count--;
	}
	cout<<"\nShortest Path: ";
	cout<<path;
	cout<<"\n";

	if(Map.find(path)!=Map.end()) cout<<Map[path];
	
	return 0;
}