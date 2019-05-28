#include<iostream>
#include <string.h>
#include <stdio.h>
#include "PropertiesParser.h"
using namespace std;
using namespace cppproperties;

void testwrite()
{
	Properties props=PropertiesParser::Read("11.properties");;
	props.AddProperty("key1001", "value100");
	props.AddProperty("key2001", "value200");
	props.AddProperty("key300", "value3001");
	PropertiesParser::Write("11.properties", props);
}
int main(int argc,char** argv)
{
	testwrite();
	getchar();
	return 0;
}