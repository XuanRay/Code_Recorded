#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;


/**
 * @brief 实现饿汉模式
 * 
 * 无线程安全问题。缺点：程序中单例较多，程序启动慢，性能低。
 * 其次如果两个单例类有依赖关系，无法保证创建初始化实例的顺序。
 */
class Singleton {
public:
    static Singleton& getInstance() {
        return m_singleton;
    }

    /* 禁用copy ctor和copy assignment */
    Singleton(const Singleton& s) = delete;
    Singleton& operator=(const Singleton& s) = delete;

private:
    static Singleton m_singleton;

    /* ctor 私有化 */
    Singleton() {}    
};

Singleton Singleton::m_singleton; /* 初始化 */


/* test */
int main() {
    vector<thread> vThread;
    
    for (int i = 0; i < 4; ++i) {
        vThread.push_back(thread([](){
            this_thread::sleep_for(std::chrono::seconds(1));
            for (int j = 0; j < 10; ++j) {
                cout << &Singleton::getInstance() << endl;
            }
        }));
    }

    for (auto& e : vThread) {
        e.join();
    }

    return 0;
}