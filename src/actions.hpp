#pragma once 

#include "utils.hpp"
#include "ini.h"

bool save(const std::string& path, bool keep = false) {
    INI inifile;
    for (auto& dir : fs::directory_iterator(fs::path(inisgPath)))
    {
        if(dir.is_directory()) {
            std::string dirpath = dir.path().string();
            std::string dirname = INI::trim(dirpath.substr(dirpath.find_last_of("/\\") + 1));
            if(inifile.count(dirname) > 0)
                throw std::logic_error("There are multiple sections with the same name...");
            else
                inifile[dirname] = {};
            for (auto& fdir : fs::directory_iterator(dir))
            {
                if (fdir.is_regular_file())
                {
                    std::string filename = fdir.path().filename().string();
                    std::string key = INI::trim(filename.substr(0, filename.find_last_of(".")));
                    std::ifstream fin(fdir.path(), std::ios::in);
                    std::string value;
                    std::getline(fin,value);
                    value = INI::trim(value);
                    if(inifile.at(dirname).count(key) > 0) {
                        throw std::logic_error("There are multiple keys with the same name...\n\t" + dirname + "\t" + key + "\t" + value);
                    }
                    else {
                        inifile(dirname,key) = value;
                    }
                }
            }
        }
    }
    inifile.save(path);
    if(!keep)
        del(inisgPath);
    return true;
}

bool load(const std::string& path, bool force = false) {
    if (!fs::exists(inisgPath) || force)
    {
        std::ofstream fout;
        mkf(inisgPath, force);
        INI ini;
        ini.load(path);
        for(Table& section : ini) {
            std::string sectionPath = inisgPath + section.first + "/";
            if(createDir(sectionPath)) {
                for (KeyValue& kv : section.second)
                {
                    std::string keyFile = sectionPath + kv.first + ".val";
                    if(createFile(keyFile, false, true)) {
                        fout.open(keyFile);
                        fout << kv.second;
                        fout.close();
                    }
                }

            }

        }
        mkf(seasoninfofile, true);
        fout.open(seasoninfofile);
        fout << path;
    }
    else {
        throw std::logic_error("There is allready an ini loaded! 'save' or 'clear' to load a new ini-file.");
    }
    return true;
}

void inside(uint8_t op, int argc ,char** argv) {
    std::string file;
    switch (op)
    {
    case 1: {
        std::string section = "empty";
        std::string key = "";
        std::string value;
        for (uint32_t i = 3; i < argc; i++)
        {
            std::string arg = argv[i];
            if (arg == "-f")
            {
                if(argc < i+1)
					helpInside("Missing argument!");
                file = argv[++i];
            }
            else if (arg == "-s") {
                if(argc < i+1)
					helpInside("Missing argument!");
                section = argv[++i];
            }
            else if (arg == "-k") {
                if(argc < i+1)
					helpInside("Missing argument!");
                key = argv[++i];
            }
            else if (arg == "-v") {
                if(argc < i+1)
					helpInside("Missing argument!");
                value = argv[++i];
                if ((value = INI::trim(value)) == "-")
							value = "";
            }
            else {
                helpInside(arg + " is not a valid argument.");
            }
        }
        break;
    }
    case 2: {
        std::string section = "empty";
        std::string key = "";
        std::string value = "";

        std::string outf = "";
        std::ios_base::openmode outmode = std::ios::out;
        bool bfisout = false; // the next `-f`'s are the output file
        for (uint32_t i = 3; i < argc; i++)
        {
            std::string arg = argv[i];
            if (arg == "-f")
            {
                if(argc < i+1)
					helpInside("Missing argument!");
                if (bfisout)
                    outf = argv[++i];
                else
                    file = argv[++i];
            }
            else if (arg == "-s") {
                if(argc < i+1)
					helpInside("Missing argument!");
            }
            else if (arg == "-k") {
                if(argc < i+1)
					helpInside("Missing argument!");
            }
            else if (arg == "-v") {
                if(argc < i+1)
					helpInside("Missing argument!");
                value = argv[++i];
                if ((value = INI::trim(value)) == "-")
							value = "";
            }
            else if (arg == "--out") {
                bfisout = true;
            }
            else if (arg == "--trunc") {
                outmode |= std::ios::trunc;
            }
            else {
                helpInside(arg + " is not a valid argument.");
            }
        }
    }
    case 3: {
        for (uint32_t i = 3; i < argc; i++)
        {
            std::string arg = argv[i];
            if (arg == "-f")
            {
                if(argc < i+1)
					helpInside("Missing argument!");
                file = argv[++i];
            }
            else if (arg == "-s") {
                if(argc < i+1)
					helpInside("Missing argument!");
            }
            else if (arg == "-k") {
                if(argc < i+1)
					helpInside("Missing argument!");
            }
            else {
                helpInside(arg + " is not a valid argument.");
            }
        }
    }
    case 4: {
        std::string fromFile;
        bool bfisfrom = false;
        for (uint32_t i = 3; i < argc; i++)
        {
            std::string arg = argv[i];
            if (arg == "-f")
            {
                if(argc < i+1)
					helpInside("Missing argument!");
                if(bfisfrom)
                    fromFile = argv[++i];
                else
                    file = argv[++i];
            }
            else {
                helpInside(arg + " is not a valid argument.");
            }
        }
    }
    default:
        break;
    }
}