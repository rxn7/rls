#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  bool hidden_files;
} flags_t;

void evaluate_flags(flags_t *flags, const char *str) {
  for (int j = 1; j < strlen(str); ++j) {
    const char c = str[c];
    switch (c) {
    case 'a':
      flags->hidden_files = true;
      break;

    default:
      fprintf(stderr, "Unknown flag: %c\n\n", c);
      break;
    }
  }
}

int main(int argc, const char **argv) {
  flags_t flags = {
      .hidden_files = false,
  };

  const char *path = "./";

  for (int i = 1; i < argc; ++i) {
    const char *arg = argv[i];

    if (arg[0] == '-') {
      evaluate_flags(&flags, arg);
    } else {
      path = arg;
    }
  }

  char absolute_path[4096];
  path = realpath(path, absolute_path);

  DIR *dir = opendir(absolute_path);
  if (!dir) {
    fprintf(stderr, "Path is not a directory: %s\n", absolute_path);
    return -1;
  }

  unsigned int i = 0;
  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
      if (!flags.hidden_files && entry->d_name[0] == '.')
        continue;

      printf("%s\n", entry->d_name);
    }

    ++i;
  }

  closedir(dir);
}
