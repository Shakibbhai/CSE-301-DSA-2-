#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string str;
char alphabet[100];
string Pk;
string Pq;
int delta[100][100]; // Assuming a maximum of 100 states and 100 alphabet symbols
string input;
int main() {
    int num;
    cout << "Enter the number of alphabet: ";
    cin >> num;

    for (int i = 0; i < num; i++) {
        cin >> alphabet[i];
    }

    cout << "Enter the pattern: ";
    cin >> str;
    int m = str.length();

    for (int q = 0; q <= m; q++) {
        for (int i = 0; i < num; i++) {
            int k = 1+min(m, q + 1);
            while (k > 0) {
                --k;
                Pk = str.substr(0, k);
                Pq = str.substr(0, q) + alphabet[i];
                string ch = Pq.substr(Pq.size()-k);
                if (Pk == ch) {
                    break;
                }
            }
            delta[q][i] = k;
        }
    }

    // Print the transition function
    cout << "Transition Function:" << endl;
    for (int q = 0; q <= m; q++) {
        for (int i = 0; i < num; i++) {
            cout << "δ(" << q << ", " << alphabet[i] << ") = " << delta[q][i] << "\t";
        }
        cout << endl;
    }

    cout << "Enter the input string: ";
    cin >> input;
    int len = input.length();
    int q =0, s, count=0;
    for (int i = 0; i < len; i++)
    {
        q = delta[q][input[i]-'a'];
        if(q==m){
            s = i-m+1;
            cout << "Pattern occurs with shift "<< s << endl;
            ++count;
        }
    }
    cout << "Total matched string: "<<count<<endl;

    return 0;
}
