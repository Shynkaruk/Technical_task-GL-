#include "file_search.h"
#include <thread>
#include <filesystem>
#include <iostream>
#include <mutex>

using namespace std;

string searchFileInDirectory(const std::string& directory, const std::string& filename) {
    for (const auto& entry : filesystem::recursive_directory_iterator(directory)) {
        if (entry.is_regular_file() && entry.path().filename().string() == filename) {
            return entry.path().string();
        }
    }

    return ""; // ��������� ������� �����, ���� ���� �� ��������
}

std::string searchFileByName(const std::string& directory, const std::string& filename) {

    string result = "";
    vector<std::thread> threads;
    mutex resultMutex;

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_directory()) {
            if (threads.size() < 8) {
                threads.emplace_back([&result, &resultMutex, &entry, &filename]() {
                    std::string foundPath = searchFileInDirectory(entry.path().string(), filename);
                if (!foundPath.empty()) {
                    std::lock_guard<mutex> lock(resultMutex);
                    if (result.empty()) {
                        result = foundPath;
                    }
                }
                    });
            }
            else {
                // ������� ���������� ������, ���� ����������� ������� ���������
                for (auto& thread : threads) {
                    thread.join();
                }
                threads.clear();
            }
        }
    }

    // ������� ���������� ������, ���� ���� � ��� �� ����������
    for (auto& thread : threads) {
        thread.join();
    }

    return result; // ��������� ���� �� ���������� ����� ��� ������� �����, ���� ���� �� ��������
}
