#include <iostream>
#include <fstream>
#include <string>

// replace s1 by s2 in the line and return the modified line
std::string replaceAll(std::string str, std::string s1, std::string s2) {
	std::string result = "";
	size_t pos = 0;
	size_t found;

	while ((found = str.find(s1, pos)) != std::string::npos) {
		result += str.substr(pos, found - pos);
		result += s2;
		pos = found + s1.length();
	}

	result += str.substr(pos);

	return result;
}

int main(int argc, char **argv) {
	if (argc != 4) {
		std::cerr << "Usage: ./replace <filename> <s1> <s2>" << std::endl;
		return 1;
	}

	std::string filename = argv[1];
	std::string s1 = argv[2];
	std::string s2 = argv[3];

	if (s1.empty()) {
		std::cerr << "Error: s1 cannot be empty" << std::endl;
		return (1);
	}

	// open file
	std::ifstream infile(filename.c_str());
	if (!infile.is_open()) {
		std::cerr << "Error: cannot open file" << filename << std::endl;
		return 1;
	}

	// output file stream file
	std::ofstream outfile((filename + ".replace").c_str());
	if (!outfile.is_open()) {
		std::cerr << "Error: Cannot create output file" << std::endl;
		infile.close();
		return 1;
	}

	// gnl for replaceAll
	std::string line;
	while (std::getline(infile, line)) {
		outfile << replaceAll(line, s1, s2) << std::endl;
	}

	infile.close();
	outfile.close();

	return 0;
}
