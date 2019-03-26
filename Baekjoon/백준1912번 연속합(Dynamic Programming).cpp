#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

	int N(0), i(0), j(0), result(-1001);
	vector<int> arr;
	vector<int> dp(100001, -1001); // �ش� �ε�����° ���� �����Ͽ� �������� �� �ִ뿬����  

	scanf("%d", &N);
	arr = vector<int>(N);

	for (i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}

	dp[0] = arr[0];
	result = arr[0];
	for (i = 1; i < N; i++) {
		dp[i] = max(dp[i - 1] + arr[i], arr[i]);
		if (result < dp[i]) {
			result = dp[i];
		}
	}
	printf("%d ", result);
}