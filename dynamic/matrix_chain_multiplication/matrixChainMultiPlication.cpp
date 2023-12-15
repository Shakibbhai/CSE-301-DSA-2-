#include<bits/stdc++.h>
#define MAX 100
#define INF 1e9
using namespace std;

int arr[MAX], numOfMatrix;
int operationTable[MAX][MAX], indexDivideTable[MAX][MAX];

void getInput(){
    //while (scanf("%d", &arr[sizeOfDimensionArray++]) != EOF);
    //cout<<sizeOfDimensionArray;
    cin>>numOfMatrix;
    for(int i=0; i<=numOfMatrix; i++){
        cin>>arr[i];
    }
    for(int i=1; i<=numOfMatrix; i++){
        for(int j=1; j<=numOfMatrix; j++){
            operationTable[i][j] = -INF;
        }
    }
}

void printResource(){
    cout<<"Dimension matrix: "<<endl;
    for(int i=0; i<=numOfMatrix; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    cout<<"Operation Table: "<<endl;
    for(int i=1; i<=numOfMatrix; i++){
        for(int j=1; j<=numOfMatrix; j++){
            if(operationTable[i][j] == -INF){
                cout<<0<<"\t";
            }
            else
                cout<<operationTable[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<"Dividation index table:" <<endl;
    for(int i=1; i<=numOfMatrix; i++){
        for(int j=1; j<=numOfMatrix; j++){
            cout<<indexDivideTable[i][j]<<"\t";
        }
        cout<<endl;
    }
}

int MCM(int firstMatrix, int lastMatrix){
    if(firstMatrix == lastMatrix){
        operationTable[firstMatrix][lastMatrix] = 0;
        return 0;
    }
    else if( operationTable[firstMatrix][lastMatrix] >= 0 ){
        return operationTable[firstMatrix][lastMatrix];
    }  
    else{
        int q = INF;
        for(int i=firstMatrix; i<lastMatrix; i++){
            int operation = MCM(firstMatrix, i) + MCM(i+1, lastMatrix) + arr[firstMatrix-1]*arr[i]*arr[lastMatrix];
            if(operation < q){
                q = operation;
                operationTable[firstMatrix][lastMatrix] = q;
                indexDivideTable[firstMatrix][lastMatrix] = i;
            }
        }
    }
    return operationTable[firstMatrix][lastMatrix];
}

void printParenthesizedMatrix(int firstMatrix, int lastMatrix){
    if(firstMatrix == lastMatrix){
        cout<<"A"<<firstMatrix<<" * ";
        return;
    }
    else{
        cout<<"( ";
        printParenthesizedMatrix(firstMatrix, indexDivideTable[firstMatrix][lastMatrix]);
        printParenthesizedMatrix(indexDivideTable[firstMatrix][lastMatrix] + 1, lastMatrix);
        cout<<")";
    }
}

int main(){

    freopen("MCM_input.txt", "r", stdin);
    getInput();

    MCM(1,numOfMatrix);
    cout<<"Minimum operations needed: "<<operationTable[1][numOfMatrix]<<endl;
    cout<< "Parenthesized matrix: ";
    printParenthesizedMatrix(1, numOfMatrix);
    cout<<endl;
    printResource();
}