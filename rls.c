#include <stdio.h>
#include <string.h>
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
                if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                        printf("%s | ", entry->d_name);
                }
        }
        
        closedir(dir);
}
