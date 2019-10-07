#include <iostream>
#include <cstdlib>
using namespace std;

char map[9][9];

int dfs(int i, int j);
int check(int i, int j, int num);

int dfs(int i, int j) {

	if (map[i][j] != '0') {	
		if (j < 8) {
			dfs(i, j + 1);
		}
		else if (i < 8){
			j = 0;
			dfs(i + 1, j);
		}
		else {
			for (int a = 0; a < 9; a++) {
				for (int b = 0; b < 9; b++) {
					printf("%c", map[a][b]);
				}
				printf("\n");
			}
			exit(0);
		}
		return 0;
	}

	for (int num = 1; num < 10; num++) {
		if (check(i, j, num) == 0) {
			map[i][j] = num + '0';
			dfs(i, j);
		}
		map[i][j] = '0';
	}
	
	return 0;
}

int check(int i, int j, int num) {
	for (int x = 0; x < 9; x++) { // ���� üũ
		if (x != i && map[x][j] == num + '0') {
			return 1; // �Ұ���
		}
	}
	for (int y = 0; y < 9; y++) { // ���� üũ
		if (y != j && map[i][y] == num + '0') {
			return 1; // �Ұ���
		}
	}
	for (int z = 0; z < 9; z++) { // ��� üũ
		if ((3 * (i / 3) + (z / 3)) != i && (3 * (j / 3) + (z % 3)) != j && map[3 * (i / 3) + (z / 3)][3 * (j / 3) + (z % 3)] == num + '0') {
			return 1; // �Ұ���
		}
	}
	return 0; // ����
}

int main() {

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> map[i][j];
		}
	}
	
	dfs(0, 0);
}