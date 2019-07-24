#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int main() {
	int N, M, indegree[1000] = { 0 }; // N�� 1000���� �ڿ���, M�� 100���� �ڿ���
	vector<int> adj[1000];

	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++) {
		int num, prev, curr;
		scanf("%d", &num);
		if (num == 0) continue;

		scanf("%d", &prev);
		for (int i = 1; i < num; i++) {
			scanf("%d", &curr);
			indegree[curr - 1]++; // ������ ���� ����
			adj[prev - 1].push_back(curr - 1); // �������
			prev = curr;
		}
	}

	int result[1000];
	queue<int> Q;
	// ���� ���� ����: ť�� indegree�� 0�� ������ �� ����
	for (int i = 0; i < N; i++) {
		if (indegree[i] == 0) {
			Q.push(i);
		}
	}

	// ���� ����
	for (int i = 0;  i < N; i++) {
		if (Q.empty()) { // ���߿� ť�� ��� ����Ŭ�� �ִ°����� �Ұ���
			puts("0");
			return 0;
		}

		int curr = Q.front();
		Q.pop();
		result[i] = curr + 1;
		// ������ ������ ��ȸ�ϸ鼭 indegree 1�� ����. 0�� �Ǹ� ť�� ����
		for (int next : adj[curr])
			if (--indegree[next] == 0) {
				Q.push(next);
			}
	} // ���߿� ť�� ũ�Ⱑ 2�̻��ΰ��� ���� �������� ���� �� ������ �ǹ�

	// ��� ���
	for (int i = 0; i < N; i++) {
		printf("%d\n", result[i]);
	}
}