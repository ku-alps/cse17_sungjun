#include <iostream> // ����2
#include <vector> // ž�ٿ�(�޸������̼�)�� DP��� ��� § �ڵ�
#include <algorithm>

using namespace std;	

const int MAX_K = 10001;
/*
int minCoinNum(vector<int> &coin, vector< vector<int> > &memoization, int i, int n, int k);  // i��° �������� ��밡���ϸ� k���� ǥ���ϴ� �ּ� ������ ������ �����Ѵ�

int main() { // ž�ٿ� �޸������̼�

	vector<int> coin;
	vector< vector<int> > memoization;
	int n(0), k(0), result(0);

	cin >> n >> k;

	coin = vector<int>(n);
	memoization = vector< vector<int> >(n, vector<int>(MAX_K, 0));

	for (int i = 0; i < n; i++) {
		cin >> coin[i];
	}

	sort(coin.begin(), coin.end());

	result = minCoinNum(coin, memoization, 0, n, k);
	if (result == MAX_K)
		cout << "-1" << endl;
	else
		cout << minCoinNum(coin, memoization, 0, n, k) << endl;

}

int minCoinNum(vector<int> &coin, vector< vector<int> > &memoization, int i, int n, int k) {

	int result(0);

	if (k == 0) {
		return 0;
	}
	if (i == n) {
		return MAX_K;
	}

	if (memoization[i][k] != 0) {
		return memoization[i][k];
	}

	if (k - coin[i] >= 0) {
		result = min(minCoinNum(coin, memoization, i + 1, n, k), minCoinNum(coin, memoization, i, n, k - coin[i]) + 1);
	}
	else
		return MAX_K;

	memoization[i][k] = result;

	return result;
}*/

int main() { // DP��� ���� ��

	vector<int> coin;
	vector< vector<int> > dp;
	int n(0), k(0), result(0);

	cin >> n >> k;

	coin = vector<int>(n);
	dp = vector< vector<int> >(n + 1, vector<int>(MAX_K, MAX_K));

	for (int i = 0; i < n; i++) {
		cin >> coin[i];
	}

	sort(coin.begin(), coin.end());

	for (int i = 0; i < n; i++) {
		dp[i][0] = 0;
		for (int j = 0; j <= k; j++) {
			if (j + coin[i] <= k)
				dp[i][j + coin[i]] = min(dp[i][j + coin[i]], dp[i][j] + 1);
			dp[i + 1][j] = dp[i][j];
		}
	}

	result = dp[n - 1][k];
	if (result == MAX_K)
		cout << "-1" << endl;
	else
		cout << result << endl;
}