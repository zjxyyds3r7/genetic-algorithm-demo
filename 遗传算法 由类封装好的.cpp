#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
/**
 * 定义自己的遗传算法 修改Result类中的函数
 * 目标函数:Result::getTarget()
 * 进化函数:Result::getEvolution(...)
 * 变异函数:Result::getVariation()
 * 
 * Target表示目标函数值的类型 必须支持比较大小 需要在算法中排序
 * Result::getVariation()中需要限定变量定义域
 * 
 **/

typedef double Target;
typedef double result;

class Result {
		result res;
	public:
		/**
		 * @brief 获取一个变异值
		 *
		 *
		 * @return 返回变异值的res值
		 **/
		static result getVariation() {
			// TODO
			//
			return (rand() % (100)) * 1.0 / 100 + rand() % 2;
		}

		Result(result r = getVariation()) {
			this->res = r;
		}

		Result(const Result& o) {
			this->res = o.getRes();
		}


		/**
		 * @brief 获取这个解对应的目标函数的值
		 *
		 *
		 * @return 当前解所对应的目标函数的值
		 **/
		Target getTarget() {
			return 1 / res + 2 / (2 - res);
		}

		/**
		 * @brief 通过两个解计算进化解
		 *
		 * @param other 另一个解 第一个解为this
		 *
		 * @return 返回计算后的进化解
		 **/
		Result getEvolution(Result other) {
			return Result((other.getRes() + this->getRes()) / 2);
		}

		result getRes() const {
			return res;
		}

		/**
		 * @brief 输出当前解
		 *
		 * @param out 流
		 * @param r 要输出的种群
		 *
		 * @return 无
		 **/
		friend std::ostream& operator<<(std::ostream& out, Result& r) {
			// TODO
			// 输出当前解
			out << r.getRes() << " ";
			return out;

		}

};

class Genetic {
		Result best;// 最优解
		std::vector<Result> group; // 种群
		int groupSize; // 种群大小
		double saveRatio; // 保留比例：所保留的最优解比例
		double variationRatio;// 变异比例：不保留部分的变异比例
	public:
		Genetic(int g = 10, double sr = 0.5, double vr = 0.3): groupSize(g), saveRatio(sr), variationRatio(vr) {
			for (int i = 0; i < g; i++) {
				group.push_back(Result());
			}
			best = group[0];
		}
		
		/**
		 * @brief 开始遗传算法
		 * 
		 * @param times 轮数
		 **/
		void start(int times = 1000) {
			//Result minres = group[0];
			for (int i = 0; i < times; i++) {
				std::sort(group.begin(), group.end(), [](auto x, auto y) {
					return x.getTarget() - y.getTarget();
				});
				if (best.getTarget() > group[0].getTarget()) {
					best = group[0];
					std::cout << "执行第" << i + 1 << "轮\t最优解为:" << best.getTarget() << std::endl;
					std::cout << "当前种群" << *this << std::endl;
				}
				evolution();

			}
		}
		
		/**
		 * @brief 进行种群进化
		 * 
		 **/
		void evolution() {
			int saveNum = groupSize * saveRatio;
			for (int i = saveNum; i < groupSize; i++) {
				if (rand() % 1000 < variationRatio * 1000) {
					group[i] = Result::getVariation();
				} else {
					group[i] = group[i].getEvolution(group[rand() % saveNum]);
				}
			}
		}
		
		std::vector<Result> getGroup() {
			return this->group;
		}
		
		friend std::ostream& operator<<(std::ostream& out, Genetic& g) {
			for (Result r : g.getGroup()) {
				out << r;
			}
			return out;
		}
};

int main(int argc, char** argv) {
	srand(time(NULL));
	Genetic g;
	g.start();
	return 0;
}
