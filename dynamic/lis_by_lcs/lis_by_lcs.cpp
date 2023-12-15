#include<bits/stdc++.h>
#define diarrow -100
#define uparrow -101
#define lftarrow -102
#define MAX 1000
using namespace std;

struct cell{
    int count;
    int arrow;
}Matrix[MAX][MAX];

int numOfElement, arr1[MAX], sorted[MAX];

void getInput(){
    cin>>numOfElement;
    for(int i=0; i<numOfElement; i++){
        cin>>arr1[i];
        sorted[i] = arr1[i];
    }
}

void LCS(int m, int n){
    for(int i=0; i<=m; i++) Matrix[i][0].count = 0;
    for(int j=1; j<=n; j++) Matrix[0][j].count = 0;

    for(int i=1; i<=m; i++){
        for(int j=1; j<=n; j++){
            if(arr1[i-1]==sorted[j-1]){   // vul hoy karon string suru hoice 0 index theke but matrix e count korsi 1 theke
                Matrix[i][j].count = Matrix[i-1][j-1].count + 1;
                Matrix[i][j].arrow = diarrow;
            }
            else if(Matrix[i-1][j].count >= Matrix[i][j-1].count){
                Matrix[i][j].count = Matrix[i-1][j].count;
                Matrix[i][j].arrow = uparrow;
            }
            else{
                Matrix[i][j].count = Matrix[i][j-1].count;
                Matrix[i][j].arrow = lftarrow;
            }
        }
    }
}

void printLCS(int m, int n){
    if(m==0 || n==0){
        return;
    }
    else if(Matrix[m][n].arrow == diarrow){
        printLCS(m-1, n-1);
        cout<<arr1[m-1]<<" ";   //vul korsilam string er indexing suru hoy 0 theke
    }
    else if(Matrix[m][n].arrow == uparrow){
        printLCS(m-1, n);
    }
    else if(Matrix[m][n].arrow == lftarrow){
        printLCS(m, n-1);
    }
}

void LIS(int m, int n){
    LCS(m, n);
}

void printLIS(int m, int n){
    printLCS(m, n);
    cout<<endl;
}

int main(){
    freopen("LIS_input.txt", "r", stdin);

    getInput();
    sort(sorted, sorted + numOfElement);
    LIS(numOfElement, numOfElement);
    printLIS(numOfElement, numOfElement);
}
