// �̰߳�ȫ���ڴ氲ȫ������ʽ����
// ע��linux�ϣ�ʹ��g++����ʱû������ģ����Խ������������ͷ�

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
	����shared_ptr,����C++�Ƚϳ�����RAII˼�룬�ö��ֹ�����Դ����shared_ptr������ʱ��new�����Ķ���Ҳ�ᱻdelete����һ�α����ڴ�й¶
	��������ʹ�û��������ﵽ�̰߳�ȫ������ʹ�������� if �ж����ļ�����Ϊ˫������ �ô��ǣ�ֻ���ж�ָ��Ϊ�յ�ʱ��Ż������������ÿ�ε���get_instance�ķ��������������Ŀ����Ƚϴ�

���㣺
	ʹ������ָ���Ҫ���û�Ҳ��ʹ������ָ�룬�Ǳ�Ҫ��Ӧ��������Լ����ʹ����Ҳ�п�����ͬʱ������Ҳ�����ˣ�ʵ����ʼ��ϣ��Խ��Խ��
*/