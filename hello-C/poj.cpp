#include <iostream>
using namespace std;
int main(){
    unsigned int x;
    int y;
    cin >> x>>y;
    if( x>y ) 
        cout << ">" ;
    else if(x==y)
        cout << "=";
else cout << "<";
    return 0;
}