#include<iostream>
#include<fstream>
using namespace std;

struct Groundwork{
  int start_time;
  int duration;
  int end_time;
};

struct Available_Groundworks{
   int n;
   Groundwork arr[22];
};

Available_Groundworks* initialize (int start_time[ ], int duration[ ], int n){
  Available_Groundworks G;
  Available_Groundworks* ptr = &G;
  ptr->n=n;
  for(int i=0;i<n;i++){
    G.arr[i].duration=duration[i];
    G.arr[i].start_time=start_time[i];
    G.arr[i].end_time=start_time[i] + duration[i];
  }
  return ptr;
}

void selectionSort(int start_time[ ], int duration[ ], int n) {
   int i, j, minm,temp;
   for (i = 0; i < n - 1; i++) {
      minm = i;
      for (j = i + 1; j < n; j++)
        if (start_time[j] < start_time[minm])
          minm = j;
      temp = start_time[i];
      start_time[i] = start_time[minm];
      start_time[minm] = temp;
      temp = duration[i];
      duration[i] = duration[minm];
      duration[minm] = temp;
   }
}

int CalculateMaxGroundworks(Available_Groundworks* ptr){
  if(ptr->n==1) return 1;
  Available_Groundworks G;
  Available_Groundworks* newptr = &G;
  for(int i=0;i<(ptr->n-1);i++)
    newptr->arr[i] = ptr->arr[i+1];
  newptr->n = ptr->n - 1;
  if(ptr->arr[0].end_time <= ptr->arr[1].start_time) {
    return 1+CalculateMaxGroundworks(newptr);
    }
  else if(ptr->arr[0].end_time <= ptr->arr[2].start_time && ptr->arr[1].end_time > ptr->arr[2].start_time) {
    return 1+CalculateMaxGroundworks(newptr);
  }
  return CalculateMaxGroundworks(newptr);
}

int main(){
  char str[80];
  int start_time[22],duration[22],Count=0;
  ifstream fin;
  fin.open("Schedule.txt");
  while(!fin.eof()){
    fin>>str;
    if(!fin.eof()){
      fin>>start_time[Count]>>duration[Count];
      Count++;
    }
  }
  fin.close();
  selectionSort(start_time, duration, 22);
  Available_Groundworks* ptr = initialize(start_time, duration, 22);
  Available_Groundworks G = *ptr;
  cout<<CalculateMaxGroundworks(&G);
}
