#include"model_rank.h"
#include<iostream>

class AModel : public Model{
public:
	AModel() {};
	virtual ~AModel() {};
};

ModelRegistry* GlobalModelRegistry() {
	static ModelRegistry helper;
	return &helper;
}

REGISTER_MODEL_SIMPLE("AModel", AModel)

void main() {
	std::cout << "HENG HA" << std::endl;

	system("pause");
	return;
}

