#include <bits/stdc++.h>
#include <stdlib.h>	// 亂數相關函數
#include <time.h>	// 時間相關函數
#include<unistd.h>  //顏色輸出
using namespace std;

char table[6][5]={0};
char check_table[6][5];
char w_list[25]={0};
int w_index=0;
char y_list[25]={0};
int y_index=0;
stack<int> y_stack;
int icount=0;
int error_c=0;

typedef struct{
  int count;
  char data='N';
  char status='N';
}letter_t;

void init(){
  // init check_table
  for(size_t i=0;i<6;i++){
    for(size_t j=0;j<5;j++){
      check_table[i][j]='N';
    }
  }
}

void input(int count){
  string temp;
  cout<<"word: ";
  cin>>temp;
  if(temp.size()>5){
    icount-=1;
    error_c=1;
    return;
  }
  for(size_t i=0;i<5;i++){
    table[count][i]=temp[i];
  }
  cout<<"\n";
  cout<<"status(G,Y,W): ";
  cin>>temp;
  if(temp.size()>5){
    icount-=1;
    error_c=1;
    return;
  }
  for(size_t i=0;i<5;i++){
    check_table[count][i]=temp[i];
  }
  cout<<"\n";
}

void output(){
  system("clear");
  for(size_t i=0;i<6;i++){
    for(size_t j=0;j<5;j++){
      if(check_table[i][j]=='G'){
        cout<<"\033[32;7m"<<setw(2)<<table[i][j]<<" \033[0m";
        continue;
      }else if(check_table[i][j]=='Y'){
        cout<<"\033[33;7m"<<setw(2)<<table[i][j]<<" \033[0m";
        continue;
      }else if(check_table[i][j]=='W'){
        cout<<"\033[37;7m"<<setw(2)<<table[i][j]<<" \033[0m";
        continue;
      }else{
        cout<<"\033[30;7m"<<setw(2)<<"_"<<" \033[0m";
        continue;
      }
    }
    cout<<"\n";
  }
  cout<<"\n";
  // Error
  if(error_c!=0){
    switch(error_c){
      case 1:
        cout<<"error: input > 5 alphebet.\n";
        error_c=0;
        break;
      case 2:
        cout<<"word is not allowed word.\n";
        error_c=0;
        break;
    }

  }
}

void listWord(int count){
  cout<<"list :\n";
  // w_list
  for(size_t i=0;i<count;i++){
    for(size_t j=0;j<5;j++){
      if(check_table[i][j]=='W'){
        w_list[w_index]=table[i][j];
        w_index++;
      }
    }
  }
  // y_stack
  for(size_t i=0;i<count;i++){
    for(size_t j=0;j<5;j++){
      if(check_table[i][j]=='Y'){
        y_stack.push(table[i][j]);
      }
    }
  }
  // file read
  ifstream ifs;
  char buffer[256]={0};
  ifs.open("Data/allowed_words.txt");
  if (!ifs.is_open()){
      cout << "Failed to open file.\n";
  }else{
      while(!ifs.eof()){
        bool isCount=true;
        ifs.getline(buffer, sizeof(buffer));
        // check White
        for(size_t i=0;i<5;i++){
          for(size_t j=0;j<w_index;j++){
            if(buffer[i]==w_list[j]) isCount=false;
          }
        }
        // check yellow
        for(size_t i=0;i<5;i++){
          for(size_t j=0;j<y_index;j++){

          }
        }
        if(isCount) cout<<buffer<<endl;
    }
    ifs.close();
  }

  cout<<"\n";
}

int main(){
  init();
  // game loop
  while(true){
    output();
    input(icount);
    listWord(icount);
    icount+=1;
  }
  output();
  return 0;
}
