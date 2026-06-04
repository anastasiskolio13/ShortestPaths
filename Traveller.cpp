#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#define INF 1e16
using namespace std;

int main()
{
	int N;
	int M;
	int K;

	cin >> N >> M >> K;

	vector<vector<pair<int, int>>> Adj(N);

	for (int i = 0; i < M; ++i)
	{
		int v;
		int u;
		int w;

		cin >> v >> u >> w;

		Adj[--v].push_back(make_pair(--u, w));
		Adj[u].push_back(make_pair(v, w));
	}

	// Υποπροβλήματα 2, 3.
	if (N > 1000)
	{
		vector<long long> dp(N);
		vector<int> parent(N);

		set<pair<long long, int>> Q;

		for (int v = 1; v < N; ++v)
		{
			dp[v] = INF;

			Q.insert(make_pair(dp[v], v));
		}

		dp[0] = 0;

		Q.insert(make_pair(dp[0], 0));

		for (int i = 0; i < N - 1; ++i)
		{
			auto [_, v] = *Q.begin();
			Q.erase(Q.begin());

			for (auto [u, w] : Adj[v])
			{
				if (dp[v] + w < dp[u])
				{
					Q.erase(make_pair(dp[u], u));

					dp[u] = dp[v] + w;

					Q.insert(make_pair(dp[u], u));

					parent[u] = v;
				}
			}
		}

		cout << dp[N - 1] / 2 << endl;

		vector<int> path;

		int v = N - 1;

		while (v)
		{
			path.push_back(v + 1);

			v = parent[v];
		}

		path.push_back(1);

		reverse(path.begin(), path.end());

		cout << path.size() << endl;

		for (int v : path)
		{
			cout << v << " ";
		}

		return 0;
	}

	// Υποπροβλήματα 1, 4.
	vector<vector<long long>> dp(K + N, vector<long long>(N));
	vector<vector<int>> parent(K + N, vector<int>(N));

	dp[0][0] = 0;

	for (int v = 1; v < N; ++v)
	{
		dp[0][v] = INF;
	}

	for (int i = 1; i <= K + N - 1; ++i)
	{
		for (int v = 0; v < N; ++v)
		{
			dp[i][v] = INF;

			for (auto [u, w] : Adj[v])
			{
				if (dp[i - 1][u] + w < dp[i][v])
				{
					dp[i][v] = dp[i - 1][u] + w;
					parent[i][v] = u;
				}
			}
		}
	}

	long long minimumCostWithoutTheDiscount = INF;
	int numberOfEdgesTraversedWithoutTheDiscount;

	for (int i = 1; i < N; ++i)
	{
		if (dp[i][N - 1] < minimumCostWithoutTheDiscount)
		{
			minimumCostWithoutTheDiscount = dp[i][N - 1];
			numberOfEdgesTraversedWithoutTheDiscount = i;

		}
	}

	long long minimumCostWithTheDiscount = INF;
	int numberOfEdgesTraversedWithTheDiscount;

	for (int i = K; i <= K + N - 1; ++i)
	{
		if (dp[i][N - 1] < minimumCostWithTheDiscount)
		{
			minimumCostWithTheDiscount = dp[i][N - 1];
			numberOfEdgesTraversedWithTheDiscount = i;
		}
	}

	vector<int> path;

	int i;

	if (minimumCostWithoutTheDiscount < minimumCostWithTheDiscount / 2)
	{
		cout << minimumCostWithoutTheDiscount << endl;

		i = numberOfEdgesTraversedWithoutTheDiscount;
	}
	else
	{
		cout << minimumCostWithTheDiscount / 2 << endl;

		i = numberOfEdgesTraversedWithTheDiscount;
	}

	int v = N - 1;

	while (i > 0)
	{
		path.push_back(v + 1);

		v = parent[i--][v];
	}
	
	path.push_back(1);
	
	cout << path.size() << endl;

	reverse(path.begin(), path.end());
	
	for (int v : path)
	{
		cout << v << " ";
	}
}