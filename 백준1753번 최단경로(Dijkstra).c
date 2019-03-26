#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))

int main() {

	int V = 0, E = 0;
	int s = 0; // ���� �������� ���� ����
	int **weight = NULL; // V * V ����ġ ������� 
	int i = 0, u = 0, v = 0, w = 0;
	int mind = 0;
	int finish = 0;
	int *d = NULL; // ���� ���������� �ִܰŸ�
	int *p = NULL; // 1�̸� ������ 0�̸� �ӽ���

	scanf("%d %d", &V, &E); // ������ ������ ���� �Է�
	scanf("%d", &s); // Ž�� ���� ���� �Է�
	
	weight = (int **)calloc(V + 1, sizeof(int *));
	for (i = 0; i <= V; i++) 
		weight[i] = (int *)calloc(V + 1, sizeof(int));
	
	for (i = 0; i < E; i++) { // �� ������ ����ġ �Է�
		scanf("%d %d %d", &u, &v, &w);
		weight[u][v] = w;
	}
	
	d = (int *)calloc(V + 1, sizeof(int));
	for (i = 1; i <= V; i++)
		d[i] = INT_MAX;
	d[s] = 0;

	p = (int *)calloc(V + 1, sizeof(int));
	p[s] = 1;
	// �ʱ�ȭ �Ϸ�

	while (1) {
		mind = INT_MAX;
		for (i = 1; i <= V; i++) {
			if (weight[s][i] != 0) { // ���� �������� �� �� �ִ� �����̸�
				d[i] = min(d[i], d[s] + weight[s][i]); // ���Ͽ� ���� �Ÿ��� ���Ѵ�.
			}
		}
		for (i = 1; i <= V; i++) { // ������ �ӽ��� �ּҰŸ��� ���� �������� ã�� ���� ��带 �� �������� �ٲپ��ش�.
			if (p[i] == 0 && mind >= d[i]) {
				mind = d[i];
				s = i;
			}
		}
		p[s] = 1;
		for (i = 1; i <= V; i++) { // ��� ������ ���������� Ȯ��
			if (p[i] == 0) {
				finish = 0;
				break;
			}
			else {
				finish = 1;
			}
		}
		if (finish == 1)
			break;
	}

	for (i = 1; i <= V; i++) { // �� ���������� �ִ� �Ÿ� ���
		if (d[i] == INT_MAX)
			printf("INF\n");
		else
			printf("%d\n", d[i]);
	}
}