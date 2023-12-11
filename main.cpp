#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

typedef unsigned char BYTE;

std::vector<BYTE> readFile(const char* filename)
{

	// open the file
	std::streampos begin,end,fileSize;
	std::ifstream file(filename, std::ios::binary);

	// get its size

	begin = file.tellg();
	file.seekg(0, std::ios::end);
	end = file.tellg();
	fileSize = end - begin;


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

	// get the binary
	int byteIndex = 0;
	std::string asmOperation;
	std::string opCode;
	std::string MOD;
	std::string RM;
	std::string REG;
	bool WIDE = false;
	bool DIRECTION = false;
	std::cout << "bits 16\n" << std::endl;
	for (char byte: fileData) {
		std::string byteString = std::bitset<8>(byte).to_string();
		if(byteIndex == 0) {
			if(byteString.substr(0, 6) == "100010") {
				asmOperation = "move";
				DIRECTION = byteString.substr(6, 1) == "1";
				WIDE = byteString.substr(7, 1) == "1";
				byteIndex = 1;
			} else if(byteString.substr(0, 4) == "1011") {
				asmOperation = "immediateToRegister";
				byteIndex = 1;
			} else {
				byteIndex = 0;
			}
		} else if(byteIndex == 1) {
			if(asmOperation == "move") {
				MOD = byteString.substr(0, 2);
				opCode = "mov ";
				if(MOD == "11") {
					REG = byteString.substr(2, 3);
					RM = byteString.substr(5, 3);
					if(WIDE) {
						if(REG == "000") {
							opCode = opCode + "ax, ";
						}
						else if(REG == "001") {
							opCode = opCode + "cx, ";
						}
						else if(REG == "010") {
							opCode = opCode + "dx, ";
						}
						else if(REG == "011") {
							opCode = opCode + "bx, ";
						}
						else if(REG == "100") {
							opCode = opCode + "sp, ";
						}
						else if(REG == "101") {
							opCode = opCode + "bp, ";
						}
						else if(REG == "110") {
							opCode = opCode + "si, ";
						}
						else if(REG == "111") {
							opCode = opCode + "di, ";
						}
					} else {
						if(REG == "000") {
							opCode = opCode + "al, ";
						}
						else if(REG == "001") {
							opCode = opCode + "cl, ";
						}
						else if(REG == "010") {
							opCode = opCode + "dl, ";
						}
						else if(REG == "011") {
							opCode = opCode + "bl, ";
						}
						else if(REG == "100") {
							opCode = opCode + "ah, ";
						}
						else if(REG == "101") {
							opCode = opCode + "ch, ";
						}
						else if(REG == "110") {
							opCode = opCode + "dh, ";
						}
						else if(REG == "111") {
							opCode = opCode + "bh, ";
						}
					}
					if(WIDE) {
						if(RM == "000") {
							opCode = opCode + "ax";
						}
						else if(RM == "001") {
							opCode = opCode + "cx";
						}
						else if(RM == "010") {
							opCode = opCode + "dx";
						}
						else if(RM == "011") {
							opCode = opCode + "bx";
						}
						else if(RM == "100") {
							opCode = opCode + "sp";
						}
						else if(RM == "101") {
							opCode = opCode + "bp";
						}
						else if(RM == "110") {
							opCode = opCode + "si";
						}
						else if(RM == "111") {
							opCode = opCode + "di";
						}
					} else {
						if(RM == "000") {
							opCode = opCode + "al";
						}
						else if(RM == "001") {
							opCode = opCode + "cl";
						}
						else if(RM == "010") {
							opCode = opCode + "dl";
						}
						else if(RM == "011") {
							opCode = opCode + "bl";
						}
						else if(RM == "100") {
							opCode = opCode + "ah";
						}
						else if(RM == "101") {
							opCode = opCode + "ch";
						}
						else if(RM == "110") {
							opCode = opCode + "dh";
						}
						else if(RM == "111") {
							opCode = opCode + "bh";
						}
					}
				}
				std::cout << opCode << std::endl;
				byteIndex = 0;
			}
		}
	}

	return 0;
}

