#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int histogram(vector<int> &height, int start, int end);

// ���� �������� ������׷����� �ذ��ϱ�
int main() {

	int N(0); // ĭ ��
	vector<int> height;
	scanf("%d", &N);
	height = vector<int>(N);
	for (int i = 0; i < N; i++)
		scanf("%d", &height[i]);
	printf("%d\n", histogram(height, 0, N));
}

int histogram(vector<int> &height, int start, int end) {

	if (start == end) // base case ���� 0 
		return 0;
	if (start + 1 == end) // base case ���� �ϳ�ũ��
		return height[start];

	int mid = (start + end) / 2;
	int result = max(histogram(height, start, mid), histogram(height, mid, end)); // �� ���� �����˻��ؼ� �ִ�
															
	int width = 1, maxHeight = height[mid], left = mid, right = mid;

	while (right - left + 1 < end - start) {

		int leftMax = left > start ? min(maxHeight, height[left - 1]) : -1; // �������� Ȯ������ ����� ����
		int rightMax = right < end - 1 ? min(maxHeight, height[right + 1]) : -1; // ���������� Ȯ������ ����� ����
												
		if (leftMax >= rightMax) { // �� ���� ���̸� ���� ������ Ȯ��
			maxHeight = leftMax;
			left--;
		}
		else {
			maxHeight = rightMax;
			right++;
		}
		width++;
		result = max(result, width * maxHeight); // �ִ� ����
	}

	return result;
}