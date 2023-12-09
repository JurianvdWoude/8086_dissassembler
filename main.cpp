#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

typedef unsigned char BYTE;

std::vector<BYTE> readFile(const char* filename)
{
	printf("Trying to open: %s\n", filename);

	// open the file
	std::streampos begin,end,fileSize;
	std::ifstream file(filename, std::ios::binary);

	// get its size

	begin = file.tellg();
	file.seekg(0, std::ios::end);
	end = file.tellg();
	fileSize = end - begin;

	printf("filesize is %d\n", (int)fileSize);

	// read the data
	file.seekg(0, std::ios::beg);
	std::vector<BYTE> fileData(fileSize);
	file.read((char*) &fileData[0], fileSize);
	file.close();

	return fileData; 
}

int main(int argc, char* argv[])
{
	// make sure a filename is given
	if(argc == 1) {
		printf("No filename was given\n");
		return 1;
	}
	if(argc > 2) {
		printf("You have entered %d arguments:\n", argc - 1);
		printf("Too many arguments given\n");
		return 1;
	}

	// store the filename
	const char* filename = argv[1];

	// get the file contents
	std::vector<BYTE> fileData = readFile(filename);
	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

	// get the binary
	for (char byte: fileData) {
		std::cout << std::bitset<8>(byte).to_string() << std::endl;
	}

	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
	printf("Finished reading the file\n");
	return 0;
}

