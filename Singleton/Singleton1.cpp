#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;


/**
 * @brief 实现懒汉模式（常用），延迟加载
 * 
 * 存在线程安全问题。 加锁解决
 * 
 * 使用时才加载资源，第一次使用实例对象时，创建对象（即new出来）。进程启动无负载。
 * 多个单例实例启动顺序自由控制。
 */
class Singleton {
public:
    // static Singleton& getInstance() { 
    //     m_lock.lock();            //每次获取实例都要加锁，影响性能。
    //     if (m_p_singleton == nullptr) {
    //         m_p_singleton = new Singleton();
    //     }
    //     m_lock.unlock();
    //     return *m_p_singleton;
    // }

    static Singleton& getInstance() {
        /* 双重检查提高效率 */
        if (m_p_singleton == nullptr) {
            m_lock.lock();
            if (m_p_singleton == nullptr) {
                m_p_singleton = new Singleton();    
            }
            m_lock.unlock();
        }
        return *m_p_singleton;
    }

    /* 禁用copy ctor和copy assignment */
    Singleton(const Singleton& s) = delete;
    Singleton& operator=(const Singleton& s) = delete;

private:
    static Singleton* m_p_singleton;
    static mutex      m_lock;

    /* ctor 私有化 */
    Singleton() {}    
};

Singleton* Singleton::m_p_singleton = nullptr; /* 初始化 */
mutex Singleton::m_lock;

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