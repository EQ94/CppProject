// ����ģʽ
// ֱ��ʹ��ʱ��ʵ�������󣬼���ֱ����Ӿget_instance()������ʱ���newһ�������Ķ���
// �ô�����������þͲ���ռ���ڴ�
// �������̲߳���ȫ���ڴ�й©

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

// �������
// �̰߳�ȫ���⣺�����̻߳�ȡ����ʱ�п���������̬��������һ���߳���if���ж� m_instance_ptr�ǿյģ����ǿ�ʼʵ��������
//			ͬʱ��2���߳�Ҳ���Ի�ȡ���������ʱ���ж�m_instance_ptr���ǿյģ�����Ҳ��ʼʵ���������������ͻ�ʵ��������������
//	  �������������
// �ڴ�й¶��ע�⵽����ֻ����new������ȴû�и���delete�������ֻ�й��캯�������ã���������ȴû�б����ã���˻ᵼ���ڴ�й¶��
//    ���������ʹ�ù���ָ��
