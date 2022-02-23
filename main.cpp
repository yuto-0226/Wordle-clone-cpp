// Title: Wordle Clone using C++
// Date: 2022/02/16
// Author: 羅崧瑋

#include <bits/stdc++.h>  // 萬用標頭檔
#include <stdlib.h>	      // 亂數相關函數
#include <time.h>	        // 時間相關函數
#include <unistd.h>       // 顏色輸出
using namespace std;

char table[6][5]={0};     //輸入表
char check_table[6][5];   // 檢查表
char current_word[5];     // 目前目標單字
int icount=0;             // count
bool all_correct=false;   // 檢查單字是否正確
int error_c=0;            // ERROR_CODE

void init(){
  // random word
  ifstream ifs;
  int count=0;
  char buffer[256]={0};

  // read file
  ifs.open("Data/possible_words.txt");
  if (!ifs.is_open()){
    error_c=3;
  }else{
    while(!ifs.eof()){
        ifs.getline(buffer, sizeof(buffer));
        count+=1;
    }
    ifs.close();
  }
  int max=count;
  int min=0;
  int rand_num=rand()%(max-min+1)+min;

  ifs.open("Data/possible_words.txt");
  if (!ifs.is_open()){
    error_c=3;
  }else{
    count=0;
    while(!ifs.eof()){
      ifs.getline(buffer, sizeof(buffer));
      if(rand_num==count){
        for(size_t i=0;i<5;i++) current_word[i]=buffer[i];
        cout<<buffer<<"\n";
        usleep(1000000);
        break;
      }
      count+=1;
    }
    ifs.close();
  }

  // init check_table
  for(size_t i=0;i<6;i++){
    for(size_t j=0;j<5;j++){
      check_table[i][j]='N';
    }
  }
}

void input(int count){
  string temp;
  cout<<"input: ";
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
}

void check(int count){
  // is allowed word
  ifstream ifs;
  char buffer[256]={0};
  bool is_allowed_word=false;

  ifs.open("Data/allowed_words.txt");
  if (!ifs.is_open()){
    error_c=3;
  }else{
      while(!ifs.eof()){
          ifs.getline(buffer, sizeof(buffer));
          //cout<<table[count]<<" -> "<<buffer<<endl;
          if(table[count][0]==buffer[0]&&
              table[count][1]==buffer[1]&&
              table[count][2]==buffer[2]&&
              table[count][3]==buffer[3]&&
              table[count][4]==buffer[4]){
                is_allowed_word=true;
                break;
          }
      }
      ifs.close();
  }
  // throw out error
  if(!is_allowed_word){
    icount-=1;
    error_c=2;
    return;
  }
  
  for(size_t i=0;i<5;i++){
    if(table[count][i]==current_word[i]){
      check_table[count][i]='G';
      continue;
    }
    for(size_t j=0;j<5;j++){
      if(table[count][i]==current_word[j]){
        check_table[count][i]='Y';
        i++;
        continue;
      }
    }
    check_table[count][i]='W';
  }
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
      case 3:
        cout << "Failed to open file.\n";
        error_c=0;
        break;
    }

  }
}

bool is_end(int count){
  if(count==6) return true;
  for(size_t i=0;i<5;i++){
    if(check_table[count][i]!='G') return false;
  }
  all_correct=true;
  return true;
}

int main(){
  srand(time(0));
  init();
  // game loop
  while(true){
    output();
    input(icount);
    check(icount);
    if(is_end(icount)) break;
    icount+=1;
  }
  output();
  if(all_correct){
    cout<<"Congrats! You win this turn.";
  }else{
    cout<<"See you next time :(";
  }
  return 0;
}