// cat.c 
// Author: jcolours 
// Date: 2026-06-12
// Description: Simple remake of the basic cat unix tool using C, 
// C libraries, and C sys calls to the kernel

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
  if (argc > 1)
  {
    for (int i=1; i < argc; i++)
    {
      int fd;

      if ((fd = open(argv[i], O_RDONLY)) == -1)
      {
        perror("\nopen");
        exit(EXIT_FAILURE);
      }

      char buf[4096];

      size_t size;
      if ((size = read(fd, buf, sizeof(buf))) == -1)
      {
        perror("\nread");
        exit(EXIT_FAILURE);
      }

      buf[size] = '\0';

      printf("%s", buf);

      close(fd);
    }
  }
  else 
  {
    int fd = 0;

    char buf[4096];

    size_t size = 1;

    while (size > 0) // reason: read returns 0 on EOF and -1 on error
    {
      if ((size = read(fd, buf, sizeof(buf)) == -1)
      {
        perror("\nread");
        exit(EXIT_FAILURE);
      }
  
      buf[size] = '\0';

      printf("%s", buf);
    }

    close(fd);
  }

  return EXIT_SUCCESS;
}
