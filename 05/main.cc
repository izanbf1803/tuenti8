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


bool bt(const V<string>& chains, int n, const string& prefix, set<int>& indices)
{
	for (int i = 0; i < n; ++i) {
		if (indices.count(i) == 0) {
			const string& longest  = prefix.size() >  chains[i].size() ? prefix : chains[i];
			const string& shortest = prefix.size() <= chains[i].size() ? prefix : chains[i];

			if (longest.find(shortest) == 0) {
				indices.insert(i);
				string sufix = longest.substr(shortest.size());
				if (sufix.size() == 0 or bt(chains, n, sufix, indices)) return true;
				indices.erase(i);
			}
		}
	}

	return false;
}

set<int> in_sequence(const V<string>& chains, int n)
{
	for (int i = 0; i < n; ++i) {
		set<int> indices = { i };
		if (bt(chains, n, chains[i], indices)) {
			return indices;
		}
	}
	return {};
}

int main(int argc, char** argv)
{
	ios::sync_with_stdio(0);
	int n = argc-1;
	V<string> chains(n);
	map<string,int> str_indices;
	map<int,int> real_indices;
	for (int i = 0; i < n; ++i) {
		chains[i] = argv[i+1]; 
		str_indices[chains[i]] = i+1;
	}
	sort(chains.begin(), chains.end(), chain_sort());
	for (int i = 0; i < n; ++i) {
		real_indices[i] = str_indices[chains[i]];
	}
	set<int> sq = in_sequence(chains, n);
	if (not sq.empty()) {
		V<int> result;
		for (int k : sq) {
			result.push_back(real_indices[k]);
		}
		sort(result.begin(), result.end());
		for (int i = 0; i < result.size(); ++i) {
			if (i > 0) cout << ',';
			cout << result[i];
		}
		cout << endl;
	}
	else {
		cout << "ERR" << endl;
	}
}