#include<iostream>
#include <string.h>
#include <stdio.h>
#include "PropertiesParser.h"
#include <string>
using namespace std;
using namespace cppproperties;

void testwrite()
{
	//string rv = PropertiesParser::ReadData("wzb1.prop", "key1");
	//cout << "rv=" << rv << endl;
	//int ret = PropertiesParser::WriteData("wzb1.prop", "key1", "a1231");
	//cout << "ret=" << ret << endl;
	int ret = PropertiesParser::WriteData("wzb2.prop", "key2", "baaa33222");
	cout << "ret1=" << ret << endl;
	//int ret = PropertiesParser::RemoveData("wzb2.prop", "key1");
	//cout << "ret2=" << ret << endl;
}
int main(int argc,char** argv)
{
	testwrite();
	getchar();
	return 0;
}