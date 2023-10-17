#pragma once 

#include <filesystem>
#include <string>
#include <fstream>
#include <unordered_map>

namespace fs = std::filesystem;
typedef std::pair<const std::string, std::string> KeyValue;
typedef std::unordered_map<std::string, std::string> List;
typedef std::pair<const std::string, std::unordered_map<std::string, std::string>> Table;


class INI 
	: public std::unordered_map<std::string, List>  /* <Section, <Key, Value> > */
{
public:
	INI(); 
	void save(std::string);
	void load(std::string);
	std::string& operator()(std::string _sec, std::string _key);
public:
	static std::string removeComment(const std::string& line) {
		const auto commentPos = line.find('#');
		if (commentPos != std::string::npos) {
			return line.substr(0, commentPos);
		}
		return line;
	}
	static bool isSection(const std::string& line) {
		return line.front() == '[' && line.back() == ']';
	}
	static std::string trim(const std::string& str) {
		const auto start = str.find_first_not_of(" \t");
		const auto end = str.find_last_not_of(" \t");
		if (start == std::string::npos || end == std::string::npos) {
			return "";
		}
		return str.substr(start, end - start + 1);
	}
	static std::string getSectionName(const std::string& line) {
		return line.substr(1, line.size() - 2);
	}
	bool parseLine(const std::string& line, std::string& key, std::string& value) {
		const auto equalsPos = line.find('=');
		if (equalsPos == std::string::npos) {
			return false;
		}
		key = line.substr(0, equalsPos);
		value = line.substr(equalsPos + 1);
		key = trim(key);
		value = trim(value);
		if (value.find("[") != std::string::npos && value.find("]") != std::string::npos && value.find_first_of("[") < value.find_first_of("]")) // we have a "[...]" in our value
		{
			std::string sub;
			if (!(sub = value.substr(value.find_first_of("[") + 1, value.find_first_of("]"))).empty()) // the content of the "[...]" is not empty
			{
				std::string sec = "", _key = "";
				if (sub.find(".") != std::string::npos)
				{
					sec = sub.substr(sub.find("."));
					key = sub.substr(sub.find(".")+1, sub.length()-1);
				}
				else {
					key = sub;
				}
				if (this->count(sec) > 0)
				{
					if (this->operator[](sec).count(key) > 0)
					{
						value = value.substr(0,value.find_first_of("[")) + this->operator[](sec)[key] + value.substr(value.find_first_of("]")+1);
					}
					else {
						if (sec == "")
						{
							throw std::logic_error("Key does not exist. Key: " + _key);
						}
						throw std::logic_error("Key does not exist. Section: " + sec + " ; Key: " + _key);
					}
				}
				else {
					throw std::logic_error("Section does not exist. Section: " + sec);
				}
				
			}
			
		}
		
		return !key.empty();
	}
	// deletes a file
	static uint8_t deleteDir(const std::string& filename)
	{
		int re = fs::remove(filename);
		if (fs::exists(filename))
			return re;
		else
			return 0;
	}
	static uint8_t createDir(const std::string& filename, bool ignoreExist = false)
	{
		if (fs::exists(filename) && !ignoreExist)
			return 1;
		else
		{
			std::ofstream creater(filename, std::ios::trunc | std::ios::out);
			if (!creater.is_open())
			{
				creater.close();
				return deleteDir(filename);
			}
			else
			{
				creater.close();
				return 0;
			}
		}
	}
};