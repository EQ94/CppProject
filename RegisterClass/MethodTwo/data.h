#pragma once
#include<iostream>
#include<memory>
#include<vector>
#include<unordered_map>
#include<fstream>

class Data_Base {
public:
	virtual ~Data_Base() = default;
	void ClassShow() {
		std::cout << "This is Data_Base Class" << std::endl;
	}
};