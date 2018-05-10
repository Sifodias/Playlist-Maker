#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>

std::vector<std::string> findNames(std::string folder)
{
	std::vector<std::string> types = { ".mp3", ".mp4", ".m4a", ".webm", ".flac", ".mkv" };
	std::vector<std::string> names;
	for (std::vector<std::string>::iterator i = types.begin(); i != types.end(); i++) {
		char path[200];
		sprintf_s(path, ("%s/*" + (*i)).c_str(), folder.c_str());
		WIN32_FIND_DATA data;
		HANDLE finder = ::FindFirstFile(path, &data);
		if (finder != INVALID_HANDLE_VALUE) {
			do {
				if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
					names.push_back(data.cFileName);
			} while (::FindNextFile(finder, &data));
			::FindClose(finder);
		}
	}
	return names;
}


int main()
{
	std::ofstream pls("./pls.m3u");
	std::vector<std::string> names = findNames("./");
	for (unsigned int i = 0; i < names.size(); i++) {
		pls << names[i].c_str();
		pls << std::endl;
	}

	return 0;
}