#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct histo {
	int height;
	int index;
};

int main() {

	vector<histo> stack, histogram;
	int N, i, maxSquare(0), poped(0), poped_index(0), base(0);
	histo element;

	cin >> N;

	for (i = 0; i < N; i++) { // �Է��Ҷ����� ó���ص� ������ �������� ���� ���� �ް� ó���Ѵ�
		scanf("%d", &element.height);
		element.index = i;
		histogram.push_back(element);
	}

	for (i = 0; i < N + 1; i++) {
		if ((i != N) && (stack.empty() || stack.back().height < histogram[i].height)) { //������ �ܰ谡 �ƴϰ� ������ ����ְų� ���� Ž���κ��� ���̰� �� ũ�ٸ�
		}
		else { // �׷��� �ʴٸ� 
			base = 0;
			while ((i == N) || (!stack.empty() && stack.back().height >= histogram[i].height)) { // ������ �ܰ��̰ų� ������ ������� �ʾƾ� �ϰ� ������ top�� ���� Ž������ ũ�ų� ������ pop�Ѵ�
				if (stack.empty()) { // ������ ����ٸ� 
					break;
				}
				poped = stack.back().height; // ������ top�� ������ �����´�
				poped_index = stack.back().index;
				stack.pop_back();
				if (stack.empty()) { // ������ ����ٸ� 
					base = i;
				}
				else { // ������ ������� �ʴٸ� poped�� �ε����� �� ������׷��� �ε��� ũ�����̰� �غ��� �ȴ�
					base += poped_index - stack.back().index;
				}
				maxSquare = max(maxSquare, poped * base);
			}
		}
		if (i != N) {
			stack.push_back(histogram[i]); // ���ÿ� �����͸� Ǫ�����ش�
		}
	}
	
	cout << maxSquare << endl;
}