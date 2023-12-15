#include<bits/stdc++.h>
#define MAX 100
using namespace std;

struct ITEM{
    string ID;
    int weight;
    int profit;
}items[MAX];

struct Table{
    int maxProfit;
    int prevRow;
    int prevCol;
    bool isCompat;
}table[MAX][MAX];
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
                table[i][w].maxProfit = table[i-1][w].maxProfit;
                table[i][w].prevRow = i-1;
                table[i][w].prevCol = w;
                table[i][w].isCompat = false;
            }
            else{
                if(table[i-1][w].maxProfit > (items[i].profit + table[i-1][w-items[i].weight].maxProfit)){
                    table[i][w].maxProfit = table[i-1][w].maxProfit;
                    table[i][w].prevRow = i-1;
                    table[i][w].prevCol = w;
                    table[i][w].isCompat = false;
                }
                else{
                    table[i][w].maxProfit = items[i].profit + table[i-1][w-items[i].weight].maxProfit;
                    table[i][w].prevRow = i-1;
                    table[i][w].prevCol = w-items[i].weight;
                    table[i][w].isCompat = true;
                }
            }
        }
    }
}

void printPath(int row, int col){
    if(row == 0 && col == 0) return;
    printPath(table[row][col].prevRow, table[row][col].prevCol);
    if(table[row][col].isCompat){
        cout<<"Item-"<<items[row].ID<<"  ";
    }
}

int main(){
    freopen("knap01_input.txt", "r", stdin);
    readInput();
    printOutput();

    knapsack();
    for(int i=0;i<=numOfItems; i++){
        for(int w = 0; w<=capacity; w++){
            cout<<table[i][w].maxProfit<<" ";
        }
        cout<<endl;
    }
        
    cout<<"Max profit is: "<<table[numOfItems][capacity].maxProfit<<endl;
    cout<<"Items to be selected for maxprofit: ";
    printPath(numOfItems, capacity);
    cout<<endl;
}