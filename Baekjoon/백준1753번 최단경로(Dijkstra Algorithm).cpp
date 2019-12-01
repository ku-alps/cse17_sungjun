#include <cstdio>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
#include <algorithm>

using namespace std;
const int MAX_V = 20000; // �ִ� ����� ����
const int INF = 1000000000; // ���� ���� �� ���� ��ΰ� 10�� ����
typedef pair<int, int> P;

int main() {
	int V, E, source, target;
	vector<P> adj[MAX_V]; // ���� ����Ʈ 
	scanf("%d %d %d", &V, &E, &source);
	source--;

	for (int i = 0; i<E; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		adj[u - 1].push_back(P(v - 1, w));
		//adj[v - 1].push_back(P(u - 1, w)); ����� �׷����� ��� �ʿ�
	}

	int dist[MAX_V]; // �Ÿ� �迭
	int prev[MAX_V]; // ��� ��� �迭
	fill(dist, dist + MAX_V, INF);
	bool visited[MAX_V] = { 0 }; // �湮 ���� �迭
	priority_queue<P, vector<P>, greater<P>> PQ; // �켱���� ť

												 // ���ͽ�Ʈ�� �˰���
	dist[source] = 0; // ������������ �Ÿ��� 0
	PQ.push(P(0, source)); // �������� PQ�� �ְ� ����
	while (!PQ.empty()) { // PQ�� ��� ����
		int curr;
		do {
			curr = PQ.top().second; // �켱���� ť ������ ���� ª�� �Ÿ��� ������ �����´�
			PQ.pop();
		} while (!PQ.empty() && visited[curr]); // curr�� �湮�� �����̸� ����
												// �� �̻� �湮�� �� �ִ� ������ ������ ����
		if (visited[curr]) break; // �� �̻� �湮�� �� �ִ� ������ ���������� ����

		visited[curr] = true; // �湮
		for (auto &p : adj[curr]) {
			int next = p.first, d = p.second;

			if (dist[next] > dist[curr] + d) { // �Ÿ��� ���ŵ� ��� PQ�� ���� ����
				dist[next] = dist[curr] + d;
				prev[next] = curr;
				PQ.push(P(dist[next], next));
			}
		}
	}

	// ���
	for (int i = 0; i < V; i++) {
		if (dist[i] == INF) puts("INF");
		else printf("%d\n", dist[i]);
	}
}