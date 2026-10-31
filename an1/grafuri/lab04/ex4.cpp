#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <unordered_map>
#include <set>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <stdlib.h>
#include <string>
using namespace std;
#define ull unsigned long long 
#define ld long double
#define ll long long
#define int long long
#define pii pair<int, int>
#define all(v) v.begin(), v.end()
int mod = 1e9 + 7; 
const ll inf = 1e18;
const int N = 1e5 + 50, K = 22;

struct Node{
    char ch;
    int freq;
    char minChar;
    Node* left;
    Node* right;

    Node(char c, int f){
        ch = c;
        freq = f;
        minChar = c;
        left = right = nullptr;
    }

    Node(Node* l, Node* r){
        left = l;
        right = r;
        freq = l->freq + r->freq;
        minChar = min(l->minChar, r->minChar);
    }
};

struct Compare{
    bool operator()(Node* a, Node* b){
        if(a->freq != b->freq)
            return a->freq > b->freq;
        return a->minChar > b->minChar;
    }
};

int32_t main(int32_t argc, char* argv[]){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    //int t = 1;
    // cin >> t;
    // while(t--)
    //     solve();

    if(argc != 3){
        cout << "Insuficiente argumente!!!\n";
        return 0;
    }

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int N;
    fin >> N;
    fin.get();

    map<char, int> freq;

    for(int i = 0; i < N; i++){
        char c;
        int f;

        fin.get(c);
        fin >> f;
        fin.get();

        freq[c] = f;
    }

    string cod;
    getline(fin, cod);

    priority_queue<Node*, vector<Node*>, Compare> pq;

    for(auto& [c, f] : freq)
        pq.push(new Node(c, f));

    while(pq.size() > 1){
        Node* a = pq.top(); 
        pq.pop();
        Node* b = pq.top(); 
        pq.pop();
        pq.push(new Node(a, b));
    }

    Node* root = pq.top();

    string ans = "";
    Node* cur = root;

    for(char bit : cod){
        if(bit == '0')
            cur = cur->left;
        else
            cur = cur->right;

        if(!cur->left && !cur->right){
            ans += cur->ch;
            cur = root;
        }
    }

    fout << ans << "\n";

    fin.close();
    fout.close();

    return 0;
}