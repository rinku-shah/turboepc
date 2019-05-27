#include <ctime>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
int main() {
  using namespace std;
  clock_t begin = clock();
  double elapsed_secs;
  clock_t end = begin + 1000;
  cout <<begin << " "<<end <<endl; 
  while(elapsed_secs < end){
  usleep(1000);
  

  //clock_t end = clock();
  clock_t curr = clock();
  elapsed_secs = double(curr - begin); // / CLOCKS_PER_SEC;
  cout <<begin << " "<<end << " "<<elapsed_secs<<endl; 
}

  return 0;
}
