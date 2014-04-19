#ifndef _SICONF_READER_
#define _SICONF_READER_
#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>

typedef std::string SiString;
const SiString SEPERATION_STRING("=");
const SiString NOT_FOUND("");
typedef std::unordered_map<SiString,SiString> section_map;
class ConfReader {

	SiString stringToLower(const SiString& input);
	public:
		ConfReader():m_file_name(),m_values(),m_debug(false) {}


	//void init();
	bool init(const SiString& filename,bool debug = false);



	/*
	const SiString& get(SiString& name) const {
		if (m_values.find(name) != m_values.end())
			return m_values[name];
		return NOT_FOUND;
	}
	*/
	section_map* get_section(const SiString& name) {
		SiString lowerName(stringToLower(name));
		if (m_values.find(lowerName) != m_values.end())
			return &m_values[lowerName];
		if (m_debug)
			std::cerr << name << " is null\n";
		return NULL;
	}


	inline section_map* get_section( const char* name) {
		return get_section(SiString(name));
	}

	inline section_map* safe_get_section( const char* name) {
		section_map* map(NULL);
		map = get_section(name);
		if (map != NULL)
			return map;
		return new section_map();
	}

	private:

		SiString rstrip(SiString& str) {
			for(SiString::reverse_iterator it(str.rbegin()); it != str.rend(); ++it) {
				switch(*it) {
					case ' ':
					case '\n':
					case '\r':
						break;
					default:
						return SiString(str.begin(),it.base());
				}
			}
			return str;
		}

		bool load(SiString&);
		void read_section(std::ifstream& input,section_map& values);

		SiString m_file_name;
		std::unordered_map<SiString,section_map> m_values;
		bool m_debug;


};
#endif
