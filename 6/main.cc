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

struct Iv { // interval
	int x, l, s, p; // X, L, S, P, initial position, length, speed and score of the note.
	int start;
	int end;
};

struct Iv_sort {
	bool operator()(const Iv& a, const Iv& b) 
	{
		if (a.end != b.end) return a.end < b.end;
		return a.p > b.p;
	}
};

V<Iv> ivs; // intervals

int last_non_conflict(int index) // using binary search
{
	int l = 0;
	int r = ivs.size();
	int m;
	while (r - l >= 1) {
		m = (l + r) / 2;
		if (ivs[m].end < ivs[index].start) {
			if (ivs[m+1].end >= ivs[index].start) {
				return m;
			}
			else {
				l = m+1;
			}
		}
		else {
			r = m;
		}
	}
	return -1;
}

ll max_score_starting_from(int start)
{
	int n = ivs.size();
	V<int> dp(n);
	dp[0] = ivs[0].p;
	ll maxsum = 0;
    for (int i = 1; i < n; ++i) {
    	int sum = ivs[i].p;
    	int l = last_non_conflict(i);
    	if (l != -1) sum += dp[l];
    	dp[i] = max(dp[i-1], sum);
    }
    return dp[n-1];
}

int main()
{
    ios::sync_with_stdio(0);

    int C;
    cin >> C;
    for (int tc = 1; tc <= C; ++tc) {
        int n;
        cin >> n;
        ivs.clear();
        for (int i = 0; i < n; ++i) {
        	Iv iv;
        	cin >> iv.x >> iv.l >> iv.s >> iv.p;
        	iv.start = iv.x / iv.s;
        	iv.end = (iv.x + iv.l) / iv.s;
        	bool merged = false;
        	for (Iv& iv2 : ivs) {
        		if (iv.start == iv2.start and iv.end == iv2.end) {
        			merged = true;
        			iv2.p += iv.p;
        			break;
        		}
        	}
        	if (not merged) ivs.push_back(iv);
        }
        sort(ivs.begin(), ivs.end(), Iv_sort());
        cout << "Case #" << tc << ": " << max_score_starting_from(0) << endl;	
    }
}