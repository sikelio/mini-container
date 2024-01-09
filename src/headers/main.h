#include <unistd.h>
#include <sys/wait.h>
#include <sys/mount.h>

#include "file-handler.h"

#define _GNU_SOURCE
#define CLONE_NEWPID 0x00000200
#define CLONE_NEWNS 0x00020000
