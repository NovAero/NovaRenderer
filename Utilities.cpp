#include "Utilities.h"
#include <sstream>
#include <fstream>

std::string LoadFileAsString(std::string filePath)
{
	std::stringstream output;
	std::ifstream file;

	file.open(filePath, std::ios::in);

	if (file.is_open()) {
		output << file.rdbuf();

		file.close();
		return output.str();
	}

	return "";
}
