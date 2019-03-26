#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct conference{

	int start;
	int end;

}Conference;

bool compare(Conference a, Conference b);

int main() {

	int N(0), time(0), max(0);
	Conference con;
	vector<Conference> meeting;
	
	scanf("%d", &N);

	for (int i(0); i < N; i++) {
		scanf("%d %d", &con.start, &con.end);
		meeting.push_back(con);
	}

	sort(meeting.begin(), meeting.end(), compare); // ������ �ð��� ���缭 ����
	
	//for (int i(0); i < N; i++)
	//	printf("%d %d\n", meeting[i].start, meeting[i].end);

	for (int i(0); i < N; i++) { // ȸ�� ��ȣ�� ���ʴ�� Ȯ��
		while (time > meeting[i].start) {
			i++;
			if (i == N)
				break;
		}
		if (i == N)
			break;
		max++;
		time = meeting[i].end;
	}

	cout << max << "\n";
}

bool compare(Conference a, Conference b) {
	
	if (a.end == b.end) { // ������ �ð��� ������ ���۽ð��� �̸���
		return a.start < b.start;
	}
	else { // ������ �ð��� �ٸ��� ������ ���� ������ �ð���
		return a.end < b.end;
	}
}