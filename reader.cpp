#include "reader.h"
#include <iostream>

bool ConfReader::init(const SiString& filename,bool debug) {
	m_file_name = filename;
	m_debug = debug;
	return load(m_file_name);
}

SiString ConfReader::stringToLower(const SiString& input) {
	SiString lowercase(input);
	for (size_t i = 0; i !=  lowercase.length();i++) {
		lowercase[i] = tolower(lowercase[i]);
	}
	return lowercase;
}
void ConfReader::read_section(std::ifstream& input,section_map& values) {
	SiString buf;
	size_t loc(SiString::npos);
	while ((getline(input,buf)).good()) {
		buf = rstrip(buf);
		if (buf.size() <= 1)
			return;
		if (buf[0] == ';')
			continue;
		loc = buf.find(SEPERATION_STRING);
		if (loc == SiString::npos)
			continue;
		SiString key(stringToLower(buf.substr(0,loc)));
		SiString value(buf.substr(loc+1));
		if (m_debug)
			std::cerr << "\tKey: '" << key << "'\n\tValue: '" << value << "'\n";
		values[key] = value;
	}

}

bool ConfReader::load(SiString& filename) {
	std::ifstream conf_file;
	conf_file.open(filename.c_str(),std::fstream::in);
	if (!conf_file) {
		conf_file.close();
		return false;
	}
	
	SiString sectionName;
	while ((getline(conf_file,sectionName)).good()) {
		if (sectionName.empty())
			continue;
		switch (sectionName[0]) {
			case '[':
				// remove //[
				sectionName.erase(sectionName.begin());
				// remove //]
				sectionName.erase(sectionName.rfind("]"));
				sectionName = stringToLower(sectionName);
				if (m_debug)
					std::cerr << "Section " << sectionName << "\n";
				m_values[sectionName] = section_map();
				read_section(conf_file,m_values[sectionName]);
				break;

			default:
				break;
		}
	}
	conf_file.close();
	return true;
}

/*
const SiString& get(SiString& attribute) const {
	if (m_values.find(attribute) != m_values.end())
		return m_values[attribute];
	return NOT_FOUND;
}
*/

