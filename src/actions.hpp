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