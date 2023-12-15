#include<bits/stdc++.h>
#define MAX 100
using namespace std;
 
struct ITEM{
    string ID;
    int weight;
    int profit;
}items[MAX];

int table[MAX][MAX];
int numOfItems, capacity;

void readInput(){
    cin>>numOfItems>>capacity;
    for(int i=1; i<=numOfItems; i++){
        cin>>items[i].ID>>items[i].weight>>items[i].profit;
    }
}

void printOutput(){
    for(int i=1; i<=numOfItems; i++){
        cout<<items[i].ID<<"  "<<items[i].weight<<"  "<<items[i].profit<<endl; 
    }
    cout<<"-------------------------------------------------------------------"<<endl;
}

void knapsack(){
    for(int i=1; i<=numOfItems; i++){
        for(int w=1; w<=capacity; w++){

            if(items[i].weight > w){
                table[i][w] = table[i-1][w];
            }
            else{
                table[i][w] = max(table[i-1][w], items[i].profit + table[i-1][w-items[i].weight]);
            }
        }
    }
}

int main(){
    freopen("knap01_input.txt", "r", stdin);
    readInput();
    printOutput();

    knapsack();
    for(int i=0;i<=numOfItems; i++){
        for(int w = 0; w<=capacity; w++){
            cout<<table[i][w]<<" ";
        }
        cout<<endl;
    }
    cout<<"Max profit is: "<<table[numOfItems][capacity]<<endl;
}