#include "../headers/file-handler.h"
#include "../headers/file-path.h"

int createDir(const char *baseDir, const char *subDir) {
    char fullPath[100];

    snprintf(fullPath, sizeof(fullPath), "%s%s", baseDir, subDir);

    if (mkdir(fullPath, 0755) == -1 && errno != EEXIST) {
        perror("mkdir error");

        return 1;
    }

    return 0;
}

int copyFile(const FilePath file) {
    char command[1024];

    snprintf(command, sizeof(command), "cp %s %s", file.sourcePath, file.destPath);

    if (system(command) == -1) {
        perror("copy file error");

        return 1;
    }

    return 0;
}
