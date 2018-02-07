#pragma once

#define ZIPHELPER_REPLACE 0
#define ZIPHELPER_ADD 1

#define ZIPHELPER_KEEP_FILES 0
#define ZIPHELPER_CLEANUP_FILES 1

int unzipAndLoad(char *filename, int (*fileCallback)(char *filename), char *expectedComment, int keepFiles);
int zipFiles(char *filename, char **files, int fileCount, int mode, char *comment);
