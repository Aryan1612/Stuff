#include<bits/stdc++.h>
using namespace std;
int main(){
    vector<double>x={1,1.5,2,2.5,3,3.5,4},y={25,31,27,28,36,35,32};
    int n=x.size();
    double sumx=0,sumx2=0,sumy=0,sumxy=0;
    for(int i=0;i<n;i++){
        sumx+=x[i];
        sumx2+=x[i]*x[i];
        sumy+=y[i];
        sumxy+=x[i]*y[i];
    }
    //cout<<sumx<<" "<<sumx2<<" "<<sumxy<<endl;
    double b=(n*(sumxy-sumx*sumy/n))/(n*sumx2-sumx*sumx);
    double a=(sumy-b*sumx)/n;
    cout<<a<<" "<<b;
    return 0;
}
