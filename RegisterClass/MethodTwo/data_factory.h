#pragma once
#include"data.h"
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<functional>
// 类模板std::function是一个通用的多态函数包装器。std::function的实例可以存储，复制和调用任何可调用的目标
// 当std::function对象未包裹任何实际的可调用元素，调用该std::function对象将抛出std::bad_function_call异常
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