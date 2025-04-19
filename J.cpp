#include <bits/stdc++.h>
using namespace std;
using u32 = uint32_t;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, k1, k2;
    cin >> N >> k1 >> k2;
    vector<u32> A(N), B(N);
    for(int i = 0; i < N; i++) cin >> A[i];
    for(int i = 0; i < N; i++) cin >> B[i];

    // Build difference constraints
    vector<u32> Da(N), Db(N);
    for(int i = 0; i < N; i++){
        int ni = (i+1 == N ? 0 : i+1);
        Da[i] = A[i] ^ A[ni];
        Db[i] = B[i] ^ B[ni];
    }

    // Graph-BFS to satisfy C[i] ^ C[i+k1] = Da[i] and C[i] ^ C[i+k2] = Db[i]
    vector<char> vis(N, 0);
    vector<u32> C(N, 0);
    for(int start = 0; start < N; start++){
        if(vis[start]) continue;
        queue<int> q;
        vis[start] = 1;
        C[start] = 0;
        q.push(start);
        while(!q.empty()){
            int u = q.front(); q.pop();
            // k1-forward
            int v = u + k1; if(v >= N) v -= N;
            if(!vis[v]){
                vis[v] = 1;
                C[v] = C[u] ^ Da[u];
                q.push(v);
            }
            // k1-backward
            v = u - k1; if(v < 0) v += N;
            if(!vis[v]){
                vis[v] = 1;
                C[v] = C[u] ^ Da[v];
                q.push(v);
            }
            // k2-forward
            v = u + k2; if(v >= N) v -= N;
            if(!vis[v]){
                vis[v] = 1;
                C[v] = C[u] ^ Db[u];
                q.push(v);
            }
            // k2-backward
            v = u - k2; if(v < 0) v += N;
            if(!vis[v]){
                vis[v] = 1;
                C[v] = C[u] ^ Db[v];
                q.push(v);
            }
        }
    }

    // Absolute-window adjustment
    int g = gcd(gcd(N, k1), k2);
    // Raw window XORs from C
    u32 A0p = 0, B0p = 0;
    for(int i = 0; i < k1; i++) A0p ^= C[i];
    for(int i = 0; i < k2; i++) B0p ^= C[i];
    u32 dA = A0p ^ A[0];
    u32 dB = B0p ^ B[0];
    bool m1 = ((k1/g) & 1);
    bool m2 = ((k2/g) & 1);

    // Choose fix for residue-0 class
    u32 fix;
    if(m1) fix = dA;
    else if(m2) fix = dB;
    else fix = C[0] ^ A[0];

    for(int i = 0; i < N; i += g) C[i] ^= fix;

    // Output result
    for(int i = 0; i < N; i++){
        cout << C[i] << (i+1 < N ? ' ' : '\n');
    }
    return 0;
}
