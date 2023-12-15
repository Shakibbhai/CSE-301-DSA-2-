#include<bits/stdc++.h>
using namespace std;

struct rod{
    int length;
    int price;
    int maxProfit;
    pair<int, int> lengths;
}cutLength[1000];
int numberOfInput, totalLength;
int totalcut = 0;

void readInput(){
    cin>>numberOfInput>>totalLength;
    for(int i=1; i<=numberOfInput; i++){
        cin>>cutLength[i].length>>cutLength[i].price;
        cutLength[i].maxProfit = -100;
    }
}

void printResult(){
    for(int i=1; i<=numberOfInput; i++){
        cout<<cutLength[i].length<<" "<<cutLength[i].price<<" "<<cutLength[i].maxProfit<<endl;
        cout<<"pairs :"<< cutLength[i].lengths.first<<" "<<cutLength[i].lengths.second<<endl; 
    }
    cout<<"------------------------------------------------------------------"<<endl;
}

int calcMaxProfit(int i){
    cout<<"length: "<<i<<endl;
    if(cutLength[i].maxProfit > 0){
        return cutLength[i].maxProfit;
    } 
    else if( i==0 ){
        return 0;
    }
    else{
        int profit = -1, length1, length2;
        for(int j=1; j<=i; j++){
            if(cutLength[j].price == 0) continue;
            int calculatedprofit = cutLength[j].price + calcMaxProfit(i-j);
            if(calculatedprofit > profit){
                length1 = j;
                length2 = i - j;
                profit = calculatedprofit;
            }
            //profit = max(profit, cutLength[j].price + calcMaxProfit(i-j));
        }
        cutLength[i].lengths.first = length1; 
        cutLength[i].lengths.second = length2; 
        //lengths.push_back(length);
        //cout<<"for maxprofit for "<<i<< " take length: "<< length
        return profit;
    } 
}

void cutRod(){
    for(int i=0; i<=totalLength; i++){
        cutLength[i].maxProfit = calcMaxProfit(i);
    }
}

void printcutlength(int lentgh){
    int length1 = cutLength[lentgh].lengths.first;
    int length2 = cutLength[lentgh].lengths.second;
    if( length1 == 0 || length2 == 0){
        totalcut++;
        if(length1){
            cout<<length1<<" ";
        }
        else cout<< length2<<" ";
    }
    else{
        printcutlength(length1);
        printcutlength(length2);
    }
}

int main(){
    
    freopen("rodCutting_input.txt", "r", stdin);
    readInput();
    printResult();
    cutRod();
    printResult();
    cout<<"Maxprofit for length "<<totalLength<<" is : "<<cutLength[totalLength].maxProfit<<endl;
    cout<<"take this lengths: ";

    printcutlength(totalLength);
    cout<<endl;
    cout<<"total cut: "<<totalcut<<endl;
}