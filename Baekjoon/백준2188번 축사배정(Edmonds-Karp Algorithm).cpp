// ������ ī�� �˰��� BFS, ���� ǮĿ�� �˰��� DFS
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int MAX_V = 800;

struct Edge {
	int to, capacity, flow;
	Edge *dual;
	Edge() : Edge(-1, 0) {} 
	Edge(int to, int capacity) : to(to), capacity(capacity), flow(0), dual(nullptr) {}
	int spare() { 
		return capacity - flow;
	}
	void addFlow(int flow) { 
		this->flow += flow;
		dual->flow -= flow;
	}
};

int main() {
	
	int N, M; // N: �� ����, M: ��� ����
	int total = 0, S = 0, T = 0; // total: �� ����, S: �ҽ�, T: ��ũ
	vector<Edge *> adj[MAX_V]; // ���� ����Ʈ
	scanf("%d %d", &N, &M);

	S = 0; // �ҽ� �ε���
	// �ҽ����� �ҷΰ��� �뷮 1�� ���� �߰�
	for (int i = 0; i < N; i++) {
		int u = 0, v = i + 1;
		Edge *e1 = new Edge(v, 1);
		Edge *e2 = new Edge(u, 0);
		e1->dual = e2;
		e2->dual = e1;
		adj[u].push_back(e1);
		adj[v].push_back(e2);
	}

	T = N + M + 1; // ��ũ �ε���
	// ��翡�� ��ũ�ΰ��� �뷮 1�� ���� �߰�
	for (int i = 0; i < M; i++) {
		int u = i + N + 1, v = T;
		Edge *e1 = new Edge(v, 1);
		Edge *e2 = new Edge(u, 0);
		e1->dual = e2;
		e2->dual = e1;
		adj[u].push_back(e1);
		adj[v].push_back(e2);
	}

	// ������ �Է¹޾� �°� ���� ���� �߰�
	for (int i = 0; i < N; i++) {
		int capable_num, barn;
		scanf("%d", &capable_num);
		for (int j = 0; j < capable_num; j++) {
			scanf("%d", &barn);
			int u = i + 1; // �� �ε���
			int v = N + barn; // ������ ��� �ε���
			Edge *e1 = new Edge(v, 1);
			Edge *e2 = new Edge(u, 0);
			e1->dual = e2;
			e2->dual = e1;
			adj[u].push_back(e1);
			adj[v].push_back(e2);
		}
	}

	// �ִ� ���� ���ϱ�
	while (1) {
		Edge *prev[MAX_V] = { NULL }; // ��θ� ����ϱ� ���� prev �迭 ��� 
		queue<int> Q;
		Q.push(S);

		while (!Q.empty() && prev[T] == NULL) { // ť�� ���ְ� ��ũ�� �� ���� ������ �ݺ��Ѵ�, ���� ��θ� BFS�� ã��
			int curr = Q.front();
			Q.pop();
			for (Edge *next : adj[curr]) { // ���� ��忡�� ������ �����鿡 ����
				// next->spare() - 1 >= 0: ���� �������� ���� �������� ������ �긱 ������ ���Ҵ°�?
				// prev[next] == NULL: next->to ������ ���� �湮���� �ʾҴ°�?
				if (next->spare() - 1 >= 0 && prev[next->to] == NULL) {
					Q.push(next->to);
					prev[next->to] = next; // ��θ� ����ϱ� ���� prev �迭 ���
					if (next->to == T) break; // ��ũ�� �����ϸ� ����
				}
			}
		}
		// ��ũ�� ���� ��ΰ� �� ������ ���� Ż��
		if (prev[T] == NULL) break;

		// ��λ󿡼� ���� ���ġ�� ���� ���� ã�� �� ���������� �ʿ� ���� �κ�
		int flow = 100;
		for (int i = T; i != S; i = prev[i]->dual->to) {
			flow = min(flow, prev[i]->spare());
		}
		// ã�� flow��ŭ �ش� ��ο� ���� �����
		for (int i = T; i != S; i = prev[i]->dual->to) {
			prev[i]->addFlow(flow);
			// printf("%d->%d ", prev[i]->to, prev[i]->dual->to);
		}
		// �� ���� �� ����
		total += flow;
	}
	
	printf("%d\n", total);
}

