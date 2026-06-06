#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void depthFirstSearch(int v, vector<vector<pair<int, int>>>& Adj, vector<bool>& isVisited, int minimumWeight)
{
	isVisited[v] = true;

	for (auto [u, w] : Adj[v])
	{
		if (!isVisited[u] && w >= minimumWeight)
		{
			depthFirstSearch(u, Adj, isVisited, minimumWeight);
		}
	}
}

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

		int maximumWeight = 0;

		for (int i = 0; i < M; ++i)
		{
			int v;
			int u;
			int w;

			cin >> v >> u >> w;

			Adj[--v].push_back(make_pair(--u, w));
			Adj[u].push_back(make_pair(v, w));

			maximumWeight = max(maximumWeight, w);
		}

		int S;
		int D;
		int T;

		cin >> S >> D >> T;

		--S;
		--D;

		int lo = 1;
		int hi = maximumWeight;

		while (lo < hi)
		{
			int mid = (lo + hi + 1) / 2;
			
			vector<bool> isVisited(N, false);

			depthFirstSearch(S, Adj, isVisited, mid);

			if (isVisited[D])
			{
				lo = mid;
			}
			else
			{
				hi = mid - 1;
			}
		}

		int minimumNumberOfTrips = ceil((double)T / (lo - 1));

		cout << "Scenario #" << scenarioNumber << endl << "Minimum Number of Trips = " << minimumNumberOfTrips << endl << endl;

		cin >> N >> M;
	}
}
