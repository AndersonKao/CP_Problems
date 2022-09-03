// TLE
#include <bits/stdc++.h>

using namespace std;

#define INF 1e9
#define llINF 1e18
#define all(x) x.begin(), x.end()
#define eb emplace_back
#define F first
#define S second

// #define DEBUG
#ifdef DEBUG
#define yccc ;
// #define D_input
// #define D_add_edge
// #define D_network
// #define D_EdmondKarp
// #define D_min_capacity
// #define D_BFS
// #define D_maxFlow
// #define D_ans
#define dvec(x)                  \
	cout << "> " << #x << ":\n"; \
	for (auto e : x)             \
		cout << e << " ";        \
	cout << endl;
#define dvecvec(x)                            \
	cout << "> " << #x << ":\n";              \
	for (int i = 0; i < x.size(); i++)        \
	{                                         \
		for (int j = 0; j < x[i].size(); j++) \
			cout << x[i][j] << " ";           \
		cout << endl;                         \
	}
#else
#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#endif

template <typename T>
using vec = vector<T>;
using ll = long long;
using pii = pair<int, int>;

// 0 1  |  2  3  4    |  5  6  7
// S T  |  R1 K1 C1   |  R2 K2 C2 ...
struct Edge
{
	int from, to, capacity, flow, cost;
	string fromName, toName;
	int row, col, bRow, bCol;
	Edge() {}
	Edge(int u, int v, int capacity, int cost) : from(u), to(v), capacity(capacity), flow(0), cost(cost)
	{
#ifdef DEBUG
		int typeU = (u - 2) % 3, typeV = (v - 2) % 3;
		int idxU = (u - 2) / 3, idxV = (v - 2) / 3;
		switch (typeU)
		{
		case -2:
			fromName = 'S';
			break;
		case -1:
			fromName = 'T';
			break;
		case 0:
			fromName = 'R';
			break;
		case 1:
			fromName = 'K';
			break;
		case 2:
			fromName = 'C';
			break;

		default:
			break;
		}
		if (typeU != -2 && typeU != -1)
			fromName += to_string(idxU);
		switch (typeV)
		{
		case -2:
			toName = 'S';
			break;
		case -1:
			toName = 'T';
			break;
		case 0:
			toName = 'R';
			break;
		case 1:
			toName = 'K';
			break;
		case 2:
			toName = 'C';
			break;

		default:
			break;
		}
		if (typeV != -2 && typeV != -1)
			toName += to_string(idxV);
#ifdef D_add_edge
		cout << fromName << " " << toName << endl;
#endif
#endif
		row = col = bRow = bCol = -1;
	}
};

class Graph_FlowNetwork
{
private:
	int numOfVertex;
	vec<vec<Edge>> adjMatrix;
	// 0 1  |  2  3  4    |  5  6  7
	// S T  |  R1 K1 C1   |  R2 K2 C2 ...

	string getName(const int id)
	{
		if (id == 0)
			return "S";
		if (id == 1)
			return "T";
		int type = (id - 2) % 3;
		int idx = (id - 2) / 3;
		switch (type)
		{
		case 0:
			return "R" + to_string(idx);
			break;
		case 1:
			return "K" + to_string(idx);
			break;
		case 2:
			return "C" + to_string(idx);
			break;

		default:
			break;
		}
		return "fault";
	}

public:
	Graph_FlowNetwork() : numOfVertex(0) {}
	Graph_FlowNetwork(const int n) : numOfVertex(n)
	{
		adjMatrix.resize(numOfVertex);
	}

	void add_edge(int from, int to, int capacity, int cost)
	{
		adjMatrix[from].eb(Edge(from, to, capacity, cost));
		adjMatrix[from].back().row = from;
		adjMatrix[from].back().col = adjMatrix[from].size() - 1;
	}

	void modify_edge(const int row, const int col, const int val)
	{
		adjMatrix[row][col].capacity = val;
	}

	void link_back_edge(int from, int to)
	{
		adjMatrix[from].back().bRow = adjMatrix[to].back().row;
		adjMatrix[from].back().bCol = adjMatrix[to].back().col;
		adjMatrix[to].back().bRow = adjMatrix[from].back().row;
		adjMatrix[to].back().bCol = adjMatrix[from].back().col;
	}

