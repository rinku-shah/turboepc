//To delete entries from delay file:  sed -i '/^pattern/d' delay.csv
//(C++) Operations: Input/Output
#include <iostream>
#include <math.h>

//(C++) STL Operations: String, Vector, String stream
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <queue>

// For integrity protection (NAS Signalling)
#include <openssl/hmac.h>

// For encryption/decryption (AES)
#include <openssl/aes.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

//(C) Operations: Input/Output, String, Standard libraries(like atoi, malloc)
#include <stdio.h>
#include <random>
#include <string.h>
#include <stdlib.h>
#include <thread>
exponential_distribution<double> exponential(1.0/mean);
int main()
{
    const double mean = 13.0;
    double sum = 0.0;
    
    //exponential_distribution<double> exponential(1.0/mean);
    for (int i = 0; i < 10; ++i){
        sum += exponential(i);
	printf("%f /n",sum); //cout<<i<<endl;
    }
    return(1);
}
