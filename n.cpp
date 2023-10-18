#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>

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

    
    void createFile(string fileName, string content) {
        files[fileName].fileName = fileName;
        FileVersion initialVersion;
        initialVersion.versionNumber = 1;
        initialVersion.content = content;
        files[fileName].versions.push_back(initialVersion);

        ofstream file(fileName);
        if (file.is_open()) {
            file << content;
            file.close();
            cout << "File created successfully." << endl;
        } else {
            cout << "Unable to create the file." << endl;
        }
    }

    void deleteFile(string fileName) {
        if (remove(fileName.c_str()) != 0) {
            perror("Error deleting file");
        } else {
            files.erase(fileName);
            cout << "File deleted successfully." << endl;
        }
    }

    void copyFile(string fileName, string newPath) {
        ifstream srcFile(fileName);
        ofstream destFile(newPath);
        destFile << srcFile.rdbuf();
        cout << "File copied successfully." << endl;
    }

    void moveFile(string fileName, string newPath) {
        ifstream srcFile(fileName);
        ofstream destFile(newPath);
        destFile << srcFile.rdbuf();
        srcFile.close();
        destFile.close();
        deleteFile(fileName);
        cout << "File moved successfully." << endl;
    }

    void addFileVersion(string fileName, string newContent) {
        ifstream file(fileName);
        string oldContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        ofstream newFile(fileName);
        newFile << oldContent + "\n" + newContent;
        newFile.close();
        FileVersion newVersion;
        newVersion.versionNumber = files[fileName].versions.back().versionNumber + 1;
        newVersion.content = newContent;
        files[fileName].versions.push_back(newVersion);
        cout << "New version added successfully." << endl;
    }

    
    
};

int main() {
    FileSystem fileSystem;
    fileSystem.createFile("example.txt", "Initial content of the file.");

    //Copying and moving file example
    fileSystem.copyFile("example.txt", "C:/Users/Dell/OneDrive/Desktop/acc/.vscode/oopS/example.txt");

    //copyfile

    //moving file


    fileSystem.moveFile("example.txt", "C:/Users/Dell/OneDrive/Desktop/acc/.vscode/patterns/example.txt");

    // Adding new version example
    fileSystem.addFileVersion("C:/Users/Dell/OneDrive/Desktop/acc/.vscode/patterns/example.txt", "New content added.");

    // Reverting to an older version example
    

    //fileSystem.revertToFileVersion("C:/Users/Dell/OneDrive/Desktop/acc/.vscode/DP/files/example.txt", 1);
    fileSystem.deleteFile("example.txt");

    return 0;
}
