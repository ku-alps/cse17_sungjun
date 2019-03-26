#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long segmentalArr(vector<long long> &width, int start, int end);

// ���� �������� �κй迭 ����
int main() {

	int N(0); // �迭�� ��
	vector<long long> width;
	scanf("%d", &N);
	width = vector<long long>(N);
	for (int i = 0; i < N; i++)
		scanf("%lld", &width[i]);
	printf("%lld\n", segmentalArr(width, 0, N));
}

long long segmentalArr(vector<long long> &width, int start, int end) {

	if (start == end) // base case ���� 0 
		return 0;
	if (start + 1 == end) // base case �迭�ϳ�
		return width[start] * width[start];

	int mid = (start + end) / 2;
	long long result = max(segmentalArr(width, start, mid), segmentalArr(width, mid, end)); // �� ���� �����˻��ؼ� �ִ�

	long long baseLine = width[mid], maxHeight = width[mid], left = mid, right = mid;

	while (right - left + 1 < end - start) {

		long long leftMax = left > start ? min(maxHeight, width[left - 1]) : -1; // �������� Ȯ������ ����� ����
		long long rightMax = right < end - 1 ? min(maxHeight, width[right + 1]) : -1; // ���������� Ȯ������ ����� ����

		if (leftMax >= rightMax) { // �� ���� ���̸� ���� ������ Ȯ��
			maxHeight = leftMax;
			left--;
			baseLine += width[left];
		}
		else {
			maxHeight = rightMax;
			right++;
			baseLine += width[right];
		}
		result = max(result, baseLine * maxHeight); // �ִ� ����
	}

	return result;
}