#include <iostream>
using namespace std;

bool num[10][10][10] = {};

int main() {

	int N, strike, ball, result = 0;
	scanf("%d", &N);

	for (int i = 1; i < 10; i++) {
		for (int j = 1; j < 10; j++) {
			for (int k = 1; k < 10; k++) {
				num[i][j][k] = true;
				if (i == j || i == k || j == k) { // ���ڰ� �ѽ��̶� �ߺ��Ǹ� false
					num[i][j][k] = false;
				}
			}
		}
	}

	for (int n = 0; n < N; n++) {
		int i, j, k, guess;
		scanf("%d %d %d", &guess, &strike, &ball);
		i = guess / 100;
		j = (guess % 100) / 10;
		k = guess % 10;
		if (strike == 3) { // �ϳ��� �ٸ��� false
			for (int a = 1; a < 10; a++) {
				for (int b = 1; b < 10; b++) {
					for (int c = 1; c < 10; c++) {
						if (a != i || b != j || c != k) {
							num[a][b][c] = false;
						}
					}
				}
			}
		}
		else if (strike == 2 && ball == 0) { // 2���� �ٸ����� 3���� �ٸ����, ��δ� ������� false
			for (int a = 1; a < 10; a++) {
				for (int b = 1; b < 10; b++) {
					for (int c = 1; c < 10; c++) {
						if (a != i && b != j) {
							num[a][b][c] = false;
						}
						if (c != k && b != j) {
							num[a][b][c] = false;
						}
						if (a != i && c != k) {
							num[a][b][c] = false;
						}
						if (a == i && b == j && c == k) {
							num[a][b][c] = false;
						}
					}
				}
			}
		}
		else if (strike == 1 && ball == 0) { // 2���� ���ų� 3���� ���ų� 3���� �ٸ���� false
			for (int a = 1; a < 10; a++) {
				for (int b = 1; b < 10; b++) {
					for (int c = 1; c < 10; c++) {
						if (a == i && (b != j && b != k) && (c != j && c != k)) {
							continue;
						}
						if (b == j && (a != i && a != k) && (c != i && c != k)) {
							continue;
						}
						if (c == k && (b != j && b != i) && (a != i && a != j)) {
							continue;
						}
						num[a][b][c] = false;			
					}
				}
			}
		}
		else if (strike == 0 && ball == 0) { // i j k�� ���ڰ� ���� ������ false
			for (int a = 1; a < 10; a++) {
				for (int b = 1; b < 10; b++) {
					for (int c = 1; c < 10; c++) {
						if (a == i || a == j || a == k || b == i || b == j || b == k || c == i || c == j || c == k) {
							num[a][b][c] = false;
						}
					}
				}
			}
		}
		else if (strike == 0 && ball == 1) { // �ϳ��� ��Ʈ����ũ�ų� 2�� 3���ΰ�� �Ǵ� �ƿ��� ��� false
			for (int a = 1; a < 10; a++) {
				for (int b = 1; b < 10; b++) {
					for (int c = 1; c < 10; c++) {
						if (a == i || b == j || c == k) {
							num[a][b][c] = false;
						}
						if ((a == j || a == k) && (b == i || b == k)) {
							num[a][b][c] = false;
						}
						if ((c == i || c == j) && (b == i || b == k)) {
							num[a][b][c] = false;
						}
						if ((a == j || a == k) && (c == i || c == j)) {
							num[a][b][c] = false;
						}
						if ((a != j && a != k) && (b != i && b != k) && (c != i && c != j)) {
							num[a][b][c] = false;
						}
					}
				}
			}
		}
		else if (strike == 0 && ball == 2) { // �ϳ��� ��Ʈ����ũ�ų� 1�� 3�� �ƿ��ΰ�� false
			for (int a = 1; a < 10; a++) {
				for (int b = 1; b < 10; b++) {
					for (int c = 1; c < 10; c++) {
						if (a == i || b == j || c == k) {
							num[a][b][c] = false;
						}
						if ((a == j || a == k) && (b == i || b == k) && (c == i || c == j)) { // 3���� ���
							num[a][b][c] = false;
						}
						if ((a == j || a == k) && (b != i && b != k) && (c != i && c != j)) { // 1���� ���
							num[a][b][c] = false;
						}
						if ((b == i || b == k) && (a != j && a != k) && (c != i && c != j)) { // 1���� ���
							num[a][b][c] = false;
						}
						if ((c == i || c == j) && (b != i && b != k) && (a != j && a != k)) { // 1���� ���
							num[a][b][c] = false;
						}
						if ((a != j && a != k) && (b != i && b != k) && (c != i && c != j)) {
							num[a][b][c] = false;
						}
					}
				}
			}
		}
		else if (strike == 0 && ball == 3) { // �ϳ��� ��Ʈ����ũ�ų� 1�� 2�� �ƿ��ΰ�� false
			for (int a = 1; a < 10; a++) {
				for (int b = 1; b < 10; b++) {
					for (int c = 1; c < 10; c++) {
						if (a == i || b == j || c == k) {
							num[a][b][c] = false;
						}
						if ((a != j && a != k) || (b != i && b != k) || (c != i && c != j)) { // �ϳ��� ���� �ƴѰ��
							num[a][b][c] = false;
						}
						if ((a != j && a != k) && (b != i && b != k) && (c != i && c != j)) { // �ƿ��� ���
							num[a][b][c] = false;
						}
					}
				}
			}
		}
		else if (strike == 1 && ball == 1) { 
			for (int a = 1; a < 10; a++) {
				for (int b = 1; b < 10; b++) {
					for (int c = 1; c < 10; c++) {
						if (a == i && b == k && c != j) {
							continue;
						}
						if (a == i && c == j && b != k) {
							continue;
						}
						if (b == j && a == k && c != i) {
							continue;
						}
						if (b == j && c == i && a != k) {
							continue;
						}
						if (c == k && a == j && b != i) {
							continue;
						}
						if (c == k && b == i && a != j) {
							continue;
						}
						num[a][b][c] = false;
					}
				}
			}
		}
		else if (strike == 1 && ball == 2) {
			for (int a = 1; a < 10; a++) {
				for (int b = 1; b < 10; b++) {
					for (int c = 1; c < 10; c++) {
						if (a == i && b == k && c == j) {
							continue;
						}
						if (b == j && a == k && c == i) {
							continue;
						}
						if (c == k && a == j && b == i) {
							continue;
						}
						num[a][b][c] = false;
					}
				}
			}
		}
	}

	for (int i = 1; i < 10; i++) {
		for (int j = 1; j < 10; j++) {
			for (int k = 1; k < 10; k++) {
				if (num[i][j][k] == true) {
					result++;
					//printf("%d%d%d\n", i,j,k);
				}
			}
		}
	}
	printf("%d\n", result);
}