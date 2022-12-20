#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

#define height 8
#define width 8
#define widthCH 13

int mainarrays(int a[2][height][width]);
int ochki(int och[height][width]);
int table(int n, int m, char kom[height][widthCH], int azp[2][height][width], int a1[2][height][width], int a2[2][height][width], int a3[2][height][width]);
int balls(int aSUMz1[2][height][width], int a1[2][height][width], int a2[2][height][width], int a3[2][height][width], int arr[height], int m, int max, int index, int kom[height][widthCH], int x1, int x2);
int array(int SUMz[2][height][width], int a1[2][height][width], int a2[2][height][width], int a3[2][height][width]);

int main() {
	setlocale(LC_ALL, "RUS");

	char kom[height][widthCH] = {
	{"Спортклубы |"},
	{"МРСК-Волги |"},
	{"Мехзавод   |"},
	{"Промсинтез |"},
	{"ЧХТГ       |"},
	{"11 ОФПС    |"},
	{"Здоровье   |"},
	{"ДОСААФ     |"}
	};

	int az[2][height][width], a1[2][height][width], a2[2][height][width], a3[2][height][width], och[height][width], och1[height][width], och2[height][width], och3[height][width];
	int  one = 1, two = 2, sum = 0, sum1 = 0, sumob = 0,  index = 0, arr[height];
	float zabit[height], h = 0, f = 0, u = 0;
	char k = 1;

	mainarrays(a1);//Заполняю массивы случайными числами от 0 до 20 
	mainarrays(a2);//Это будут забитые и пропущенные мячи за каждую игру в каждом матче
	mainarrays(a3);//3 массива использую потому что каждая команда играет 3 игры в 1 матче

	while (1) {
		printf("\nВыберите пукт из предоставленного списка:\n1)Таблица забитых мячей\n2)Таблица пропущенных мячей\n3)Количество набранных очков каждой команды\n4)Разница между суммами забитых и пропущенных мячей\n5)Команда с наибольшим количеством забитых и пропущенных мячей\n6)Отношение суммы забитых мячей к пропущенным\n7)Количество побед в играх\n8)Завершить работу программы\n");

		scanf_s("%c", &k);
		getchar();
		switch (k) {

		case'1':
			printf("\n\t\t\t\tОбщее количество забитых мячей в каждой игре\n");
			table(sum, one, kom, az, a1, a2, a3);//Суммирую 3 массива вывожу забитые мячи [0]
			break;

		case '2':
			printf("\n\t\t\t\tОбщее количество пропущенных мячей в каждой игре\n");
			table(one, two, kom, az, a1, a2, a3);//Суммирую 3 массива вывожу пропущенные мячи [1]
			break;

		case '3':
			printf("\nКоличество набранных очков\n\n");
			ochki(och1, a1);//Считаю очки в зависимости от того как сыграли команды
			ochki(och2, a2);//Если команда забила больше ей начисляется 1 очко
			ochki(och3, a3);//Если команда проиграла или они сыграли в ничью то 0 очков

			for (int i = 0; i < height; i++) {
				for (int n = 0; n < widthCH; n++)
				{
					printf("%c", kom[i][n]);
				}
				for (int j = 0; j < width; j++) {
					och[i][j] = och1[i][j] + och2[i][j] + och3[i][j];
					sum += och[i][j];
				}
				printf("%4d", sum);
				sum = 0;
				printf("\n");
			}
			break;

		case '4':
			printf("\nРазница между суммами забитых и пропущенных мячей\n\n");
			for (int k = 0; k < 1; k++) {//Вычитаю сумму забитых и пропущенных мячей 

				for (int i = 0; i < height; i++)
				{
					for (int n = 0; n < widthCH; n++)
					{
						printf("%c", kom[i][n]);
					}
					for (int z = 0; z < width; z++) {
						array(az, a1, a2, a3);
						sum += az[k][i][z];
						sum1 += az[1][i][z];
						sumob = sum - sum1;
					}
					printf("%4d", sumob);
					sum = 0;
					sum1 = 0;
					printf("\n");
				}
			}
			break;

		case'5':
			printf("\nКоманда с наибольшим количеством забитых мячей\n");
			balls(az, a1, a2, a3, arr, sum, sum1, index, kom, sum, one);//Сортирую сумму забитых, пропущенных мячей и вывожу наибольшее кол-во
			printf("\nКоманда с наибольшим количеством пропущенных мячей\n");
			balls(az, a1, a2, a3, arr, sum, sum1, index, kom, one, two);
			break;

		case'6':
			printf("\nОтношение суммы забитых мячей к пропущенным\n\n");
			for (int i = 0; i < 1; i++) {//Сумму забитых мячей делю на сумму пропущенных 
				for (int j = 0; j < height; j++) {
					for (int n = 0; n < widthCH; n++)
					{
						printf("%c", kom[j][n]);
					}
					for (int l = 0; l < width; l++) {
						array(az, a1, a2, a3);
						f += az[0][j][l];
						u += az[1][j][l];
					}
					h = f / u;
					zabit[j] = h;
					printf("%.2f\n", zabit[j]);
					f = 0;
					u = 0;
				}
			}
			break;

		case'7':
			printf("\nКоличество побед в играх\n");
			ochki(och1, a1);//1 очко = 1 победа в игре
			ochki(och2, a2);//Соответственно просто произвожу подсчёт очков в каждой игре
			ochki(och3, a3);//Суммирую 3 массива с очками и получаю кол-во побед в каждой игре
			printf("\n--------------------------------------------------------------------------------------------------\n");
			printf("\t\tСпортклубы|МРСК-Волги|Мехзавод|Промсинтез| ЧХТГ  | 11 ОФПС | Здоровье | ДОСААФ|\n");
			for (int i = 0; i < height; i++) {
				for (int n = 0; n < widthCH; n++)
				{
					printf("%c", kom[i][n]);
				}
				for (int j = 0; j < width; j++) {
					och[i][j] = och1[i][j] + och2[i][j] + och3[i][j];
					printf("%10d", och[i][j]);
				}
				printf("\n--------------------------------------------------------------------------------------------------\n");
			}
			break;
		case '8':
			exit(EXIT_SUCCESS);
		}
	}
}

