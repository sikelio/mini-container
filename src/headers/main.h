#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <errno.h>

#define CLONE_NEWPID 0x00000200
#define CLONE_NEWNS 0x00020000
