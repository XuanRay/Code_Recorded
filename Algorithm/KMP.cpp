#include <string>
#include <iostream>
#include <vector>

// 参考自左神
// 简单测试通过
// 若要充分验证，可设计对数器予以实现

using namespace std;

vector<int> nextArray(string);

int KMP(string s1, string s2) {
	int len1 = s1.length(), len2 = s2.length();
	if (len1 < 1 || len1 < len2) {
		return -1;
	}
	int i1 = 0, i2 = 0;
	vector<int> nextArr = nextArray(s2);
	while (i1 < len1 && i2 < len2) {
		if (s1[i1] == s2[i2]) {
			i1++;
			i2++;
		}
		else if (nextArr[i2] == -1) {
			i1++;
		}
		else {
			i2 = nextArr[i2];
		}
	}
	return i2 == len2 ? i1 - i2 : -1;
}


vector<int> nextArray(string s2) {
	int sz = s2.size();
	if (1 == sz) {
		return {-1};
	}
	vector<int> v_nextarr(sz, 0);
	v_nextarr[0] = -1;
	v_nextarr[1] = 0;
	int i = 2;
	int cn = 0;
	while (i < sz) {
		if (s2[i - 1] == s2[cn]) {
			v_nextarr[i++] = ++cn;
		}
		else if (cn > 0) {
			cn = v_nextarr[cn];
		}
		else {
			v_nextarr[i++] = 0;
		}
	}
	return v_nextarr;
}


int main() {
	string s1 = "abcabcabcaaa";
	string s2 = "aa";
	int res = KMP(s1, s2);

	cout << res << "\n";

	return 0;
}
