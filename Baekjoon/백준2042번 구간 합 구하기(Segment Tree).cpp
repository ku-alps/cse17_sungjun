#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void constructSegmentTree(vector<long long> &segmentTree, vector<long long> arr, long long leafNodeSize);
void updateSegmentTree(vector<long long> &segmentTree, long long leafNodeSize, int arrIndex, long long changedValue);
long long sumArrSection(vector<long long> &segmentTree, int arrLeftIndex, int arrRightIndex, long long nodeLeftIndex, long long nodeRightIndex, long long treeIndex);
void showSegmentTree(vector<long long> &segmentTree, long long leafNodeSize);

int main() {

	int N, M, K, treeHeight, mode, a;
	long long b, leafNodeSize;
	vector<long long> segmentTree;
	vector<long long> arr;

	cin >> N >> M >> K;

	treeHeight = int(log2(N - 1)) + 1;
	leafNodeSize = (long long)(pow(2, treeHeight));
	segmentTree = vector<long long>(leafNodeSize * 2, 0);
	arr = vector<long long>(N, 0);

	for (int i = 0; i < N; i++) {
		scanf("%lld", &arr[i]);
	}

	constructSegmentTree(segmentTree, arr, leafNodeSize); // arr�迭 ������� ���� �� ���׸�Ʈ Ʈ�� ����
														  //showSegmentTree(segmentTree, leafNodeSize);

	for (int i = 0; i < M + K; i++) {
		cin >> mode >> a >> b;

		if (mode == 1) { // update ���׸�Ʈ Ʈ��
			a -= 1; // �ε����� 1 ���̰� ���Ƿ�
			updateSegmentTree(segmentTree, leafNodeSize, a, b);
			//showSegmentTree(segmentTree, leafNodeSize);
		}
		else if (mode == 2) { // ���׸�Ʈ Ʈ�� Ư�� ���� �� ����ϱ�
			a -= 1; // �ε����� 1 ���̰� ���Ƿ�
			b -= 1; // �ε����� 1 ���̰� ���Ƿ�
			cout << sumArrSection(segmentTree, a, b, 0, leafNodeSize - 1, 1) << endl;
		}
	}

}

void constructSegmentTree(vector<long long> &segmentTree, vector<long long> arr, long long leafNodeSize) {

	for (int i = 0; i < arr.size(); i++) { // ������� �����ϱ�
		segmentTree[leafNodeSize + i] = arr[i];
	}

	for (int i = leafNodeSize - 1; i > 0; i--) { // ������ ��� �����ϱ�
		segmentTree[i] = segmentTree[i * 2] + segmentTree[i * 2 + 1];
	}
}

void updateSegmentTree(vector<long long> &segmentTree, long long leafNodeSize, int arrIndex, long long changedValue) {

	long long treeIndex = leafNodeSize + arrIndex;
	segmentTree[treeIndex] = changedValue; // ���� ��� ����

	while (treeIndex > 1) { // ���� ���̿��� ���� �������ش�
		treeIndex /= 2;
		segmentTree[treeIndex] = segmentTree[treeIndex * 2] + segmentTree[treeIndex * 2 + 1];
	}
}

long long sumArrSection(vector<long long> &segmentTree, int arrLeftIndex, int arrRightIndex, long long nodeLeftIndex, long long nodeRightIndex, long long treeIndex) {

	if (arrLeftIndex > nodeRightIndex || arrRightIndex < nodeLeftIndex) { // ���׸�Ʈ Ʈ�� ������ ���� ���ؾ� �ϴ� arr ������ ���� ���Ե��� �ʴ� ���
		return 0;
	}

	else if (arrLeftIndex <= nodeLeftIndex && nodeRightIndex <= arrRightIndex) { // ���׸�Ʈ Ʈ�� ������ ���� ���ؾ� �ϴ� arr ������ ���� ���ԵǴ� ���
		return segmentTree[treeIndex];
	}

	else { // ���׸�Ʈ Ʈ�� ������ ���� ���ؾ� �ϴ� arr ������ �Ϻ� ���ԵǴ� ���
		int mid = (nodeLeftIndex + nodeRightIndex) / 2;
		return sumArrSection(segmentTree, arrLeftIndex, arrRightIndex, nodeLeftIndex, mid, treeIndex * 2) + sumArrSection(segmentTree, arrLeftIndex, arrRightIndex, mid + 1, nodeRightIndex, treeIndex * 2 + 1);
	}
}

void showSegmentTree(vector<long long> &segmentTree, long long leafNodeSize) {

	for (int i = 1; i < leafNodeSize * 2; i++) {
		cout << segmentTree[i] << " ";
	}
	cout << endl;
}