#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<functional>

class Model {
public:
	Model() {};
	virtual ~Model() {};

public:
	void ShowClass() {
		std::cout << "This is Model Class" << std::endl;
	}
};

class ModelRegistry {
public:
	using ModelFactory = std::function<Model*(void)>;
	using ModelFactoryMap = std::unordered_map<std::string, ModelFactory>;

public:
	ModelRegistry() {};
	void Register(const std::string &name, const ModelFactory &factory) {
		if (factory == nullptr)
			return;
		Model* base0 = factory();
		base0->ShowClass();
		model_factory_map_[name] = factory;
		std::cout << "model__factory_map_.size() = " << model_factory_map_.size() << std::endl;
	}

	Model* Create(const std::string& name) {
		auto it = model_factory_map_.find(name);
		if (it != model_factory_map_.end()) {
			return it->second();
		}
		return nullptr;
	}

public:
	ModelFactoryMap model_factory_map_;
};

static ModelRegistry* GlobalModelRegistry0;	// 引发读访问权限冲突
ModelRegistry* GlobalModelRegistry();

class ModelHelper {
public:
	using ModelFactory = std::function<Model*(void)>;
	using ModelFactoryMap = std::unordered_map<std::string, ModelFactory>;

public:
	ModelHelper(const std::string &name, const ModelFactory &factory) {
		Model* base0 = factory();
		base0->ShowClass();
		GlobalModelRegistry()->Register(name, factory);
	}
};

#define REGISTER_MODEL(name, factory) \
	static ModelHelper helper_obj##__COUNTER__(name, factory);

#define REGISTER_MODEL_SIMPLE(name, type) \
	REGISTER_MODEL(name, []() -> type* {return new type();})