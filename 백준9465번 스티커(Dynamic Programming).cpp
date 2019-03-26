#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int maxScore(vector< vector<int> > &sticker, int n);

int main() {

	int T(0), n(0), score;
	vector< vector<int> > sticker(2);

	cin >> T;

	for (int i = 0; i < T; i++) { // ���� �迭 �Է�
		cin >> n;
		for (int j = 0; j < n; j++) {
			cin >> score;
			sticker[0].push_back(score);
		}
		for (int j = 0; j < n; j++) {
			cin >> score;
			sticker[1].push_back(score);
		}

		printf("%d\n", maxScore(sticker, n)); // �ִ� ���
		sticker = vector< vector<int> >(2); // ���� �迭 �ʱ�ȭ
	}

}

int maxScore(vector< vector<int> > &sticker, int n) {

	vector< vector<int> > dp(n + 1, vector<int>(3, 0)); // dp�� �ι�°
	
	for (int i = 0; i < n; i++) { // ��ƼĿ�� 0������ �����Ѵٰ� ����, dp�� 1������ �����Ѵٰ� ����
		dp[i + 1][0] = max(dp[i][0], max(dp[i][1], dp[i][2])); // i�� ��ƼĿ�� �Ѵ� ���� �ʾ����� 
		dp[i + 1][1] = max(dp[i][0], dp[i][2]) + sticker[0][i]; // i�� ��ƼĿ�� �� ��ƼĿ�� ��������
		dp[i + 1][2] = max(dp[i][0], dp[i][1]) + sticker[1][i]; // i�� ��ƼĿ�� �Ʒ� ��ƼĿ�� ��������
	}

	return max(dp[n][0], max(dp[n][1], dp[n][2]));
}