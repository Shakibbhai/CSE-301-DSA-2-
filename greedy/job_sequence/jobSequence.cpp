#include<bits/stdc++.h>
using namespace std;

struct node{
    string job;
    int start, finish;
    bool iscompat;
}jobs[1000];
int numberOfjobs;

void readInput(){
    cin>>numberOfjobs;
    for(int i=0; i<numberOfjobs; i++){
        cin>>jobs[i].job>>jobs[i].start>>jobs[i].finish;
        jobs[i].iscompat = true;
    }
}

void printJobs(){
    for(int i=0; i<numberOfjobs; i++){
        cout<<jobs[i].job<<" "<<jobs[i].start<<" "<<jobs[i].finish<<" "<<jobs[i].iscompat<<" ";
        cout<<endl;
    }
}

// void sort(){
//     struct node temp;
//     for(int i=0; i<numberOfjobs-1; i++){
//         for(int j=0; j<numberOfjobs-1-i; j++){
//             if(jobs[j].finish > jobs[j+1].finish){
//                 temp = jobs[j];
//                 jobs[j] = jobs[j+1];
//                 jobs[j+1] = temp;
//             }
//         }
//     }
// }

bool compare(struct node job1, struct node job2){
    return job1.finish<job2.finish;
}

void iterativeselection(){
    int k = 0; 
    for(int i=k+1; i<numberOfjobs; i++){
        if(jobs[i].start < jobs[k].finish){
            jobs[i].iscompat = 0;
        }
        else k = i;
    }
}

void recursiveSelection(int present){
    int i ;
    for(i=present + 1; i<numberOfjobs && jobs[present].finish > jobs[i].start; i++){
        jobs[i].iscompat = 0;
    }
    if(i<numberOfjobs){
        recursiveSelection(i);
    }
} 

int main(){

    freopen("job_input.txt", "r", stdin);
    readInput();
    printJobs();
    cout<<"----------------------------------------------------------------------------------"<<endl;
    sort(jobs, jobs+numberOfjobs, compare);
    printJobs();
    cout<<"----------------------------------------------------------------------------------"<<endl;

    //iterativeselection();
    recursiveSelection(0);
    for(int i=0; i<numberOfjobs; i++){
        if(jobs[i].iscompat){
            cout<<jobs[i].job<<" "<<jobs[i].start<<" "<<jobs[i].finish<<" "<<jobs[i].iscompat<<endl;
        }
        
    }

}