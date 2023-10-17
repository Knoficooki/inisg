/***********************************
 *  _           _                
 * (_)  _ __   (_)  ___    __ _  
 * | | | '_ \  | | / __|  / _` | 
 * | | | | | | | | \__ \ | (_| | 
 * |_| |_| |_| |_| |___/  \__, | 
 *                        |___/  
 * 
 * 		IMPORTANT!
 * GIT:
 * 
 * https://github.com/Knoficooki/inisg.git
 * 
 * 
 * LICENSE:
 * GNU General Public License v2.0
 * 
 * https://github.com/Knoficooki/inisg/blob/main/LICENSE
 * 
 * 
 * README:
 * 
 * https://github.com/Knoficooki/inisg/blob/main/README.md
 * 
 * 
 * SYNTAX:
 *		inisg load -f [file] (--force)
 *
 *		inisg save ([-f [file]) (--keep)
 *
 *		inisg set (-s [section]) -k [key] -v [value]
 *
 *		inisg get (-s [section]) -k [key] (-v [default value]) (-f [file]) (--delete) (--trunc)
 *
 *		inisg new (-f [file]) (--force)
 *
 *		inisg clear (--force)
 *
 * 
 * STRUCTURE:
 *	.
 *	└── .inisig/
 *	    ├── sys.ini.info
 *	    └── [SectionName]/
 *	        └── [Key].val
 * 
 * 
***********************************/

#include <string>

std::string seasoninfofile = "./.inisg/.inisg.season.info";
std::string inisgPath = "./.inisg/";

#include "utils.hpp"

#include "actions.hpp"

void help(std::string&& e = "") {
	throw std::logic_error((
		std::string("\t\tHelp\nSYNTAX:\n\tinisg load -f [file]\n\tinisg save ([-f [file])\n\tinisg set (-s [section]) -k [key] -v [value]\n\tinisg get (-s [section]) -k [key] (-v [default value])\n\tinisg new (-f [file])\n\tinisg clear\n\n\0")
		 + e.c_str()).c_str());
}

std::vector<std::string> operators = {
	"load",
	"save",
	"set",
	"get",
	"new",
	"clear"
};

uint8_t isOperator(std::string&& str) {
	return inVector<std::string, uint8_t>(str, operators);
}

