#include"data.h"
#include"data_factory.h"
#include<iostream>
#include<vector>
#include<unordered_map>

class AData : public Data_Base {
public:
	AData() {};
};

REGISTER_DATA__FACTORY("Adata", AData)

void main() {
	std::cout << "HENG HA" << std::endl;
	system("pause");
	return;
}