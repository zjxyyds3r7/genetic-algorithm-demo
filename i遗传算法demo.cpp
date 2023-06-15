#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

/**
 * @brief 约束函数 由x转换为y 曲中x+y=2
 * 
 * @param x x值
 * 
 * @return y值
 **/
double x2y(double x) {
	return 2 - x;
}

/**
 * @brief 目标函数 此处用的是1/x+2/y
 * 
 * @param x x值
 * 
 * @return 计算出的函数值
 **/
double fun(double x) {
	double y = x2y(x);
	if (x <= 0 || y <= 0) {
		return -1;
	}
	return 1 / x + 2 / y;
}

/**
 * @brief 获取两个值中间的值 用于进化
 * 
 * @param x1 
 * @param x2 
 * 
 * @return 中间值
 **/
double getMiddle(double x1, double x2) {
	return (x1 + x2) / 2;
}
/**
 * @brief 获取随机值 用于变异以及初始参数
 * 
 * 
 * @return 随机数
 **/
double getRandom() {
	return (rand() % (int)(x2y(1) * 1000)) * 1.0 / 1000 + rand()%2;
}


/**
 * @brief 打印当前的种群
 * 
 * @param arr 要打印的种群
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
	
	vector<double> nextarr; // 种群
	
	cout << "最初种群:";
	for (int i = 0; i < 5; i++) {
		nextarr.push_back(getRandom());// 初始化随机种群
	}
	printArr(nextarr);

	double minx = nextarr[0], ans = fun(minx);
	// 用于记录最小值所对应种群信息
	
	for (int i = 0; i <= depth; i++) {
		sort(nextarr.begin(), nextarr.end(), [&](double x1, double x2) {
			return fun(x1) - fun(x2);
			// 根据目标函数的值进行排序
		});

		if (ans > fun(nextarr[0])) {
			// 如果比当前最优解更优 就换
			ans = fun(nextarr[0]);
			minx = nextarr[0];
			// 输出当前种群和最优解的值
			cout << "当前迭代次数:"<< i <<"\t当前种群:";
			printArr(nextarr);
			cout << "当前最优解:" << fun(nextarr[0]) << endl;
		}
		//此处只保留种群前三位
		
		nextarr[3] = getMiddle(nextarr[0], nextarr[1]);
		// 第四位采用进化方式修改
		
		// 变异概率可以调整
		if (rand() % 100 > 50) { //第五位有百分之五十可能性变异(使用随机数)
			nextarr[4] = getRandom();
		} else { // 另外百分之五十可能性为进化
			nextarr[4] = getMiddle(nextarr[1], nextarr[2]);
		}

	}
	return 0;
}
