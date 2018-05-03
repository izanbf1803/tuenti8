#include <iostream>
#include <iomanip>
#include <cmath>
#include <climits>
#include <algorithm>
#include <vector>
#include <array>
#include <queue>
#include <stack>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
using namespace std;

#define D(x) cerr << #x << " = " << (x) << ", "

typedef unsigned int uint;
typedef unsigned long ul;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef unsigned char byte;

template<typename T> using V = vector<T>;
template<typename T, typename U> using P = pair<T,U>;
template<typename T, typename U> using umap = unordered_map<T,U>;
template<typename T, typename U> using uset = unordered_set<T,U>;
template<typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T> using max_heap = priority_queue<T>;

template <typename T>
ostream& operator<<(ostream& os, V<T> v)
{
	os << "{";
	if (v.size() > 0) {
		os << v[0];
		for (int i = 1; i < v.size(); ++i) {
			os << ", " << v[i];
		}
	}
	os << "}";
	return os;
}

struct chain_sort {
	bool operator()(const string& a, const string& b)
	{
		if (a.size() != b.size()) return a.size() < b.size();
		return a < b;
	}
};

V<int> in_sequence(const map<int,int> indices, const V<string>& chains, int n)
{
	V<int> sq;
	for (int i = 0; i < n; ++i) {
		V<int> perm;
		for (int j = 0; j < n; ++j) {
			if (i != j) perm.push_back(j);
		}
		do {
			string chain = "";
			for (int k : perm) {
				chain += chains[k];
			}
			if (chain.find(chains[i]) != string::npos) {
				sq.push_back(indices.at(i));
				break;
			}
		} while (next_permutation(perm.begin(), perm.end()));
	}
	sort(sq.begin(), sq.end());
	return sq;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(0);
    int n = argc-1;
    V<string> chains(n);
    map<string,int> str_indices;
    map<int,int> indices;
    for (int i = 0; i < n; ++i) {
    	chains[i] = argv[i+1]; 
    	str_indices[chains[i]] = i+1;
    }
    sort(chains.begin(), chains.end(), chain_sort());
    for (int i = 0; i < n; ++i) {
    	indices[i] = str_indices[chains[i]];
    }
    // cerr << chains << endl << in_sequence(indices, chains, n) << endl;
    V<int> sq = in_sequence(indices, chains, n);
    if (sq.size() > 0) {
	    cout << sq[0];
	    for (int i = 1; i < sq.size(); ++i) {
	    	cout << ',' << sq[i];
	    }
	    cout << endl;
	}
}