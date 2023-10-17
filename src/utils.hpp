#pragma once

#if !defined(__utl_NoIncludes__) && !defined(__utl_skipIncludes__) 
#   ifndef __has_include
     static_assert(false, "__has_include not supported");
#   else // has __has_include
#      ifndef __utl_NoString__
#          if __has_include(<string>)
#              include <string>
#          else
#              define __utl_NoString__
#          endif
#      endif // __utl_NoString__

#      ifndef __utl_NoVector__
#          if __has_include(<vector>)
#              include <vector>
#          else
#              define __utl_NoVec__
#          endif
#      endif // __utl_NoVector__

#      ifndef __utl_NoFilesystem__
#          if __has_include(<filesystem>)
#              include <filesystem>
               namespace fs = std::filesystem;
#          else
#              define __utl_NoFilesystem__
#          endif
#      endif // __utl_NoFilesystem__


#      ifndef __utl_NoFileStream__
#          if __has_include(<fstream>)
#              include <fstream>
#          else
#              define __utl_NoFileStream__
#          endif
#      endif // __utl_NoFileStream__

#      ifndef __utl_NoIOStream__
#          if __has_include(<iostream>)
#              include <iostream>
#          else
#              define __utl_NoIOStream__
#          endif
#      endif // __utl_NoIOStream__
#   endif // __has_include
#else
#   if defined(__utl_NoIncludes__) && !defined(__utl_skipIncludes__)
#       define __utl_NoString__
#       define __utl_NoVector__
#       define __utl_NoFilesystem__
#       define __utl_NoFileStream__
#       define __utl_NoIOStream__
#   endif // !defined(__utl_skipIncludes__) && defined(__utl_noIncludes__)
#endif // __utl_NoIncludes__

#ifndef __utl_NoVector__

template<typename T, typename tsize = size_t>
tsize inVector(T& val, std::vector<T> vec) {
	for (tsize i = 0; i < vec.size(); i++)
		if (val == vec[i])
			return i+1;
	return 0;
}

#endif // __utl_NoVec__




#ifndef __utl_NoFilesystem__

bool createDir(std::string& path) {
    return fs::create_directories(path);
}

bool deleteDir(std::string& path, bool recursive = false) {
    if (recursive)
        fs::remove_all(path);
    else
        fs::remove(path);
    return true;
}

bool createFile(std::string& file, bool createDir = false, bool override = false) {
    std::filesystem::path path{ file };
    if (createDir) {
#ifdef __utl_NoFileStream__
        return std::filesystem::create_directories(path.parent_path()); //add directories based on the object path
#else
        std::filesystem::create_directories(path.parent_path()); //add directories based on the object path
#endif
    }
#ifndef __utl_NoFileStream__
    if(!fs::exists(path) || override) {
        std::ofstream fout(path, std::ios::trunc);
        return fout.is_open();
    }
    return false;
#endif
}

bool deleteFile(std::string& file) {
    return fs::remove(file);
}

bool copy(std::string& from, std::string& to, bool contents = false) {
    if(contents)
        return fs::copy_file(from, to);
    fs::copy(from, to);
    return fs::exists(to);
}


bool del(std::string& path) {
    return fs::remove_all(path);
}

bool mkf(std::string& path, bool clear = false) {
    if (fs::is_directory(path)) {
        if (clear) { fs::remove_all(path); }
        return createDir(path);
    }
    else {
        return createFile(path, true, clear);
    }
}

#endif // __utl_NoFilesystem__