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
    std::string defaultShortName = "custom_song";
    void saveConfig(const std::wstring& configFile) {
        std::ofstream outFile(configFile, std::ios_base::binary);
        outFile.write("usePercVel\x00", 11);
        outFile.write(usePercentVelocity ? "1\x00" : "0\x00", 2);
        outFile.write("defaultShortName\x00", 17);
        outFile.write(defaultShortName.c_str(), strlen(defaultShortName.c_str()));
        outFile.write("\x00",1);
        outFile.write("oppositeChordsAfterCurMode\x00", 27);
        outFile.write(oppositeChordsAfterCurMode ? "1\x00" : "0\x00", 2);
        outFile.write("swapBorrowedChords\x00", 27);
        outFile.write(swapBorrowedChords ? "1\x00" : "0\x00", 2);
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
                            }
                            else if (curRead == "defaultShortName") {
                                defaultShortName = value;
                            }
                            else if (curRead == "oppositeChordsAfterCurMode") {
                                if (value == "0")
                                    oppositeChordsAfterCurMode = false;
                                else
                                    oppositeChordsAfterCurMode = true;
                            }
                            else if (curRead == "swapBorrowedChords") {
                                if (value == "0")
                                    swapBorrowedChords = false;
                                else
                                    swapBorrowedChords = true;
                            }
                            curRead = "NONE";
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