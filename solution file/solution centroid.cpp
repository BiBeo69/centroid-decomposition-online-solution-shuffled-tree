#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;
#define f first
#define s second
#define pb push_back
typedef pair<int, int> pii;
typedef pair<int, ll> pil;
const int N = 150001;
const int MAXN = 1e5+69;
int n, m, q, x[N]; //x[v] is rank of node v
vector<pii> adj[N];
vector<int> ADJ[MAXN],NEAR[MAXN];
int per[N];
bool vis[N];
int sz[N];
int ctp[N];
int dpth[N];
int L[N];
int R[N];
int cur_pos[20];
int dis[N][20];
pil psa[20][N];
int wei[N];
int TIME;
int RR[2*MAXN][20],W[MAXN],S[MAXN],H[MAXN],BRUH;
int VAL[MAXN],ST[MAXN],EN[MAXN],CH[MAXN],TOUR[MAXN];
int po[MAXN];
bool HL(int A,int B){
    return S[A] > S[B];
}
void DFS(int NODE,int PA){
    BRUH++;
    RR[BRUH][0] = NODE,W[NODE] = BRUH;
    S[NODE] = 1;
    for(auto KO : ADJ[NODE]){
        if(KO != PA){
            po[KO] = NODE;
            H[KO] = H[NODE] + 1;
            NEAR[NODE].pb(KO);
            DFS(KO,NODE);
            BRUH++;
            S[NODE] += S[KO];
            RR[BRUH][0] = NODE;
        }
    }
}
int LCA(int u,int v){
    int l = W[u], r = W[v];
    if(l > r) swap(l,r);
    int k = 31 - __builtin_clz(r - l + 1);
    return (H[RR[l][k]] < H[RR[r - (1 << k) + 1][k]] ? RR[l][k] : RR[r - (1 << k) + 1][k]);
}
void HLD(int NODE){
    TIME++;
    ST[NODE] = EN[NODE] = TIME;
    TOUR[TIME] = NODE;
    int NEX = 0;
    for(auto KO : NEAR[NODE]){
        if(KO == NEAR[NODE][0]) CH[KO] = CH[NODE];
        else CH[KO] = KO;
        HLD(KO);
        EN[NODE] = TIME;
    }
}
void SPARSE(){
    for(int k = 0; (1 << (k + 1)) <= BRUH; ++k) {
    	for(int i = 1; i + (1 << (k + 1)) - 1 <= BRUH; ++i) {
    		RR[i][k + 1] = (H[RR[i][k]] < H[RR[i + (1 << k)][k]] ? RR[i][k] : RR[i + (1 << k)][k]);
    	}
    }
}
void DFS1(int v, int p){
    sz[v] = 1;
    for (pii u : adj[v]){
        if (u.s != p && !vis[u.s]){
            DFS1(u.s, v);
            sz[v] += sz[u.s];
        }
    }
}
int find(int v, int p, int s) {
    for (pii u : adj[v])
        if (u.s != p && !vis[u.s] && sz[u.s] > s) return find(u.s, v, s);
    return v;
}
void DFS2(int v, int p, int r, int d) {
    dis[v][dpth[r]] = d;
    ++cur_pos[dpth[r]];
    psa[dpth[r]][cur_pos[dpth[r]]] = {x[v], d};
    if (dpth[r] > 0){
            psa[dpth[r]][cur_pos[dpth[r]]].s -= dis[v][dpth[r] - 1];
            //cout << v << " " << r << " " << dpth[r] << " sus\n";
            //cout << psa[dpth[r]][cur_pos[dpth[r]]].s << " nig\n";
    }
    for (pii u : adj[v])
        if (u.s != p && !vis[u.s]){
            wei[u.s] = u.f;
            DFS2(u.s, v, r, d + u.f);
        }
}
void decomp(int v, int p, int d) {
    DFS1(v, 0);
    v = find(v, 0, sz[v]>>1);
    ctp[v] = p;
    dpth[v] = d;
    vis[v] = true;
    L[v] = cur_pos[d] + 1;
    DFS2(v, 0, v, 0);
    //cout << wei[v] << " centroid\n";
    R[v] = cur_pos[d];
    sort(psa[d] + L[v], psa[d] + R[v] + 1);
    for (int i = L[v]; i <= R[v]; ++i) psa[d][i].s += psa[d][i - 1].s;
    for (pii u : adj[v])
        if (!vis[u.s]) decomp(u.s, v, d + 1);
}
int bs(pil p[], int lo, int hi, int val) {
    while (lo < hi) {
        int mid = (lo + hi)>>1;
        if (p[mid].f >= val) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}
ll query(int v, int mn, int mx) {
    ll ret = 0, num = 0;
    for (int u = v; u != 0; u = ctp[u]) {
        int qL = bs(psa[dpth[u]], L[u], R[u] + 1, mn), qR = bs(psa[dpth[u]], L[u], R[u] + 1, mx + 1) - 1;
        ret += psa[dpth[u]][qR].s - psa[dpth[u]][qL - 1].s + (qR - qL + 1 - num)*dis[v][dpth[u]];
        num = qR - qL + 1;
    }
    return ret;
}
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l, int r){
    return uniform_int_distribution<int>(l, r)(rng);
}
main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    int liz = 5555;
//map<int,int> viz;
    for (int i = 1; i <= n; ++i){
        cin >> per[i];
    }
    for (int i = 1, u, v, d; i < n; ++i) {
        cin >> u >> v >> d;
        int U = u,V = v;
        //d = rand(1,1000);
//infile << u << " " << v << " " << d << '\n';
        adj[u].push_back({d, v});
        adj[v].push_back({d, u});
        ADJ[U].pb(V);
        ADJ[V].pb(U);
    }
     H[1] = 1;
    DFS(1,0);
    SPARSE();
    for(int i = 1; i <= n ; i++) sort(NEAR[i].begin(),NEAR[i].end(),HL);
    HLD(1);
    CH[1] = 1;
    for(int i = 1; i <= n ; i++) x[i] = ST[per[i]];
    decomp(1, 0, 0);

    ll ans = 0, v0, mn0, mx0;
    for (int i = 1; i <= q; ++i){
        cin >> mn0 >> mx0 >> v0;
        //mn0 = rand(1,n-1),mx0 = rand(mn0+1,n);
        //v0 = rand(1,n);
        //infile << mn0 << " " << mx0 << " " << v0 << '\n';
        int U = mn0,V = mx0;
        int u = U,v = V;
            long long ANS = 0;
            int COM = LCA(U,V);
            while(H[u] >= H[COM]){
                if(H[CH[u]] >= H[COM]) ANS += (query(v0,ST[CH[u]],ST[u]));
                else ANS += query(v0,ST[COM],ST[u]);
                u = po[CH[u]];
            }
            while(H[v] >= H[COM]){
                if(H[CH[v]] >= H[COM]) ANS += (query(v0,ST[CH[v]],ST[v]));
                else ANS += query(v0,ST[COM],ST[v]);
                v = po[CH[v]];
            }
            ANS -= query(v0,ST[COM],ST[COM]);
            cout << ANS << '\n';
    }
}