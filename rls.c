#include <stdio.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, const char **argv) {
        char cwd[4096];
        getcwd(cwd, 4096);

        DIR *dir = opendir(cwd);
        if(!dir) {
                printf("Failed to open current working directory!\n");
                return -1;
        }

        struct dirent *entry;
        while((entry = readdir(dir)) != NULL) {
                if(entry->d_type != 4) { /* Entries of type 4 are: '.' and '..'. */
                        printf("%s | ", entry->d_name);
                }
        }
        
        closedir(dir);
}
