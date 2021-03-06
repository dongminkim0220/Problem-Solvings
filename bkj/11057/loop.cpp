#include <iostream>
#define HASH 10007

using namespace std;
int main(void){

    for(int n = 1; n <= 1000; n++){
    int N;
    N = n;

    int ** arr = new int* [10];
    for(int i = 0; i < 10; i++){
        arr[i] = new int[N+1];
    }
 
    // init
    for(int i = 0; i < 10; i++){
        arr[i][1] = 1;
    }

    // loop
    for(int j = 2; j <= N; j++){
        int sum = 0;
        for(int i = 0; i < 10; i++){
            sum += arr[i][j-1]; 
            arr[i][j] = sum % HASH;
        }
    }

    // get answer
    int ans = 0;
    for(int i = 0; i < 10; i++){
        ans += (arr[i][N]) % HASH;
    }
    cout << ans << endl;

    for(int i = 0; i < 10; i++){
        delete arr[i];
    }
    delete arr;

    //return 0;
}
}
