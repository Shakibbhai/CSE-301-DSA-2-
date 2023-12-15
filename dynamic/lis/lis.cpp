#include<bits/stdc++.h>
#define MAX 100
using namespace std;

int arr[MAX];
int L[MAX];
int prevIndex[MAX];

int numOfElement;

void getInput(){
    cin>>numOfElement;
    for(int i=0; i<numOfElement; i++){
        cin>>arr[i];
        L[i] = 1;
        prevIndex[i] = -1;
    }
}

int LIS(){

    int maxLenIndex = 0, maxLen = L[0];

    for(int i=1; i<numOfElement; i++){
        for(int j = 0; j<i; j++){
            if (arr[j] < arr[i] && L[j] + 1 > L[i]) {
                L[i] = L[j] + 1;
                prevIndex[i] = j;
            }
        }
        if(L[i] > maxLen){
            maxLen = L[i];
            maxLenIndex = i;
        }
    }

    return maxLenIndex;
}

void LIS_path(int index){
    if(index == -1) return;
    LIS_path(prevIndex[index]);
    cout<< arr[index]<< " ";
}

int main(){

    freopen("LIS_input.txt", "r", stdin);
    getInput();

    int maxLenIndex = LIS();

    cout<<"Maximum length: "<< L[maxLenIndex]<<endl;
    cout<<"Sequence is: ";
    LIS_path(maxLenIndex);
    cout<<endl;
}
