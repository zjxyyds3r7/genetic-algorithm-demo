#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

/**
 * @brief Լ������ ��xת��Ϊy ����x+y=2
 * 
 * @param x xֵ
 * 
 * @return yֵ
 **/
double x2y(double x) {
	return 2 - x;
}

/**
 * @brief Ŀ�꺯�� �˴��õ���1/x+2/y
 * 
 * @param x xֵ
 * 
 * @return ������ĺ���ֵ
 **/
double fun(double x) {
	double y = x2y(x);
	if (x <= 0 || y <= 0) {
		return -1;
	}
	return 1 / x + 2 / y;
}

/**
 * @brief ��ȡ����ֵ�м��ֵ ���ڽ���
 * 
 * @param x1 
 * @param x2 
 * 
 * @return �м�ֵ
 **/
double getMiddle(double x1, double x2) {
	return (x1 + x2) / 2;
}
/**
 * @brief ��ȡ���ֵ ���ڱ����Լ���ʼ����
 * 
 * 
 * @return �����
 **/
double getRandom() {
	return (rand() % (int)(x2y(1) * 1000)) * 1.0 / 1000 + rand()%2;
}


/**
 * @brief ��ӡ��ǰ����Ⱥ
 * 
 * @param arr Ҫ��ӡ����Ⱥ
 **/
void printArr(vector<double> arr) {
	for (auto i : arr) {
		cout << i << "\t";
	}
	cout << endl;
}


int main(int argc, char** argv) {
	int depth = 1000;
	
	srand(time(0));
	
	vector<double> nextarr; // ��Ⱥ
	
	cout << "�����Ⱥ:";
	for (int i = 0; i < 5; i++) {
		nextarr.push_back(getRandom());// ��ʼ�������Ⱥ
	}
	printArr(nextarr);

	double minx = nextarr[0], ans = fun(minx);
	// ���ڼ�¼��Сֵ����Ӧ��Ⱥ��Ϣ
	
	for (int i = 0; i <= depth; i++) {
		sort(nextarr.begin(), nextarr.end(), [&](double x1, double x2) {
			return fun(x1) - fun(x2);
			// ����Ŀ�꺯����ֵ��������
		});

		if (ans > fun(nextarr[0])) {
			// ����ȵ�ǰ���Ž���� �ͻ�
			ans = fun(nextarr[0]);
			minx = nextarr[0];
			// �����ǰ��Ⱥ�����Ž��ֵ
			cout << "��ǰ��������:"<< i <<"\t��ǰ��Ⱥ:";
			printArr(nextarr);
			cout << "��ǰ���Ž�:" << fun(nextarr[0]) << endl;
		}
		//�˴�ֻ������Ⱥǰ��λ
		
		nextarr[3] = getMiddle(nextarr[0], nextarr[1]);
		// ����λ���ý�����ʽ�޸�
		
		// ������ʿ��Ե���
		if (rand() % 100 > 50) { //����λ�аٷ�֮��ʮ�����Ա���(ʹ�������)
			nextarr[4] = getRandom();
		} else { // ����ٷ�֮��ʮ������Ϊ����
			nextarr[4] = getMiddle(nextarr[1], nextarr[2]);
		}

	}
	return 0;
}
