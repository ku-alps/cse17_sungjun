#include <stdio.h>

int main() { //�� �ڸ����� ���������� �̷���� ���� �Ѽ��̴�.

	int i = 0;
	int n = 0;
	int number = 0;

	scanf("%d", &n);

	for (i = 1; i <= n; i++) {
		if (i < 10)
			number++;
		else if (i < 100) 
			number++;
		else if (i < 1000) 
			if(((i % 10) - (i / 10)%10) == ((i / 10) % 10 - (i / 100)%10))
				number++;
	}

	printf("%d\n", number);
}