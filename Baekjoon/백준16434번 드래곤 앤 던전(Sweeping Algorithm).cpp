#include <stdio.h>

int main() {

	int N, type, a, h;
	long long atk, hp(0), ans(0);

	scanf("%d %lld", &N, &atk);

	for (int i = 1; i <= N; i++) {
		scanf("%d %d %d", &type, &a, &h);
		if (type == 1) { // ������ ��� ü���� ���� ����
			long long turn = (h - 1) / atk;
			hp += turn * a;
		}
		else { // ������ ��� �ʿ��� ü���� ������ 0���� �� �� �¾���.
			atk += a;
			hp -= h;
			if (hp < 0) {
				hp = 0;
			}
		}

		if (ans < hp) { // ������ ���ԵǴ� ���� ���� ���������� �ְ��� ����س��� �ƴҽ� �� ������ ����� �� ����
			ans = hp;
		}
	}
	printf("%lld\n", ans + 1); // �� �������� - ���� + 1�� �ּҷ� �ʿ��� ���� ü���� �ȴ�
}