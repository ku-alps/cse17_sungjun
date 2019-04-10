#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

	int N;
	vector<int> stair;
	vector< vector<int> >dp; // ù��° �ε��� 0:��ĭ������ �ö�� ���, 1:��ĭ������ �ö�°��
							// �ι�° �ε��� �����ġ
	cin >> N;

	stair = vector<int>(N + 1, 0);
	dp = vector< vector<int> >(2, vector<int>(N + 1, 0));

	for (int i = 1; i < N + 1; i++) {
		scanf("%d", &stair[i]);
	}

	dp[0][1] = stair[1];
	dp[1][1] = stair[1];
	
	for (int i = 2; i < N + 1; i++) {
		dp[0][i] = dp[1][i - 1] + stair[i];
		dp[1][i] = max(dp[0][i - 2], dp[1][i - 2]) + stair[i];
	}

	cout << max(dp[0][N], dp[1][N]) << endl;
}