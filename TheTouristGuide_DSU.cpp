#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <array>
#include <algorithm>
using namespace std;

class DisjointSets
{
private:
	vector<int> P;
	vector<int> S;

public:
	DisjointSets(const int N)
	{
		P.resize(N);
		S.resize(N);
		
		iota(P.begin(), P.end(), 0);
		fill(S.begin(), S.end(), 1);
	}

	int findSet(int a)
	{
		if (P[a] == a)
		{
			return a;
		}
		else
		{
			return P[a] = findSet(P[a]);
		}
	}

	void uniteSets(int a, int b)
	{
		a = findSet(a);
		b = findSet(b);

		if (a == b)
		{
			return;
		}

		if (S[a] < S[b])
		{
			swap(a, b);
		}

		P[b] = a;
		S[a] += S[b];
	}
};

int main()
{
	int N;
	int M;

	cin >> N >> M;

	int scenarioNumber = 0;

	while (N && M)
	{
		++scenarioNumber;

		vector<array<int, 3>> E(M);

		for (int i = 0; i < M; ++i)
		{
			cin >> E[i][0] >> E[i][1] >> E[i][2];

			--E[i][0];
			--E[i][1];
		}

		int S;
		int D;
		int T;

		cin >> S >> D >> T;

		--S;
		--D;

		sort(E.begin(), E.end(), [](const array<int, 3>& edgeOne, const array<int, 3>& edgeTwo) { return edgeOne[2] > edgeTwo[2]; });

		DisjointSets DSU(N);

		for (int i = 0; i < M; ++i)
		{
			DSU.uniteSets(E[i][0], E[i][1]);

			if (DSU.findSet(S) == DSU.findSet(D))
			{
				int minimumNumberOfTrips = ceil((double)T / (E[i][2] - 1));

				cout << "Scenario #" << scenarioNumber << endl << "Minimum Number of Trips = " << minimumNumberOfTrips << endl << endl;

				break;
			}
		}

		cin >> N >> M;
	}
}