int mainarrays(int a[2][height][width]) {
	for (int e = 0; e < 2; e++) {
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				a[e][i][j] = rand() % 20;
				a[e][i][i] = 0;
			}
		}
	}
}

int ochki(int och[height][width], int a[2][height][width]) {
	int m = 0, n = 0;
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < height; j++) {
			for (int l = 0; l < width; l++) {
				m = a[0][j][l];
				n = a[1][j][l];
				if (m > n) {
					och[j][l] = 1;
				}
				if (m <= n) {
					och[j][l] = 0;
				}
				m = 0;
				n = 0;
			}
		}
	}
}

int table(int n, int m, char kom[height][widthCH], int azp[2][height][width], int a1[2][height][width], int a2[2][height][width], int a3[2][height][width]) {
	printf("\n--------------------------------------------------------------------------------------------------\n");
	printf("\t\tСпортклубы|МРСК-Волги|Мехзавод|Промсинтез| ЧХТГ  | 11 ОФПС | Здоровье | ДОСААФ|\n");
	for (int k = n; k < m; k++) {
		for (int i = 0; i < height; i++)
		{
			for (int n = 0; n < widthCH; n++)
			{
				printf("%c", kom[i][n]);
			}
			for (int z = 0; z < width; z++) {
				azp[k][i][z] = a1[k][i][z] + a2[k][i][z] + a3[k][i][z];
				printf("%10d", azp[k][i][z]);
			}
			printf("\n--------------------------------------------------------------------------------------------------\n");
		}
	}
}

int balls(int aSUMz1[2][height][width], int a1[2][height][width], int a2[2][height][width], int a3[2][height][width], int arr[height], int m, int max, int index, char kom[height][widthCH], int x1, int x2) {
	for (int i = x1; i < x2; i++) {
		for (int j = 0; j < height; j++) {
			for (int l = 0; l < width; l++) {
				aSUMz1[i][j][l] = a1[i][j][l] + a2[i][j][l] + a3[i][j][l];
				m += aSUMz1[i][j][l];
			}
			arr[j] = m;
			m = 0;
			if (max <= arr[j]) {
				max = arr[j];
				index = j;
			}
		}
		printf("%s %d", kom[index], max);
	}
	printf("\n");
}

int array(int SUMz[2][height][width], int a1[2][height][width], int a2[2][height][width], int a3[2][height][width]) {
	for (int k = 0; k < 1; k++) {
		for (int i = 0; i < height; i++) {
			for (int z = 0; z < width; z++) {
				SUMz[k][i][z] = a1[k][i][z] + a2[k][i][z] + a3[k][i][z];
				SUMz[1][i][z] = a1[1][i][z] + a2[1][i][z] + a3[1][i][z];
			}
		}
	}
}
