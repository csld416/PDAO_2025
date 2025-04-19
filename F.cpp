// Created on iPad.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 邊結構
struct Edge {
  int u, v, w, id;
};

// DSU
struct DSU {
  vector<int> p, r;
  DSU(int n): p(n), r(n,0) { iota(p.begin(), p.end(), 0); }
  int find(int x){ return p[x]==x ? x : p[x]=find(p[x]); }
  bool unite(int a,int b){
    a = find(a);  b = find(b);
    if (a==b) return false;
    if (r[a]<r[b]) swap(a,b);
    p[b] = a;
    if (r[a]==r[b]) r[a]++;
    return true;
  }
};

// Tarjan 找橋
int timer;
void dfsBridge(int u, int pe,
               vector<vector<pair<int,int>>>& adj,
               vector<int>& disc, vector<int>& low,
               vector<bool>& vis,
               unordered_set<int>& bridges)
{
  vis[u] = true;
  disc[u] = low[u] = ++timer;
  for (auto &pr : adj[u]) {
    int v = pr.first, eid = pr.second;
    if (eid == pe) continue;
    if (!vis[v]) {
      dfsBridge(v, eid, adj, disc, low, vis, bridges);
      low[u] = min(low[u], low[v]);
      if (low[v] > disc[u])  // 這條邊是橋
        bridges.insert(eid);
    } else {
      low[u] = min(low[u], disc[v]);
    }
  }
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, M;
  cin >> N >> M;
  vector<Edge> edges(M);
  for (int i = 0; i < M; i++) {
    cin >> edges[i].u >> edges[i].v >> edges[i].w;
    edges[i].id = i;
  }

  // 1. 先用一次 Kruskal 標出 inMST
  vector<int> idx(M);
  iota(idx.begin(), idx.end(), 0);
  sort(idx.begin(), idx.end(),
       [&](int a,int b){ return edges[a].w < edges[b].w; });
  DSU dsu0(N);
  vector<bool> inMST(M,false);
  for (int i : idx)
    if (dsu0.unite(edges[i].u, edges[i].v))
      inMST[i] = true;

  // 2. 用另一個 DSU 按權重分組做橋檢測
  DSU dsu(N);
  vector<int> critical, backup;

  for (int i = 0, j; i < M; i = j) {
    int w = edges[idx[i]].w;
    for (j = i; j < M && edges[idx[j]].w == w; j++);
    // 這一組所有同權重的邊
    vector<int> group(idx.begin()+i, idx.begin()+j);

    // 篩出「當前 DSU 下連不同元件」的邊
    vector<int> tempGroup;
    tempGroup.reserve(group.size());
    for (int e : group) {
      if (dsu.find(edges[e].u) != dsu.find(edges[e].v))
        tempGroup.push_back(e);
    }

    if (!tempGroup.empty()) {
      // 建立 contracted graph
      unordered_map<int,int> compMap;
      compMap.reserve(tempGroup.size()*2);
      int cid = 0;
      for (int e : tempGroup) {
        int cu = dsu.find(edges[e].u),
            cv = dsu.find(edges[e].v);
        if (!compMap.count(cu)) compMap[cu] = cid++;
        if (!compMap.count(cv)) compMap[cv] = cid++;
      }
      vector<vector<pair<int,int>>> adj(cid);
      for (int e : tempGroup) {
        int cu = compMap[dsu.find(edges[e].u)],
            cv = compMap[dsu.find(edges[e].v)];
        adj[cu].emplace_back(cv, e);
        adj[cv].emplace_back(cu, e);
      }

      // Tarjan 找橋
      unordered_set<int> bridges;
      bridges.reserve(tempGroup.size());
      vector<int> disc(cid), low(cid);
      vector<bool> vis(cid, false);
      timer = 0;
      for (int v = 0; v < cid; v++) {
        if (!vis[v])
          dfsBridge(v, -1, adj, disc, low, vis, bridges);
      }

      // 分類：橋 → critical，否則 → backup
      for (int e : tempGroup) {
        if (bridges.count(e)) critical.push_back(e);
        else               backup.push_back(e);
      }
    }

    // 最後把這組所有邊都合併進 DSU（保證下一組使用到正確的元件結構）
    for (int e : group)
      dsu.unite(edges[e].u, edges[e].v);
  }

  // 3. 排序、輸出，若空則 no channels
  sort(critical.begin(), critical.end());
  sort(backup.begin(), backup.end());

  if (critical.empty()) {
    cout << "no channels\n";
  } else {
    for (int i = 0; i < (int)critical.size(); i++) {
      cout << critical[i]
           << (i+1 < (int)critical.size() ? ' ' : '\n');
    }
  }

  if (backup.empty()) {
    cout << "no channels\n";
  } else {
    for (int i = 0; i < (int)backup.size(); i++) {
      cout << backup[i]
           << (i+1 < (int)backup.size() ? ' ' : '\n');
    }
  }

  return 0;
}
/*
6 7
0 1 6
1 2 1
2 0 1
2 3 2
3 4 1
4 5 1
3 5 1

3 3
0 1 1
1 2 1 
0 2 1
*/