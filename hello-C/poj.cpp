#include <iostream>
using namespace std;
int main(){

    int a;
    cin >> a;
    if(a/3.0+50>a/1.2) cout << "Walk";
    else if(a/3.0+50==a/1.2) cout << "All";
    else cout << "Bike";
    return 0;
}