#include <bits/stdc++.h>
using namespace std;

int main(){
    ifstream ifs;
    char buffer[256]={0};
    string intput;
    int correct;
    cin>>intput;
    ifs.open("Data/test.txt");
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
    }else{
        while(!ifs.eof()) {
            correct=0;
            ifs.getline(buffer, sizeof(buffer));
            cout<<intput<<" -> "<<buffer<<endl;
            if(intput==buffer){
                correct=1;
                break;
            }
        }
        ifs.close();
        if(correct==0) cout<<"not a allowed word.\n";
    }
    return 0;
}