#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

// Structure for file version
struct FileVersion {
    int versionNumber;
    string content;
};

// Structure for File
struct File {
    string fileName;
    vector<FileVersion> versions;
};

class FileSystem {
private:
    unordered_map<string, File> files;

public:
    bool getFile(string fileName) {
        return files.find(fileName) != files.end();
    }
    
    void createFile(string fileName, string content) {
        File newFile;
        newFile.fileName = fileName;
        FileVersion initialVersion;
        initialVersion.versionNumber = 1;
        initialVersion.content = content;
        newFile.versions.push_back(initialVersion);
        files[fileName] = newFile;
    }

    void deleteFile(string fileName) {
        files.erase(fileName);
    }

    void copyFile(string fileName, string newPath) {
        if (files.find(fileName) != files.end()) {
            files[newPath] = files[fileName];
        } else {
            cout << "File not found." << endl;
        }
    }

    void moveFile(string fileName, string newPath) {
        if (files.find(fileName) != files.end()) {
            files[newPath] = files[fileName];
            files.erase(fileName);
        } else {
            cout << "File not found." << endl;
        }
    }

    void addFileVersion(string fileName, string newContent) {
        if (files.find(fileName) != files.end()) {
            FileVersion newVersion;
            newVersion.versionNumber = files[fileName].versions.back().versionNumber + 1;
            newVersion.content = newContent;
            files[fileName].versions.push_back(newVersion);
        } else {
            cout << "File not found." << endl;
        }
    }

    void revertToFileVersion(string fileName, int versionNumber) {
        if (files.find(fileName) != files.end()) {
            for (auto& version : files[fileName].versions) {
                if (version.versionNumber == versionNumber) {
                    files[fileName].versions.resize(versionNumber);
                    break;
                }
            }
        } else {
            cout << "File not found." << endl;
        }
    }
};

int main() {
    FileSystem fileSystem;
    fileSystem.createFile("example1.txt", "Initial content of the file.");
    if (fileSystem.getFile("example1.txt")) {
        cout << "File created successfully." << endl;
    } else {
        cout << "Failed to create the file." << endl;
    }

    // // Copying and moving file example
    // fileSystem.copyFile("example.txt", "newPath/example.txt");
    // fileSystem.moveFile("example.txt", "newPath/example.txt");

    // // Adding new version example
    // fileSystem.addFileVersion("newPath/example.txt", "New content added.");

    // // Reverting to an older version example
    // fileSystem.revertToFileVersion("newPath/example.txt", 1);

    return 0;
}