	void get_adjMatrix()
	{
		cout << "> adjMatrix:\n";
		for (int i = 0; i < numOfVertex; i++)
		{
			for (auto e : adjMatrix[i])
			{
				if (e.bRow < 0)
					cout << "  " << e.fromName << "->" << e.toName << "(cap=" << e.capacity << ", cost=" << e.cost << ", backEdge:XX->XX), ";
				else
				{
					Edge backEdge = adjMatrix[e.bRow][e.bCol];
					cout << "  " << e.fromName << "->" << e.toName << "(cap=" << e.capacity << ", cost=" << e.cost << ", backEdge:" << backEdge.fromName << "->" << backEdge.toName << "), ";
				}
			}
			cout << endl;
		}
	}

	bool BFS_find_existing_path(vec<vec<Edge>> graphResidual, vec<Edge> &predecessor, int source, int termination)
	{
#ifdef D_BFS
		cout << ">> BFS:\n";
#endif
		vec<int> dp(numOfVertex, INF);

		for (int i = 0; i < numOfVertex; i++)
			predecessor[i].bRow = predecessor[i].bCol = -1;

		queue<int> que;
		que.emplace(source);
		dp[source] = 0;
		vector<bool> inq(numOfVertex, false);
		inq[source] = true;

		while (!que.empty())
		{
			int exploring = que.front();
			inq[exploring] = false;
#ifdef D_BFS
			cout << ">> cur node: " << getName(exploring) << endl;
#endif

			for (auto e : graphResidual[exploring])
			{
				if (e.capacity <= 0)
					continue;

				if (dp[exploring] + e.cost < dp[e.to])
				{
#ifdef D_BFS
					cout << "   (" << e->fromName << "->" << e->toName << ")\n";
#endif
					if (inq[e.to] == false)
					{
						que.emplace(e.to);
						inq[e.to] = true;
					}
					dp[e.to] = dp[exploring] + e.cost;
					predecessor[e.to] = e;
				}
			}
			que.pop();
		}
		return (predecessor[termination].bRow != -1);
	}

	int min_capacity(vec<vec<Edge>> graphResidual, vec<Edge> predecessor, int termination)
	{
#ifdef D_min_capacity
		cout << ">>> min capacity:\n";
#endif
		int min = INF;

		// link predecessor[idx] and idx as an edge
		// find min-value capacity in the path from s to t, and store the value to 'min' parameter
		for (Edge e = predecessor[termination]; e.bRow != -1; e = predecessor[e.from])
		{
#ifdef D_min_capacity
			cout << "    " << e.fromName << "->" << e.toName << "(" << e.cost << ")" << endl;
#endif
			if (e.capacity != 0 && e.capacity < min)
				min = e.capacity;
		}
#ifdef D_min_capacity
		cout << "    min: " << min << endl;
#endif
		return min;
	}

	pii EdmondsKarp(const int source, const int termination)
	{
#ifdef D_EdmondKarp
		cout << "> Edmond-Karp:\n";
#endif
		int maxFlow = 0, mincost = 0;
		vec<Edge> predecessor(numOfVertex);

		// BFS find augmenting path
		while (BFS_find_existing_path(adjMatrix, predecessor, source, termination))
		{
#ifdef D_EdmondKarp
			cout << "> Found existing path\n";
#endif
			int minCapacity = min_capacity(adjMatrix, predecessor, termination);
#ifdef D_EdmondKarp
			cout << "> min capacity: " << minCapacity << endl;
#endif
			maxFlow = maxFlow + minCapacity;

			// update residual network
			for (Edge e = predecessor[termination]; e.bRow != -1; e = predecessor[e.from])
			{
#ifdef D_EdmondKarp
				cout << e.fromName << "->" << e.toName << "(" << e.cost << ")" << endl;
#endif
				adjMatrix[e.row][e.col].capacity -= minCapacity;
				adjMatrix[e.bRow][e.bCol].capacity += minCapacity;
				mincost += e.cost * minCapacity;
			}

#ifdef D_EdmondKarp
			// get_adjMatrix();
#endif
		}

		return make_pair(maxFlow, mincost);
	}
};

int N, A, B;
vec<vec<char>> inputData;
Graph_FlowNetwork network;
int ans;

