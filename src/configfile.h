#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

struct ConfigFile {
	std::wstring path;
	bool usePercentVelocity = false;
	bool oppositeChordsAfterCurMode = true;
	bool swapBorrowedChords = false;
	float DG0 = 0;
	float DG1 = 0;
	float DG2 = 0;
	float DG3 = 0; 
	float RG0 = 0;
	float RG1 = 0;
	float RG2 = 0;
	float RG3 = 0;
	std::string defaultShortName = "custom_song";
	void saveConfig(const std::wstring& configFile) {
		std::ofstream outFile(configFile, std::ios_base::binary);
		outFile.write("usePercVel\x00", 11);
		outFile.write(usePercentVelocity ? "1\x00" : "0\x00", 2);
		outFile.write("defaultShortName\x00", 17);
		outFile.write(defaultShortName.c_str(), strlen(defaultShortName.c_str()));
		outFile.write("\x00", 1);
		outFile.write("oppositeChordsAfterCurMode\x00", 27);
		outFile.write(oppositeChordsAfterCurMode ? "1\x00" : "0\x00", 2);
		outFile.write("swapBorrowedChords\x00", 19);
		outFile.write(swapBorrowedChords ? "1\x00" : "0\x00", 2);
		outFile.write("DG0\x00", 4);
		outFile.write(std::to_string(DG0).c_str() , strlen(std::to_string(DG0).c_str())); 
		outFile.write("\x00", 1); 
		outFile.write("DG1\x00", 4);
		outFile.write(std::to_string(DG1).c_str(), strlen(std::to_string(DG1).c_str()));
		outFile.write("\x00", 1);
		outFile.write("DG2\x00", 4);
		outFile.write(std::to_string(DG2).c_str(), strlen(std::to_string(DG2).c_str()));
		outFile.write("\x00", 1);
		outFile.write("DG3\x00", 4);
		outFile.write(std::to_string(DG3).c_str(), strlen(std::to_string(DG3).c_str()));
		outFile.write("\x00", 1);
		outFile.write("RG0\x00", 4);
		outFile.write(std::to_string(RG0).c_str(), strlen(std::to_string(RG0).c_str()));
		outFile.write("\x00", 1);
		outFile.write("RG1\x00", 4);
		outFile.write(std::to_string(RG1).c_str(), strlen(std::to_string(RG1).c_str()));
		outFile.write("\x00", 1);
		outFile.write("RG2\x00", 4);
		outFile.write(std::to_string(RG2).c_str(), strlen(std::to_string(RG2).c_str()));
		outFile.write("\x00", 1);
		outFile.write("RG3\x00", 4);
		outFile.write(std::to_string(RG3).c_str(), strlen(std::to_string(RG3).c_str()));
		outFile.write("\x00", 1);
		outFile.close();
	}
	void loadConfig(const std::wstring& configFile) {

		if (std::filesystem::exists(configFile)) {
			std::ifstream inFile(configFile, std::ios_base::binary);
			if (inFile.is_open()) {
				std::string value;  // To store each value
				char byte;  // To read bytes from the file
				std::string curRead = "NONE";
				while (inFile.get(byte)) {
					if (byte == '\0') {
						// Null terminator encountered, process the value
						if (curRead == "NONE") {
							curRead = value;
						}
						else {
							if (curRead == "usePercVel") {
								if (value == "0")
									usePercentVelocity = false;
								else
									usePercentVelocity = true;
								curRead = "NONE";
							}
							else if (curRead == "defaultShortName") {
								defaultShortName = value;
								curRead = "NONE";
							}
							else if (curRead == "oppositeChordsAfterCurMode") {
								if (value == "0")
									oppositeChordsAfterCurMode = false;
								else
									oppositeChordsAfterCurMode = true;
								curRead = "NONE";
							}
							else if (curRead == "swapBorrowedChords") {
								if (value == "0")
									swapBorrowedChords = false;
								else
									swapBorrowedChords = true;
								curRead = "NONE";
							}
							else if (curRead == "DG0") {
								DG0 = std::stof(value);
								curRead = "NONE";
							}
							else if (curRead == "DG1") {
								DG1 = std::stof(value);
								curRead = "NONE";
							}
							else if (curRead == "DG2") {
								DG2 = std::stof(value);
								curRead = "NONE";
							}
							else if (curRead == "DG3") {
								DG3 = std::stof(value);
								curRead = "NONE";
							}
							else if (curRead == "RG0") {
								RG0 = std::stof(value);
								curRead = "NONE";
							}
							else if (curRead == "RG1") {
								RG1 = std::stof(value);
								curRead = "NONE";
							}
							else if (curRead == "RG2") {
								RG2 = std::stof(value);
								curRead = "NONE";
							}
							else if (curRead == "RG3") {
								RG3 = std::stof(value);
								curRead = "NONE";
							}
						}

						// Clear the string for the next value
						value.clear();
					}
					else {
						// Append the byte to the current value
						value.push_back(byte);
					}
				}

				inFile.close();
			}
			else {
				std::cerr << "Failed to open the file." << std::endl;
			}
		}
		else {
			saveConfig(configFile);
		}


	}
};