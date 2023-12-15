#include<bits/stdc++.h>
#define MAX 100
using namespace std;

int arr[MAX];
int L[MAX];
int L_Index[MAX];
int prevIndex[MAX];

int numOfElement;

void getInput(){
    cin>>numOfElement;
    arr[0] = 0;
    prevIndex[0] = -1;
    for(int i=1; i<=numOfElement; i++){
        cin>>arr[i];
        prevIndex[i] = -1;
    }
}

int LIS(){
    int L_length = 0;
    L[L_length] = arr[0];
    L_Index[L_length] =  -1;   // ei + er ager line just first compare ta correctly korte use hoice(think further)
    for(int i = 1; i<=numOfElement; i++){
        if(arr[i] > L[L_length]){
            L_length++;
            L[L_length] = arr[i];
            L_Index[L_length] = i;
            prevIndex[i] = L_Index[L_length-1];
        }
        else{
            int start = 0, end = L_length;
            while(start < end){
                int mid = (start + end)/2;
                if(L[mid] < arr[i]){
                    start = mid + 1;
                }
                else end = mid;
            }
            L[start] = arr[i];
            L_Index[start] = i;
            if( (start -1) >= 0)
                prevIndex[i] = L_Index[start - 1];
            else prevIndex[i] = -1;
        }
    }
    return L_length;
}

void LIS_path(int index){
    if(index == -1) return;
    LIS_path(prevIndex[index]);
    cout<< arr[index]<< " ";
}

int main(){

    freopen("LIS_Binary_input.txt", "r", stdin);
    getInput();

    int maxLen = LIS();

    cout<<"Maximum length: "<< maxLen<<endl;
    cout<<"Sequence is: ";
    LIS_path(L_Index[maxLen]);
    cout<<endl;

    // for(int i=0; i<=numOfElement; i++){
    //     cout<< i<<"  "<<arr[i]<<"  "<<prevIndex[i]<< endl;
    // }
}
