#include <iostream>
using namespace std;
 
const int N = 1e5;
int n;
vector <pair <int, int>> edges[N];
int dist[N], tin[N], tout[N];
int timer;
int up[N][20];
 
void dfs(int v, int p) {
    tin[v] = ++timer;
    up[v][0] = p; // predok na 2^0 ot v 
    for (int lvl = 1; lvl < 20; ++lvl) { // predok na 2^lvl ot v
        up[v][lvl] = up[up[v][lvl - 1]][lvl - 1];
    }
    for (int i = 0; i < edges[v].size(); ++i) {
        int to = edges[v][i].first;
        int w = edges[v][i].second;
        if (to == p) {
            continue;
        }
        dist[to] = dist[v] + w;
        dfs(to, v);
    }
    tout[v] = timer;
}
 
bool isParent (int a, int b) {
    // ? a predok dlya b ? 
    return tin[a] <= tin[b] && tin[b] <= tout[a];
}
 
int lca(int a, int b) {
    // a parent b
    if (isParent(a, b)) {
        return a;
    }
    if (isParent(b, a)) {
        return b;
    }
    for (int i = 19; i >= 0; --i) {
        int pred = up[a][i]; // prijok na 2^i ot a;
        if (isParent(pred, b)) {
            continue;
        }
        a = pred;
    }
    return up[a][0];
}
 
void solve() {
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[u].push_back({v, w});
        edges[v].push_back({u, w});
    }    
    dfs(0, 0);
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        int LCA = lca(u, v);
        cout << dist[u] + dist[v] - 2 * dist[LCA] << endl;
    }
}
 
int main() {
    ios::sync_with_stdio(NULL), cin.tie(0), cout.tie(0);
    solve();
}