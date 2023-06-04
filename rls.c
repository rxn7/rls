#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, const char **argv) {
  char cwd[4096];
  getcwd(cwd, 4096);

  DIR *dir = opendir(cwd);
  if (!dir) {
    fprintf(stderr, "Failed to open current working directory!\n");
    return -1;
  }

  unsigned int i = 0;
  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
      if (i != 0)
        fputs(" | ", stdout);

      printf("%s", entry->d_name);
    }

    ++i;
  }

  closedir(dir);
}
