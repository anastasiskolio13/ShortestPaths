#include <iostream>
#include <vector>
#include <cmath>
#define INF 1e9
using namespace std;

int main()
{
	int N;
	int M;

	cin >> N >> M;

	int scenarioNumber = 0;

	while (N && M)
	{
		++scenarioNumber;

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

		int S;
		int D;
		int T;

		cin >> S >> D >> T;

		--S;
		--D;

		vector<vector<int>> dp(2, vector<int>(N));

		dp[0][D] = INF;

		for (int v = 0; v < N; ++v)
		{
			if (v != D)
			{
				dp[0][v] = -INF;
			}
		}

		for (int i = 1; i < N; ++i)
		{
			for (int v = 0; v < N; ++v)
			{
				dp[i % 2][v] = dp[(i - 1) % 2][v];

				for (auto [u, w] : Adj[v])
				{
					dp[i % 2][v] = max(dp[i % 2][v], min(w, dp[(i - 1) % 2][u]));
				}
			}
		}

		int minimumNumberOfTrips = ceil((double)T / (dp[(N - 1) % 2][S] - 1));

		cout << "Scenario #" << scenarioNumber << endl << "Minimum Number of Trips = " << minimumNumberOfTrips << endl << endl;

		cin >> N >> M;
	}
}