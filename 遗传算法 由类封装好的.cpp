#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
/**
 * �����Լ����Ŵ��㷨 �޸�Result���еĺ���
 * Ŀ�꺯��:Result::getTarget()
 * ��������:Result::getEvolution(...)
 * ���캯��:Result::getVariation()
 * 
 * Target��ʾĿ�꺯��ֵ������ ����֧�ֱȽϴ�С ��Ҫ���㷨������
 * Result::getVariation()����Ҫ�޶�����������
 * 
 **/

typedef double Target;
typedef double result;

class Result {
		result res;
	public:
		/**
		 * @brief ��ȡһ������ֵ
		 *
		 *
		 * @return ���ر���ֵ��resֵ
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
		 * @brief ��ȡ������Ӧ��Ŀ�꺯����ֵ
		 *
		 *
		 * @return ��ǰ������Ӧ��Ŀ�꺯����ֵ
		 **/
		Target getTarget() {
			return 1 / res + 2 / (2 - res);
		}

		/**
		 * @brief ͨ����������������
		 *
		 * @param other ��һ���� ��һ����Ϊthis
		 *
		 * @return ���ؼ����Ľ�����
		 **/
		Result getEvolution(Result other) {
			return Result((other.getRes() + this->getRes()) / 2);
		}

		result getRes() const {
			return res;
		}

		/**
		 * @brief �����ǰ��
		 *
		 * @param out ��
		 * @param r Ҫ�������Ⱥ
		 *
		 * @return ��
		 **/
		friend std::ostream& operator<<(std::ostream& out, Result& r) {
			// TODO
			// �����ǰ��
			out << r.getRes() << " ";
			return out;

		}

};

class Genetic {
		Result best;// ���Ž�
		std::vector<Result> group; // ��Ⱥ
		int groupSize; // ��Ⱥ��С
		double saveRatio; // ���������������������Ž����
		double variationRatio;// ������������������ֵı������
	public:
		Genetic(int g = 10, double sr = 0.5, double vr = 0.3): groupSize(g), saveRatio(sr), variationRatio(vr) {
			for (int i = 0; i < g; i++) {
				group.push_back(Result());
			}
			best = group[0];
		}
		
		/**
		 * @brief ��ʼ�Ŵ��㷨
		 * 
		 * @param times ����
		 **/
		void start(int times = 1000) {
			//Result minres = group[0];
			for (int i = 0; i < times; i++) {
				std::sort(group.begin(), group.end(), [](auto x, auto y) {
					return x.getTarget() - y.getTarget();
				});
				if (best.getTarget() > group[0].getTarget()) {
					best = group[0];
					std::cout << "ִ�е�" << i + 1 << "��\t���Ž�Ϊ:" << best.getTarget() << std::endl;
					std::cout << "��ǰ��Ⱥ" << *this << std::endl;
				}
				evolution();

			}
		}
		
		/**
		 * @brief ������Ⱥ����
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
