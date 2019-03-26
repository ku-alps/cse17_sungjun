#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int MAX_N = 200;
const int MAX_V = MAX_N * 2 + 2;
const int S = MAX_V - 2;
const int E = MAX_V - 1;

int main() {
	// �� ������ 0 ~ MAX_N-1, ��� ������ MAX_N ~ MAX_N*2-1 �� ������ ����
	int N, M, c[MAX_V][MAX_V] = { 0 }, f[MAX_V][MAX_V] = { 0 };
	vector<int> adj[MAX_V];
	scanf("%d %d", &N, &M);
	for (int i = 0; i<N; i++) {
		int K;
		scanf("%d", &K);
		for (int k = 0; k<K; k++) {
			int j;
			scanf("%d", &j);
			j = MAX_N + j - 1;
			// ������ ���� �߰�
			c[i][j] = 1;
			adj[i].push_back(j);
			adj[j].push_back(i);
		}
		// ���������� �� �������� ���� ��
		c[S][i] = 1;
		adj[S].push_back(i);
		adj[i].push_back(S);
	}
	for (int i = MAX_N; i<MAX_N + M; i++) {
		// ��� �������� ���������� ���� ��
		c[i][E] = 1;
		adj[i].push_back(E);
		adj[E].push_back(i);
	}

	int total = 0;

	while (1) {
		// BFS�� ���� ��� ã��
		int prev[MAX_V];
		fill(prev, prev + MAX_V, -1);
		queue<int> Q;
		Q.push(S);
		while (!Q.empty()) {
			int curr = Q.front();
			Q.pop();
			for (int next : adj[curr]) {
				// c[i][j]-f[i][j] > 0: i���� j�� ������ �긱 ������ ���Ҵ°�?
				// prev[next] == -1: next ������ ���� �湮���� �ʾҴ°�?
				if (c[curr][next] - f[curr][next] > 0 && prev[next] == -1) {
					Q.push(next);
					prev[next] = curr; // ��θ� ����ϱ� ���� prev �迭 ���
					if (next == E) break; // ��ũ�� �����ϸ� ����
				}
			}
		}
		// ��ũ�� ���� ��ΰ� �� ������ ���� Ż��
		if (prev[E] == -1) break; 

			// �Ź� �긮�� ������ �ݵ�� 1�̹Ƿ� ���� ���� �� ���ص� ��
			for (int i = E; i != S; i = prev[i]) {
				f[prev[i]][i]++;
				f[i][prev[i]]--;
			}
		total++;
	}
	printf("%d\n", total);
}