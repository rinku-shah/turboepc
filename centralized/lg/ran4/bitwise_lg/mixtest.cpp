#include <iostream>
#include <vector>
#include <random>

using namespace std;

int get_mix(vector<int> weights){
	int sum = 0;
	for(int i=0;i<weights.size();i++){
		sum+=weights[i];
	}

	int rnd = rand()%sum+1;

	for(int i=0; i<weights.size(); i++) {
		if(rnd < weights[i])
	    	return i;
	  	rnd -= weights[i];
	}
	//assert(!"should never get here");
}

int main(){
	vector<int> weights(4);
	weights[0]=4;
	weights[1]=3;
	weights[2]=2;
	weights[3]=1;
	int i=10000;
	vector<int> counter(4,0);
	while(i){
		counter[get_mix(weights)]++;
		i--; 
	}
	for(int i=0;i<4;i++){
		cout<<counter[i]<<endl;
	}
	return 0;
}