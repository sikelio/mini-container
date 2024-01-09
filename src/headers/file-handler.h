#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "file-path.h"

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

int createDir(const char *baseDir, const char *subDir);
int copyFile(const FilePath file);

#endif
