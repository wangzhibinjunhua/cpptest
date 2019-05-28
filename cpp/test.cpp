#include<iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
int main_test() {

	std::string fingerprint = "Neffos/Neffos_C9s/Neffos_C9s:9";
	char* pfingerprint = "Neffos/Neffos_C9s/Neffos_C9s:9";
	
	char* _sbrand = strchr(pfingerprint, '/');
	printf("_sbrand:%s\n", _sbrand);
	std::string brand = fingerprint.substr(0, strlen(pfingerprint) - strlen(_sbrand));
	printf("brand:%s\n", brand.c_str());
	
	char* _sname = strchr(_sbrand +1, '/');
	printf("_sname:%s\n", _sname);
	printf("pfingerprint:%s\n", pfingerprint);
	std::string str_sbrand = _sbrand;
	std::string name = str_sbrand.substr(1, strlen(_sbrand) - strlen(_sname)-1);
	printf("name:%s\n", name.c_str());
	name += "_EEA";
	std::string fingerprint_new = brand + "/" + name + _sname;
	printf("new fingerprint :%s\n", fingerprint_new.c_str());
	getchar();
	return 0;
}