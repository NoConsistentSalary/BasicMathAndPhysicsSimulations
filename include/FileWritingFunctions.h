#pragma once

#include <string>
#include <fstream>

class FileHandler
{
public:

	FileHandler(std::string filelocation, std::string outputfileName)
	{
		file_location = filelocation;
		deleteFileLocationEnd();
		outfile = std::ofstream(file_location + "\\"+ outputfileName);//"vastaukset.md"
	}

	~FileHandler()
	{
		if (outfile.is_open())
		{
			printf("outfile closed\n");
			outfile.close();
		}
	}

	void writeLineInFile(std::string s)
	{
		outfile << s;
	}

	std::string getFilelocation() { return file_location; }

private:

	void deleteFileLocationEnd()
	{

		for (size_t i = file_location.length() - 1; i != 0; i--)
		{
			if (file_location[i] == '\\')
			{
				file_location.erase(i, file_location.length() - 1);
				break;
			}
		}
	}

	std::string file_location;
	std::ofstream outfile;
};