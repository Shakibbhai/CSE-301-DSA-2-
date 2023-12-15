
#include<bits/stdc++.h>
using namespace std;

struct node{
    char ch;
    int freq;
    char code;
    bool isdone;
    struct node *left, *right;
};

struct node nodes[10000];
vector<char> huffcode;

struct node* extract_min(int last){
    struct node *min = NULL ;
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->ch= '\0';
    temp->freq = 100000;
    temp->left = NULL;
    temp->right = NULL;
    min = temp;
    for(int i=0; i<=last; i++){
        if(!nodes[i].isdone && nodes[i].freq < min->freq){
            min = &nodes[i];
        }
    }
    min->isdone = true;
    return min;
}

struct node* huffman(int size){
    int ptr = size-1;
    struct node *x, *y;
    for(int i=1; i<size; i++){   //binary tree er edge number = (vertex - 1);
        x = extract_min(ptr);
        y = extract_min(ptr);
        x->code = '0';
        y->code = '1';
        ptr++;
        //freopen('0', EOF, input.txt);
        nodes[ptr].ch = '\0';
        nodes[ptr].freq = x->freq + y->freq;
        nodes[ptr].code = '\0';
        nodes[ptr].isdone = false;
        nodes[ptr].left = x;
        nodes[ptr].right = y;
    }
    return extract_min(ptr);
};

void preorder(struct node *root){
    if(!root){
        return;
    }
    if(root->code){
        huffcode.push_back(root->code);
    }

    if(root->ch != '\0'){
        cout<< root->ch <<" = ";
        for(auto it: huffcode){
            cout<< it;
        }
        cout<<endl;
    }

    preorder(root->left);
    if(root->left) huffcode.pop_back();
    preorder(root->right);
    if(root->right) huffcode.pop_back();
}

int main(){
    int n;
    freopen("input.txt", "r", stdin);
    cin>>n;
    for(int i = 0; i<n; i++){
        cin>>nodes[i].ch;
        cin>>nodes[i].freq;
        nodes[i].code = '\0';
        nodes[i].isdone =  false;
        nodes[i].left = NULL;
        nodes[i].right = NULL;
    }
    struct node *root = huffman(n);
    preorder(root);
    return 0;
}
