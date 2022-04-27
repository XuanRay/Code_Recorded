#include <iostream>
#include <vector>
using namespace std;

/* 大顶堆 */
class HeapSort {
public:
	HeapSort(vector<int> _arrs) : arrs(_arrs) {}

	HeapSort& operator=(const HeapSort& h) = delete;

	/* 建堆 */
	void buildHeap();

	/*  下沉
	 *  @param i 要下沉节点的编号
	 *  @param n 待排序数组的大小
	 */
	void percolateDown(int i, int n);

	/* 交换数组中两位置元素 */
	void swap(int i, int j) {
		int tmp = arrs[i];
		arrs[i] = arrs[j];
		arrs[j] = tmp;
	}

	/* 得到左孩子下标 */
	int LeftChild(int i) {
		return 2*i + 1;
	}

	/* 堆排序主函数 */
	void heapSorting();

	/* 测试 */
	void print() {
		for (auto v : arrs) {
			cout << v << " ";
		}
		cout << endl;
	}

	/* 对外提供的接口，访问排序后的数组 */
	vector<int> getArr() {
		return arrs;
	}


private:
	vector<int> arrs;
};


void HeapSort::percolateDown(int i, int n) {
	int tmp = arrs[i];
	int child = LeftChild(i);
	for ( ; child < n; i = child, child = LeftChild(i)) {
		if (child < n-1 && arrs[child] <= arrs[child + 1]) {
			child++;
		}
		if (tmp < arrs[child]) {
			arrs[i] = arrs[child];    //类似插入排序的覆盖
		}
		else {
			break;
		}
	}
	arrs[i] = tmp;
}

void HeapSort::buildHeap() {
	int sz = arrs.size();
	for (int i = (sz - 1) / 2; i >= 0; --i) {
		percolateDown(i, sz);
	}
}

void HeapSort::heapSorting() {
	buildHeap();
	int sz = arrs.size();
	for (int i = sz - 1; i > 0; --i) {
		swap(i, 0);
		percolateDown(0, i);
	}
}


int main() {
	vector<int> arr = {9, 2, 1, 4, 7, 5, 6, 8, 3};
	HeapSort hs(arr);
	hs.heapSorting();
	hs.print();

	return 0;
}