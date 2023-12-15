#include<bits/stdc++.h>
#define MAX 100
using namespace std;

int numOfElement;
int arr[MAX];
int sum[MAX];
int prevIndex[MAX];

void getInput(){
    cin>>numOfElement;
    for(int i=1; i<=numOfElement; i++){
        cin>>arr[i];
    }
}

int maxSubArray(){
    for(int i=1; i<=numOfElement; i++){
        if(sum[i-1]<0){
            sum[i] = arr[i];
        }
        else{
            sum[i] = sum[i-1] +  arr[i];
            prevIndex [i] = i-1;
        }
    }
    
    int maxSumIndex, maxSum = sum[0];
    for(int i=1; i<=numOfElement; i++){
        if(sum[i] > maxSum){
            maxSum = sum[i];
            maxSumIndex = i;
        }
    }

    return maxSumIndex;
}

void printSubArray(int index){
    if(index == 0) return;
    printSubArray(prevIndex[index]);
    cout<<arr[index]<<" ";
}

int main(){
    
    freopen("MSI_input.txt", "r", stdin);
    getInput();
    
    int maxSumIndex = maxSubArray();
    cout<<"Maxumum sub array sum: "<<sum[maxSumIndex]<<endl;
    
    printSubArray(maxSumIndex);
    cout<<endl;
}