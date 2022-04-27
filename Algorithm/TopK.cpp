/**
 * @file TopK.cpp
 * @author ray
 * @brief  topk问题的一个简单代码实现
 * @version 0.1
 * @date 2022-04-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// TopK一般可以和海量数据问题一起考察

// TOPK思路：
// 1. 堆
// 2. 快速选择算法
// 3. BFPRT算法
// 4. 全局排序 或者 局部排序

// 海量数据问题：
// 1. 哈希（包括一致性哈希）
// 2. 分治算法（很契合Google的map-reduce框架）
// 3. Bloom Filter

#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

namespace tt1 { //快速选择算法


	int partition(vector<int>& arrs, int l, int r) {
		if (r <= l) {
			return l;
		}
		int pivot = arrs[r];
		int i = l, j = r;
		while (i < j) {
			while (i < j && arrs[i] <= pivot) {
				++i;
			}
			while (i < j && arrs[j] >= pivot) {
				--j;
			}
			swap(arrs[i], arrs[j]);
		}
		swap(arrs[i], arrs[r]);
		return i;
	}

	int QuickSelect(vector<int>& arrs, int K) {
		if (arrs.empty() || arrs.size() < K)
			return -1;
		int low = 0, high = arrs.size() - 1;
		int index = partition(arrs, low, high);
		while (index != K) {
			if (index > K) {
				high = index - 1;
				index = partition(arrs, low, high);
			}
			else {
				low = index + 1;
				index = partition(arrs, low, high);
			}
		}

		for (int i = 0; i < K; ++i) {
			cout << arrs[i] << " ";
		}
		cout << endl;

		return arrs[index];
	}
}


namespace tt2 { //基于小根堆，这里采用STL中的priority_queue


int TopK(vector<int>& arr, int K) {
	if (K < 0 || arr.empty() || arr.size() < K) {
		return -1;
	}
	std::priority_queue<int, vector<int>, greater<int> > pq;

	for (auto v : arr) {
		if (pq.size() < K) {
			pq.push(v);
		}
		else if (pq.top() < v){
			pq.pop();
			pq.push(v);
		}
	}

	while (!pq.empty()) {
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;

	return K;
}


}



int main() {
	vector<int> arr = {9, 2, 1, 4, 7, 5, 6, 8, 3};
	tt1::QuickSelect(arr, 4);

	vector<int> arr1 = {9, 2, 1, 4, 7, 5, 6, 8, 3};
	tt2::TopK(arr1, 4);

	return 0;
}