#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
	int N, time[500], result[500] = { 0 }, indegree[500] = { 0 };
	vector<int> adj[500];
	queue<int> Q;

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", time + i);
		while (1) {
			int pre;
			scanf("%d", &pre);
			if (pre == -1) break;
			indegree[i]++;
			adj[pre - 1].push_back(i);
		}
		
		if (indegree[i] == 0) { // indegree = 0�� ������ ť�� �־� ��
			result[i] = time[i];
			Q.push(i);
		}
	}

	// ���� ����
	for (int i = 0; i < N; i++) {
		int curr = Q.front();
		Q.pop();
		for (int next : adj[curr]) {
			result[next] = max(result[next], result[curr] + time[next]); // �ּ� �Ǽ� �Ϸ� �ð� ����
			if (--indegree[next] == 0) Q.push(next); // ������ �����Ͽ� next�� indegree�� 0�� �Ǹ� next�� ť�� ����
		}
	}

	for (int i = 0; i < N; i++)
		printf("%d\n", result[i]);
}