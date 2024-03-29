// 最推荐的单例模式——局部静态变量(magic static)
// 靠靠靠靠�--靠靠靠(magic static)
#include<iostream>

class Singleton {
public:
	~Singleton() {
	    std::cout << "Singleton destruct called!" << std::endl;
	}
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	static  Singleton& get_instance() {
	    static Singleton instance;
	    return instance;
	}
private:
	Singleton() {
	    std::cout << "Singleton construct called!" << std::endl;
	}
};

int main() {
	Singleton& instance_1 = Singleton::get_instance();
	Singleton& instance_2 = Singleton::get_instance();
	return 0;
}
