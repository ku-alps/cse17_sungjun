#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;
int eaten(0); // ���� ��θ��� ����
int check[20][20] = { 0 }; // ���°�� �Դ��� Ȯ�����ִ� �迭
int q[20][20] = { 0 }; // ť�� ���°���� Ȯ�����ִ� �迭
int c = 1, k = 0; // ���°�� ������, ť�� ���° ����

struct Point {
	int i;
	int j;
};

Point moveWNES(Point point, int dir);
int bfsQueue(vector< vector<int> >& map, Point& now, int& N, int& baby_shark);

int main() {

	int N(0), baby_shark(2), result(0), temp(0);
	Point now;
	vector< vector<int> > map;
	cin >> N;
	map = vector< vector<int> >(N, vector<int>(N));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 9) {
				now.i = i;
				now.j = j;
			}
		}
	}

	map[now.i][now.j] = 0;

	while (1) {
		temp = result;
		result += bfsQueue(map, now, N, baby_shark);

		/*printf("���� ��Ȳ, ���ũ��%d  ��θ� %d\n", baby_shark, eaten);
		for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
		printf("%3d ", q[i][j]);
		}
		cout << endl;
		}
		cout << endl;
		memset(q, 0, sizeof(q));
		k = 0;*/

		if (temp == result) {
			break;
		}
	}

	/*printf("�Դ� ���� ��Ȳ\n");
	for (int i = 0; i < N; i++) {
	for (int j = 0; j < N; j++) {
	cout << check[i][j] << " ";
	}
	cout << endl;
	}*/

	cout << result << endl;
}

Point moveWNES(Point point, int dir) { // dir�� 0�� 1�� 2�� 3�� point�� ��ȯ 

	if (dir == 0)
		point.i--;
	else if (dir == 1)
		point.j--;
	else if (dir == 2)
		point.j++;
	else if (dir == 3)
		point.i++;

	return point;
}

int bfsQueue(vector< vector<int> >& map, Point& now, int& N, int& baby_shark) { // now ��ġ���� ť(��)�� �̿��Ͽ� Ž���ϱ�(BFS)

	int dir(0), i(0), j(0);
	Point temp1, temp2;
	int visited[20][20] = { 0 }; // �湮�� �� ��ġ������ ����
	int depth[20][20] = { 0 }; // ���������� �� �� ��ġ������ ������ ����(����)
	memset(depth, -1, sizeof(depth)); // ���� �迭�� -1�� ��� �ʱ�ȭ
	depth[now.i][now.j] = 0; //������ġ�� ���̴� 0�̴�
	int already_in_deq = 0;
	deque<Point> deq; // �� ����

	deq.push_back(now); // ���� ��ġ�� ���� �ִ´�

	while (1) { // ���� ���� ���� �ݺ��Ѵ� ���� �� �ִ� ����Ⱑ ���� �� �� �ִ°��� ���� �� ����
		i = now.i;
		j = now.j;

		if (map[i][j] < baby_shark && map[i][j] > 0) { // ���� ��ġ�Ѱ��� �ڱ�ũ�⺸�� ���� ����� �ִ� ���̸� �԰� ������
			map[i][j] = 0; // ����⸦ ġ���
			eaten++; // ��θ� +1
			if (eaten == baby_shark) { // ��θ��� �ڽ��� ũ��� ������
				baby_shark++; // ���ũ�� +1
				eaten = 0; // ��θ� = 0
			}
			check[i][j] = c++; // �ش� ��ġ�� ����⸦ ���°�� �Դ��� �迭�� ����
			q[i][j] = k++; // �ش� ��ġ�� ����Ⱑ ���� ���ҿ����� ����
			return depth[i][j]; // �Ÿ��� �����ϰ� �Լ� ����
		}

		else { // ���� ��ġ�Ѱ��� ���� �� �ִ� ����Ⱑ ���ٸ� (���Դ� ����Ⱑ �ְų� vs �ƹ��͵� ���ų�)

			deq.pop_front(); // ������ġ�� ���� ��带 ����
			visited[i][j] = 1;

			for (dir = 0; dir < 4; dir++) { // ���� ��ġ���� �ϼ��������� Ȯ���� �غ���
				now = moveWNES(now, dir); // ��ġ�� �ٲ��
				already_in_deq = 0;
				for (int z = 0; z < deq.size(); z++) {
					if (now.i == deq[z].i && now.j == deq[z].j) { // �̹� ���� ���� ������ �ִٸ�
						already_in_deq = 1;
						break;
					}
				}

				if (already_in_deq == 0 && now.i >= 0 && now.j >= 0 && now.i < N && now.j < N && map[now.i][now.j] >= 0 && map[now.i][now.j] <= baby_shark && visited[now.i][now.j] == 0) { // ���� ��ġ���� �ϼ����������� �˻��Ͽ� �� �� �ִ� ���̸�
					deq.push_back(now); // �� ��ġ�� ���� �ڿ� �ִ´�
					depth[now.i][now.j] = depth[i][j] + 1; // Ȯ���� ��ġ�� ���� ��ġ���� ���̰� 1�� ū���̴�
					if (deq.size() >= 2 && deq[deq.size() - 1].i >= 0 && deq[deq.size() - 2].i >= 0 && ((deq[deq.size() - 1].i + 1 == deq[deq.size() - 2].i) || ((deq[deq.size() - 1].i == deq[deq.size() - 2].i) && (deq[deq.size() - 1].j < deq[deq.size() - 2].j))) && (depth[deq[deq.size() - 1].i][deq[deq.size() - 1].j] == depth[deq[deq.size() - 2].i][deq[deq.size() - 2].j])) { // ���� ���� ���� ������ ���� �������� y��� �ϳ� ���� ������
						temp1 = deq.back(); // temp1�� �̹��� ���� ����
						deq.pop_back();
						temp2 = deq.back(); // temp2�� ������ ���� ����
						deq.pop_back();
						deq.push_back(temp1); // �̹��� ���� ������ ���� �ְ�
						deq.push_back(temp2); // ���Ŀ� ���� ������ ���߿� �ִ´�
					}
				}
				now.i = i;
				now.j = j;
			}
		}

		q[i][j] = k++;

		if (deq.empty() == 1) { // ���� �������� ã�� ���Ѵٸ�
			break;
		}

		now = deq.front(); // ������ġ�� ���� �Ǿ��� ��ġ�̴�.
	}

	return 0;
}