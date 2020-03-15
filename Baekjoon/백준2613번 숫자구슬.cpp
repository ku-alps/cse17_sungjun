#include <iostream>
#include <vector>
using namespace std;

int N, M, b, sum = 0, result;
vector<int> bead;
vector<int> people_num;

void sol(int s, int e);

int main() {

	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%d", &b);
		sum += b;
		bead.push_back(b);
	}

	sol(1, sum);

	printf("%d\n", result);
	if (people_num.size() != M) { // �׷� ���� ���� �ʴ� ��� ������ Ư�� ���̽�
		int group_size = people_num.size();
		for (int i = 0; i < people_num.size(); i++) {
			if (group_size == M) {
				break;
			}
			if (people_num[i] > 1) {
				people_num[i]--;
				people_num.insert(people_num.begin() + i, 1);
				group_size++;
			}
		}
	}
	for (int i = 0; i < people_num.size(); i++) {
		printf("%d ", people_num[i]);
	}
}

void sol(int s, int e) {

	int m = (s + e) / 2; // �׷� �ִ��� m�� �Ѿ�� �ȵ�
	int group = 1, sum = 0, flag = 0, cnt = 0;

	for (int i = 0; i < N; i++) {
		if (bead[i] > m) { // �ϳ������� �ʰ��ع����� ���
			flag = -1;
			break;
		}
		sum += bead[i];
		cnt++;
		if (sum > m) {
			group++;
			i--;
			sum = 0;
			if (s == e) {
				people_num.push_back(cnt - 1);
			}
			cnt = 0;
		}
	}
	if (s == e) {
		people_num.push_back(cnt);
		result = s;
		return;
	}
	if (group > M || flag == -1) {
		sol(m + 1, e);
	}
	else {
		sol(s, m);
	}
}