#include <iostream>
#include <cstring>

int N, result;
int queen(int chess[], int line, int possible);

int main() {

	int *chess;
	scanf("%d", &N);

	chess = new int[N] {}; // ���κ� ���� ��ġ�� ���� �迭
	for (int i = 0; i < N; i++) {
		chess[i] = -1;
	}
	printf("%d\n", queen(chess, 0, 1));

}

int queen(int chess[], int line, int possible) { // ���° line�� üũ������

	if (possible == 0) {
		return 0;
	}
	if (line == N) {
		result++;
		return 1;
	}

	for (int i = 0; i < N; i++) { // i�� ���� ��ġ�� �ǹ��Ѵ�
		for (int j = 0; j < line; j++) { // i���� ��ġ�� �� �� �ִ��� ���� ������ ���� Ȯ��
			if (i == chess[j])
				possible = 0;
			if ((i == chess[j] - (line - j)) || (i == chess[j] + (line - j)))
				possible = 0;
		}
		chess[line] = i;
		queen(chess, line + 1, possible);
		possible = 1;
	}

	return result;
}