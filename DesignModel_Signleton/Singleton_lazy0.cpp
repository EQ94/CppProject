// 懒汉模式
// 直到使用时才实例化对象，即，直到电泳get_instance()方法的时候才new一个单利的对象
// 好处是如果被调用就不会占用内存
// 坏处是线程不安全，内存泄漏

#include<iostream>
class Singleton {
private:
	Singleton() {
		std::cout << "Single Construct Called!" << std::endl;
	}
	Singleton(Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	static Singleton* m_instance_ptr;
public:
	~Singleton() {
		std::cout << "Signle Destruct Called!" << std::endl;
	}
	static Singleton* get_instance() {
		if (m_instance_ptr == nullptr) {
			m_instance_ptr = new Singleton;
		}
		return m_instance_ptr;
	}
	void use() const {
		std::cout << "Single In use()" << std::endl;
	}
};

Singleton* Singleton::m_instance_ptr = nullptr;

int main() {
	Singleton* instance = Singleton::get_instance();
	Singleton* instance_2 = Singleton::get_instance();
	return 0;
}

// 问题分析
// 线程安全问题：当多线程获取单例时有可能引发竟态条件：第一个线程在if中判断 m_instance_ptr是空的，于是开始实例化单例
//			同时第2个线程也尝试获取单例，这个时候判断m_instance_ptr还是空的，于是也开始实例化单例；这样就会实例化出两个对象
//	  解决方法：加锁
// 内存泄露：注意到类中只负责new出对象，却没有负责delete对象，因此只有构造函数被调用，析构函数却没有被调用，因此会导致内存泄露；
//    解决方法：使用共享指针
