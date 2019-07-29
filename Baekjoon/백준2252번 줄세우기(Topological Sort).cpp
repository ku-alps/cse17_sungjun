#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int main() {

	int N, M, indegree[32000] = { 0 };
	vector<int> adj[32000]; // ���� ����Ʈ

	scanf("%d %d", &N, &M);

	for (int i = 0; i < M; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		indegree[v - 1]++;
		adj[u - 1].push_back(v - 1);
	}

	// �������� ���� 
	queue<int> Q;
	for (int i = 0; i < N; i++) {  // ������ 0�� ������ ť�� �� �־��ش�
		if (indegree[i] == 0) {
			Q.push(i);
		}
	}

	int result[32000], order = 0;
	while (!Q.empty()) {
		int curr = Q.front();
		result[order] = curr + 1;
		Q.pop();

		for (int next : adj[curr]) {
			indegree[next]--;
			if (indegree[next] == 0) {
				Q.push(next);
			}
		}

		order++;
	}

	for (int i = 0; i < N; i++) {
		printf("%d ", result[i]);
	}
}