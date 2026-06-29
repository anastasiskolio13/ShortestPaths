#include <iostream>
#include <vector>
#include <set>
#define INF 2e9
using namespace std;

vector<int> Dijkstra(int s, const vector<vector<pair<int, int>>>& Adj)
{
    vector<int> D(Adj.size());
    set<pair<int, int>> Q;

    for (int v = 0; v < Adj.size(); ++v)
    {
        if (v != s)
        {
            D[v] = INF;
            Q.insert(make_pair(D[v], v));
        }
    }

    D[s] = 0;
    Q.insert(make_pair(D[s], s));

    for (int i = 0; i < Adj.size() - 1; ++i)
    {
        auto [_, v] = *Q.begin();
        Q.erase(Q.begin());

        for (auto [u, w] : Adj[v])
        {
            if (D[v] + w < D[u])
            {
                Q.erase(make_pair(D[u], u));
                D[u] = D[v] + w;
                Q.insert(make_pair(D[u], u));
            }
        }
    }

    return D;
}

int main()
{
    int N;
    int M;
    int K;
    int s;
    int t;

    cin >> N >> M >> K >> s >> t;

    --s;
    --t;

    vector<vector<pair<int, int>>> Adj(N);
    vector<vector<pair<int, int>>> AdjR(N);

    for (int i = 0; i < M; ++i)
    {
        int v;
        int u;
        int w;

        cin >> v >> u >> w;

        Adj[--v].push_back(make_pair(--u, w));
        AdjR[u].push_back(make_pair(v, w));
    }

    vector<int> D = Dijkstra(s, Adj);
    vector<int> DR = Dijkstra(t, AdjR);

    int ans = D[t];

    for (int i = 0; i < K; ++i)
    {
        int v;
        int u;
        int w;

        cin >> v >> u >> w;

        ans = min((long)ans, (long)D[--v] + w + DR[--u]);
    }

    cout << ans << endl;
}