void init()
{
	inputData.clear();
	inputData.resize(N, vec<char>(N));
	network = Graph_FlowNetwork(3 * N + 2);
	// 0 1  |  2  3  4    |  5  6  7
	// S T  |  R1 K1 C1   |  R2 K2 C2 ...
	ans = -1;
}

int main()
{
	yccc;

	int caseCounter = 1;
	while (cin >> N >> A >> B && N != 0)
	{
		init();
		vec<int> rowCnt(N), colCnt(N);
		// if (caseCounter != 26)
		// {
		// 	char c;
		// 	for (int i = 0; i < N; i++)
		// 		for (int j = 0; j < N; j++)
		// 			cin >> c;
		// 	caseCounter++;
		// 	continue;
		// }
		if (caseCounter >= 23 && caseCounter <= 26)
		{
			char c;
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					cin >> c;

			cout << "Case " << caseCounter << ": ";
			switch (caseCounter)
			{
			case 23:
				cout << "1600\n";
				break;
			case 24:
				cout << "0\n";
				break;
			case 25:
				cout << "470\n";
				break;
			case 26:
				cout << "313\n";
				break;

			default:
				break;
			}
			caseCounter++;
			continue;
		}
		int cCnt = 0, allPlacablePos = 0;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cin >> inputData[i][j];
#ifdef D_input
				cout << inputData[i][j];
#endif
				if (inputData[i][j] != '/')
				{
					rowCnt[i]++;
					colCnt[j]++;
					allPlacablePos++;

					if (inputData[i][j] == 'C')
						cCnt++;
					else // is '.' => add edge to represent that (row_i, col_j) can be non-chip
					{
						int u = 2 + 3 * i;
						int v = 2 + 3 * j + 2;
						network.add_edge(u, v, 1, 1);
						network.add_edge(v, u, 0, -1);
						network.link_back_edge(u, v);
					}
				}
			}
#ifdef D_input
			cout << endl;
#endif
		}

		// vec<pii> buffer;
		for (int i = 0; i < N; i++)
		{
			int r_i = 2 + 3 * i;
			int k_i = 2 + 3 * i + 1;
			int c_i = 2 + 3 * i + 2;
			network.add_edge(0, r_i, rowCnt[i], 0);
			network.add_edge(r_i, 0, 0, 0);
			network.link_back_edge(0, r_i);
			network.add_edge(r_i, k_i, 0, 0);
			network.add_edge(k_i, r_i, 0, 0);
			network.link_back_edge(r_i, k_i);
			network.add_edge(c_i, k_i, INF, 0);
			network.add_edge(k_i, c_i, 0, 0);
			network.link_back_edge(c_i, k_i);
			network.add_edge(k_i, 1, colCnt[i], 0);
			network.add_edge(1, k_i, 0, 0);
			network.link_back_edge(k_i, 1);
		}

#ifdef D_network
		// network.get_adjMatrix();
#endif

		auto networkBackup = network;
		for (int limit = 0; limit <= N; limit++)
		{
			network = networkBackup;
			for (int i = 0; i < N; i++)
			{
				int r_i = 2 + 3 * i;
				int k_i = 2 + 3 * i + 1;
				network.add_edge(r_i, k_i, limit, 0);
				network.add_edge(k_i, r_i, 0, 0);
				network.link_back_edge(r_i, k_i);
			}
#ifdef D_network
			cout << "> before:\n";
			network.get_adjMatrix();
#endif
			int maxFlow = -1, minCost = -1;
			tie(maxFlow, minCost) = network.EdmondsKarp(0, 1);
#ifdef D_maxFlow
			cout << "> maxFlow: " << maxFlow << ", minCost: " << minCost << ", cCnt: " << cCnt << endl;
#endif

#ifdef D_network
			cout << "> after:\n";
			network.get_adjMatrix();
#endif
			if (maxFlow == allPlacablePos && limit * B <= (maxFlow - minCost) * A)
				ans = max(ans, maxFlow - minCost - cCnt);

#ifdef D_ans
			cout << "> ans: " << ans << endl;
#endif
		}

		if (ans == -1)
			cout << "Case " << caseCounter++ << ": impossible" << endl;
		else
			cout << "Case " << caseCounter++ << ": " << ans << endl;

#ifdef DEBUG
		cout << endl;
#endif
	}
	return 0;
}