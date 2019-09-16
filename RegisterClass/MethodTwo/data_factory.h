#pragma once
#include"data.h"
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<functional>
// ��ģ��std::function��һ��ͨ�õĶ�̬������װ����std::function��ʵ�����Դ洢�����ƺ͵����κοɵ��õ�Ŀ��
// ��std::function����δ�����κ�ʵ�ʵĿɵ���Ԫ�أ����ø�std::function�����׳�std::bad_function_call�쳣
class DataFactory {
public:
	using DataBuilder = std::function<Data_Base*(void)>;
	using DataBuilderMap = std::unordered_map<std::string, DataBuilder>;

public:
	static DataFactory& Instance() {
		static DataFactory inst;
		return inst;
	}

	bool RegisterFactory(const std::string& name, const DataBuilder& builder) {
		Data_Base* base0 = builder();
		base0->ClassShow();
 		data__factory_[name] = builder;
		std::cout << "data__factory.size() = " << data__factory_.size() << std::endl;
		auto it = data__factory_.begin();
		Data_Base* base= it->second();
		base->ClassShow();
		return true; 
	}

	Data_Base* Create(const std::string& name) {
		auto it = data__factory_.find(name);
		return (it == data__factory_.end() ? nullptr : (it->second)());
	}
private:
	DataFactory() = default;
	DataFactory(const DataFactory&) = delete;
	DataFactory& operator=(const DataFactory&) = delete;

	DataBuilderMap data__factory_;
};

#define REGISTER_DATA__FACTORY(name, type) \
	static bool _register_dc_factoer_helper##__LINE__ = \
		DataFactory::Instance().RegisterFactory(name, []()->type*{return new type();});