int main(int argc, char** argv) {
	try {
		if (argc == 1) {
			help();
		} 
		else {
			uint8_t op = isOperator(argv[1]);
			switch (op)
			{
			case 1: {
				if(argc < 4)
					help("Not enougth arguments!");
				bool forceload = false;
				std::string inifile;
				for (unsigned int i = 2; i < argc; i++)
				{
					std::string arg = argv[i];
					if (arg == "-f")
					{
						if(argc < i+1)
							help("Missing argument!");
						inifile = argv[++i];
					}
					else if (arg == "--force")
					{
						forceload = true;
					}
					else {
						help(std::string("This argument is not part of the syntax. Argument:") + argv[i]);
					}
				}
				load(inifile, forceload);
				break;
			}
			case 2: {
				std::string inifilePath;
				bool keep = false;
				if (argc > 2) {
					for (unsigned int i = 2; i < argc; i++)
					{
						std::string arg = argv[i];
						if (arg == "-f")
						{
							if(argc < i+1)
								help("Missing argument!");
							inifilePath = argv[++i];
						}
						else if (arg == "--keep")
						{
							keep = true;
						}
						else {
							help(std::string("This argument is not part of the syntax. Argument:") + argv[i]);
						}
					}
				}
				if (inifilePath.empty())
				{
					if (!fs::exists(seasoninfofile))
					{
						help("Add a file name, if there was no file from which it was loaded.");
					}
					else {
						std::ifstream seasoninfo(seasoninfofile);
						std::getline(seasoninfo,inifilePath);
						inifilePath = INI::trim(inifilePath);
					}
					if (inifilePath.empty())
					{
						help("Add a file name, there was no file from which it was loaded.");
					}
				}
				
				save(inifilePath, keep);
				break;
			}
			case 3: {
				if (!fs::exists(inisgPath))
				{
					help("'get' and 'set' only work if an ini setup is done over 'new' or 'load'!");
				}
				
				if (argc < 6)
				{
					help("Not enougth arguments!");
				}

				std::string key = "",value = "";
				std::string section = "empty";
				for (uint32_t i = 2; i < argc; i++)
				{
					std::string arg = argv[i];
					if (arg == "-s")
					{
						if(argc < i+1)
							help("Missing argument!");
						section = argv[++i];
					}
					else if(arg == "-k") {
						if(argc < i+1)
							help("Missing argument!");
						key = argv[++i];
					}
					else if (arg == "-v")
					{
						if(argc < i+1)
							help("Missing argument!");
						value = argv[++i];
						if ((value = INI::trim(value)) == "-")
							value = "";
					}
					else
					{
						help(std::string("This argument is not part of the syntax. Argument:") + argv[i]);
					}

				}
				std::string setfile = inisgPath + section + "/" + key + ".val";
				if(!fs::exists(setfile))
					mkf(setfile);

				std::ofstream fout(setfile, std::ios::out | std::ios::trunc);
				fout << value;
				break;
			}
			case 4: {
				if (!fs::exists(inisgPath))
				{
					help("'get' and 'set' only work if an ini setup is done over 'new' or 'load'!");
				}
				if (argc < 4)
				{
					help("Not enougth arguments!");
				}
				bool clear = false;
				std::ios_base::openmode out = std::ios::out;
				std::string file = "";
				std::string key;
				std::string defvalue = "";
				std::string section = "empty";
				for (uint32_t i = 2; i < argc; i++)
				{
					std::string arg = argv[i];
					if (arg == "-s")
					{
						if(argc < i+1)
							help("Missing argument!");
						section = argv[++i];
					}
					else if(arg == "-k") {
						if(argc < i+1)
							help("Missing argument!");
						key = argv[++i];
					}
					else if (arg == "-v")
					{
						if(argc < i+1)
							help("Missing argument!");
						defvalue = argv[++i];
						if ((defvalue = INI::trim(defvalue)) == "-")
							defvalue = "";

					}
					else if (arg == "-f")
					{
						if(argc < i+1)
							help("Missing argument!");
						file = argv[++i];
					}
					else if (arg == "--delete")
					{
						clear = true;
					}
					else if (arg == "--trunc") 
					{
						out = out | std::ios::trunc;
					}
					else
					{
						help(std::string("This argument is not part of the syntax. Argument:") + argv[i]);
					}

				}

				if (INI::trim(key).empty())
				{
					help("For 'get' and 'set', the key needs a value!");
				}
				

				std::string getfile = inisgPath + section + "/" + key + ".val";
				if(!fs::exists(getfile))
					std::invalid_argument("This key does not exist in this section.");

				std::string value;
				std::ifstream fin(getfile, std::ios::in);
				fin >> value;
				if (INI::trim(value).empty())
				{
					value = defvalue;
				}
				if (!INI::trim(file).empty())
				{
					std::ofstream fout(file, out);
					fout << value;
				}
				if(clear)
					del(getfile);
				std::cout << value << std::endl;

				break;
			}
			case 5: {
				std::string file;
				bool force = false;
				if (argc > 2)
				{
					for (uint32_t i = 2; i < argc; i++)
					{
						std::string arg = argv[i];
						if (arg == "-f")
						{
							if(argc < i+1)
								help("Missing argument!");
							file = argv[++i];
						}
						else if(arg == "--force") 
						{
							force = true;
						}
						else
						{
							help(std::string("This argument is not part of the syntax. Argument:") + argv[i]);
						}
					}
				}
				if (fs::exists(inisgPath) && !force)
				{
					help("There is already a setup. Use 'clear' or 'save' to be able to create a new one.\nOr use '--force' to override.");
				}
				mkf(inisgPath, true);
				if(!file.empty()) {
					mkf(seasoninfofile, true);
					std::ofstream seasoninfo(seasoninfofile, std::ios::out | std::ios::trunc);
					seasoninfo << file;
				}
				break;
			}
			case 6: {
				bool force = false;
				if (argc > 2)
				{
					for (uint32_t i = 2; i < argc; i++)
					{
						std::string arg = argv[i];
						if(arg == "--force")
						{
							force = true;
						}
						else
						{
							help(std::string("This argument is not part of the syntax. Argument:") + arg);
						}
					}
				}
				if(!fs::is_empty(inisgPath) && !force) {
					char yn;
					std::cout << "Are you sure? Everything that is not saved in the ini file gets deleted." << std::endl;
					std::cout << "Do you want to clear? [y/n]\t";
					std::cin >> yn;
					yn = tolower(yn);
					if (yn == 'y')
					{
						del(inisgPath);
					}
					else if(yn == 'n') {
						break;
					}
					else {
						help("Try using the given characters!");
					}
				}
				del(inisgPath);
				break;
			}
			default:{
				help((std::string("There is no implementation for operator: ") + operators[op-1] + "\t\tNumber: " + std::to_string(op) + "\t\tID: " + std::to_string(op-1) + "\n").c_str());
				break;
			}
			}
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
