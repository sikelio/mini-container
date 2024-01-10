#include "./src/headers/main.h"

int main(int argc, char** argv) {
    char *chrootDir;

    if (!argv[1]) {
        printf("no chroot directory entered\n");

        return 1;
    }

    chrootDir = argv[1];

    const char *subDirs[] = { "", "/bin", "/lib64", "/lib", "/lib/x86_64-linux-gnu" };
    int subDirsCount = sizeof(subDirs) / sizeof(subDirs[0]);

    FilePath libFiles[] = {
        { "/bin/bash", "/home/sik/chroot/bin/" },
        { "/bin/ps", "/home/sik/chroot/bin/" },
        { "/bin/kill", "/home/sik/chroot/bin/" },
        { "/bin/ls", "/home/sik/chroot/bin/" },

        { "/lib/x86_64-linux-gnu/librt.so.1", "/home/sik/chroot/lib/x86_64-linux-gnu/" },
        { "/lib/x86_64-linux-gnu/libpthread.so.0", "/home/sik/chroot/lib/x86_64-linux-gnu/" },
        { "/lib/x86_64-linux-gnu/libpcre2-8.so.0", "/home/sik/chroot/lib/x86_64-linux-gnu/" },
        { "/lib/x86_64-linux-gnu/libselinux.so.1", "/home/sik/chroot/lib/x86_64-linux-gnu/" },
        { "/lib/x86_64-linux-gnu/libprocps.so.8", "/home/sik/chroot/lib/x86_64-linux-gnu/" },
        { "/lib/x86_64-linux-gnu/libtinfo.so.6", "/home/sik/chroot/lib/x86_64-linux-gnu/" },
        { "/lib/x86_64-linux-gnu/libc.so.6", "/home/sik/chroot/lib/x86_64-linux-gnu/" },
        { "/lib/x86_64-linux-gnu/libsystemd.so.0", "/home/sik/chroot/lib/x86_64-linux-gnu/" },
        { "/lib/x86_64-linux-gnu/liblzma.so.5", "/home/sik/chroot/lib/x86_64-linux-gnu/" },
        { "/lib/x86_64-linux-gnu/libzstd.so.1", "/home/sik/chroot/lib/x86_64-linux-gnu/" },
        { "/lib/x86_64-linux-gnu/liblz4.so.1", "/home/sik/chroot/lib/x86_64-linux-gnu/" },
        { "/lib/x86_64-linux-gnu/libcap.so.2", "/home/sik/chroot/lib/x86_64-linux-gnu/" },
        { "/lib/x86_64-linux-gnu/libgcrypt.so.20", "/home/sik/chroot/lib/x86_64-linux-gnu/" },
        { "/lib/x86_64-linux-gnu/libgpg-error.so.0", "/home/sik/chroot/lib/x86_64-linux-gnu/" },
        { "/lib/x86_64-linux-gnu/libdl.so.2", "/home/sik/chroot/lib/x86_64-linux-gnu/" },

        { "/lib64/ld-linux-x86-64.so.2", "/home/sik/chroot/lib64/" },
    };
    int libFilesCount = sizeof(libFiles) / sizeof(libFiles[0]);

    if (unshare(CLONE_NEWPID) < 0) {
        perror("unshare error");

        return 1;
    }

    for (int i = 0; i < subDirsCount; i++) {
        if (createDir(chrootDir, subDirs[i]) == 1) {
            return 1;
        }
    }

    for (int i = 0; i < libFilesCount; i++) {
        if (copyFile(libFiles[i]) == 1) {
            return 1;
        }
    }

    pid_t pid = fork();

    switch (pid) {
        case -1:
            perror("error fork");
            exit(1);
            break;
        case 0:
            if (unshare(CLONE_NEWNS) == -1) {
                perror("unshare error");
                exit(1);
            }

            if (chroot(chrootDir) == -1) {
                perror("chroot error");
                exit(1);
            }

            if (chdir("/") == -1) {
                perror("chdir error");
                exit(1);
            }

            if (mkdir("/proc", 0755) == -1 && errno != EEXIST) {
                perror("proc mkdir error");

                exit(1);
            }

            if (mount("proc", "proc", "proc", 0, NULL) == -1) {
                perror("mount error");
                exit(1);
            }

            execlp("/bin/bash", "bash", NULL);
            perror("execlp error");
            exit(1);
            break;
    }

    int status;

    waitpid(pid, &status, 0);
    
    return 0;
}
