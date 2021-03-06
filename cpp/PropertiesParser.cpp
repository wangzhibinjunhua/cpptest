/*
 * Copyright (c) 2014 Fredy Wijaya
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <fstream>
#include <iostream>
#include "PropertiesParser.h"
#include "PropertiesUtils.h"

namespace cppproperties {

PropertiesParser::PropertiesParser() {
}

PropertiesParser::~PropertiesParser() {
}

Properties PropertiesParser::Read(const std::string& file) {
    Properties properties;

    std::ifstream is;
    is.open(file.c_str());
    if (!is.is_open()) {
        throw PropertiesException("PropertiesParser::Read(" + file + "): Unable to open file for reading.");
    }

    try {
        size_t linenr = 0;
        std::string line;
        while (getline(is, line)) {
            if (PropertiesUtils::IsEmptyLine(line) || PropertiesUtils::IsComment(line)) {
                // ignore it
            } else if (PropertiesUtils::IsProperty(line)) {
                std::pair<std::string, std::string> prop = PropertiesUtils::ParseProperty(line);
                properties.AddProperty(prop.first, prop.second);
            } else {
                throw PropertiesException("PropertiesParser::Read(" + file + "): Invalid line " + std::to_string(linenr) + ": " + line);
            }
            ++linenr;
        }
        is.close();
    } catch (...) {
        // don't forget to close the ifstream
        is.close();
        throw;
    }

    return properties;
}

void PropertiesParser::Write(const std::string& file, const Properties& props) {
    std::ofstream os;
    os.open(file.c_str());
    if (!os.is_open()) {
        throw PropertiesException("PropertiesParser::Write(" + file + "): Unable to open file for writing.");
    }

    try {
        const std::vector<std::string>& keys = props.GetPropertyNames();
        for (std::vector<std::string>::const_iterator i = keys.begin();
            i != keys.end(); ++i) {
            os << *i << " = " << props.GetProperty(*i) << std::endl;
        }
        os.close();
    } catch (...) {
        // don't forget to close the ofstream
        os.close();
        throw;
    }
}

//add by wzb
std::string PropertiesParser::ReadData(const std::string& file, const std::string& key)
{
	std::ifstream fin(file.c_str());
	if (!fin) {
		Properties props;
		props.AddProperty("wzb", "1");
		PropertiesParser::Write(file, props);
		
	}
	else
	{
		fin.close();
	}
	
	Properties properties= PropertiesParser::Read(file);
	std::string value = properties.GetProperty(key,"");
	return value;
}

int PropertiesParser::WriteData(const std::string& file, const std::string& key, const std::string& value)
{
	std::ifstream fin(file.c_str());
	if (!fin) {
		Properties props;
		props.AddProperty("wzb", "1");
		PropertiesParser::Write(file, props);

	}
	else
	{
		fin.close();
	}
	
	Properties properties = PropertiesParser::Read(file);
	properties.AddProperty(key, value);
	try
	{
		PropertiesParser::Write(file, properties);
	}
	catch (const std::exception&)
	{
		return -1;
	}
	
	return 0;
}

int PropertiesParser::RemoveData(const std::string& file, const std::string& key)
{
	std::ifstream fin(file.c_str());
	if (!fin) {
		return 0;
	}
	fin.close();

	Properties properties = PropertiesParser::Read(file);
	std::ofstream os;
	os.open(file.c_str());
	if (!os.is_open()) {
		return -1;
	}
	try
	{
		properties.RemoveProperty(key);
		const std::vector<std::string>& keys = properties.GetPropertyNames();
		for (std::vector<std::string>::const_iterator i = keys.begin();
			i != keys.end(); ++i) {
			os << *i << " = " << properties.GetProperty(*i) << std::endl;
		}

		os.close();
	}
	catch (const std::exception&)
	{
		os.close();
		//return -1;
	}
	
	return 0;

}

//end

} /* namespace cppproperties */
