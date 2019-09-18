// 线程安全，内存安全的懒汉式单例
// 注：linux上，使用g++编译时没有问题的，可以进入析构，并释放

#include<iostream>
#include<memory>
#include<mutex>

class Singleton{
public:
	typedef std::shared_ptr<Singleton> Ptr;
	~Singleton() {
		std::cout << "Singleton2 Destruct called!" << std::endl;
	}
	Singleton(Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	static Ptr get_instance() {
		// double check lock
		if (m_instance_ptr == nullptr) {
			std::lock_guard<std::mutex> lk(m_mutex);
			if (m_instance_ptr == nullptr) {
				m_instance_ptr = std::shared_ptr<Singleton>(new Singleton);
			}
			return m_instance_ptr;
		}
		// return m_instance_ptr;
	}
private:
	Singleton() {
		std::cout << "Singleton2 construct called!" << std::endl;
	}
	static Ptr m_instance_ptr;
	static std::mutex m_mutex;
};
Singleton::Ptr Singleton::m_instance_ptr = nullptr;
std::mutex Singleton::m_mutex;

int main() {
	Singleton::Ptr instance = Singleton::get_instance();
	Singleton::Ptr instance_2 = Singleton::get_instance();
	return 0;
}

/*
	基于shared_ptr,用来C++比较倡导的RAII思想，用兑现管理资源，当shared_ptr析构的时候，new出来的对象也会被delete掉，一次避免内存泄露
	加了锁，使用互斥量来达到线程安全。这里使用了两个 if 判断语句的技术成为双检锁； 好处是，只有判断指针为空的时候才会加锁，避免了每次调用get_instance的方法都加锁，锁的开销比较大

不足：
	使用智能指针会要求用户也得使用智能指针，非必要不应该提这种约束；使用锁也有开销；同时代码量也增多了，实现上始终希望越简单越好
*/