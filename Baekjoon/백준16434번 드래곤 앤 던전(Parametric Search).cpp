#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Map {
	int type;
	int atk;
	int hp;
};

struct Hero {
	long long atk;
	long long hp;
};

int main() {

	int N, heroATK;
	long long minHP(0), maxHP(0), hp(0);
	vector<Map> map;
	Hero hero;

	cin >> N >> heroATK;
	map = vector<Map>(N);

	for (int i = 0; i < N; i++) {
		cin >> map[i].type >> map[i].atk >> map[i].hp;
		if (map[i].type == 1) { // ��簡 �־��� ��� �̰ܾߵǴ� �ִ� ü��ġ�� ����Ѵ� (Parametric Search�� ��ش��� �����ϴ� ����� ���� �˾ƾ��ϱ� ����)
			maxHP += (long long)((map[i].hp / heroATK) + 1) * map[i].atk; // ����ȯ �ʼ�!
		}
	}

	//printf("�ʱ� ���� �ִ� ü��: %lld\n", maxHP);

	while (1) {

		hp = (maxHP + minHP) / 2; // ������ �Ҹ��� ���� ������� �ӽ� ü�°��� �����ش�
		//printf("���ο� �ӽ� ü��: %lld\n", hp);
		hero.atk = heroATK; // ������� ���� �ʱ�ȭ
		hero.hp = hp;

		for (int i = 0; i < N; i++) {
			if (map[i].type == 1) { // �ش� �ε��� ������ ���Ͱ� �ִٸ�

				int turn = ((map[i].hp - 1) / hero.atk); // ������ �ش� �ϸ�ŭ ������ �ްԵȴ�
				hero.hp -= (long long)turn * map[i].atk; // ���� ü�� ���� ����

				if (hero.hp <= 0) { // ������ ������ �׾��ٸ� ���� ���°��� �׸��ΰ� ���ο� ���� ü�������� ������Ѵ�
					break;
				}
			}
			else if (map[i].type == 2) { // �ش� �ε��� ������ ������ �ִٸ� ���������� �����Ѵ�
				hero.hp += map[i].hp;
				hero.atk += map[i].atk;
				if (hero.hp > hp) { // ������ ü���� �ִ�ü���� ���� �� ����
					hero.hp = hp;
				}
			}	
		}

		if (hero.hp > 0) { // ������ ü�� ������ ������ ���⿡ ����, min ~ �߰�
			maxHP = hp;
		}
		else { // ������ ü�� ������ ������ ���⿡ �Ҹ���, �߰� ~ max
			minHP = hp;
		}
		if (minHP + 1 == maxHP) {
			break;
		}
	}
	cout << maxHP << endl;
}