#include "ini.h"

INI::INI() 
{ }
void INI::save(std::string _file) 
{
    if (!fs::exists(_file))
	{
		createDir(_file);
		if (!fs::exists(_file))
			return;
	}
	std::ofstream file(_file, std::ios::out | std::ios::trunc);
	if (!file) {
		throw std::logic_error("Failed to open file: " + _file);
	}
	for (const auto& section : (*this)) {
		std::string sec = section.first;
		if (sec == "empty")
			sec = "";
		
		file << "[" << sec << "]" << std::endl;
		for (const auto& keyValuePair : section.second) {
			file << keyValuePair.first << "=" << keyValuePair.second << std::endl;
		}
	}
}
void INI::load(std::string _file) 
{
    std::ifstream file(_file);
	if (!file) {
		throw std::logic_error("Failed to open file: '" + _file + "'");
	}
    std::string line;
	std::string currentSection = "empty";
	while (std::getline(file, line)) {
		line = removeComment(line);
		line = trim(line);
		if (line.empty()) {
			continue;
		}
		if (isSection(line)) {
			currentSection = getSectionName(line);
			currentSection = trim(currentSection);
			if (currentSection == "")
				currentSection = "empty";
			
			if (count(currentSection) > 0) {
				continue;
			}
			(*this)[currentSection] = {};
		}
		else {
			std::string key, value;
			if (!parseLine(line, key, value)) {
				throw std::logic_error("Invalid line: ' " + line + " '");
			}
			(*this)[currentSection][key] = value;
		}
	}
}
std::string& INI::operator()(std::string _sec, std::string _key)
{
	if(_sec.empty())
		_sec = "empty";
    return (*this)[_sec][_key];
}