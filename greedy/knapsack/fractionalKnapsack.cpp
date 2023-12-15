#include<bits/stdc++.h>
using namespace std;

struct item{
    string ID;
    int weight;
    int benefit;
    double unitbenefit;
}items[1000];

int numberOfItems, capacity;

void readInput(){
    cin>>numberOfItems>>capacity;
    for(int i=0; i<numberOfItems; i++){
        cin>>items[i].ID>>items[i].weight>>items[i].benefit;
        items[i].unitbenefit = items[i].benefit/items[i].weight;
    }
}

void printOutput(){
    for(int i=0; i<numberOfItems; i++){
        cout<<items[i].ID<<"  "<<items[i].weight<<"  "<<items[i].benefit<<endl; 
    }
    cout<<"-------------------------------------------------------------------"<<endl;
}

bool compare(struct item item1, struct item item2){     //   sort max to min
    return item1.benefit/item1.weight > item2.benefit/item2.weight;
}

double fractionKnapsnac(){
    int currentweight = 0;
    double benefit = 0;
    for(int i=0; i<numberOfItems; i++){
        if(items[i].weight < (capacity - currentweight)){
            currentweight = currentweight + items[i].weight;
            benefit = benefit + items[i].weight * items[i].unitbenefit;
        }
        else {
            benefit = benefit + (capacity - currentweight) * items[i].unitbenefit;
            return benefit;
        }
    }
    return benefit;
}

int main(){
    //freopen("items_input.txt", "r", stdin);
    freopen("items_2.txt", "r", stdin);
    readInput();
    printOutput();
    sort(items, items+numberOfItems, compare);   // this will sort max to min using condition "compare"
    printOutput();
    double totalBenefit = fractionKnapsnac();
    cout<<"Total benefit: "<<totalBenefit<<endl;
}