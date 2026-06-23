// wc.c
// Author: jcolours
// Date: 2026-06-16
// Description: building a wc clone from scratch utilizing system calls such
// as read, close, and open.

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>

int return_char_count(size_t size, char *file);
int return_word_count(size_t size, char prev, char *file);
int return_line_count(size_t size, char *file);

int main(int argc, char **argv)
{
    int fd;
    size_t size = 1;
    char prev;

    if (argc < 2)
    {
        char buf[4096];

        fd = 0;

        int char_count = 0;
        int word_count = 0;
        int line_count = 0;

        prev = ' ';

        while (size > 0)
        {
            if ((size = read(fd, buf, sizeof(buf))) == -1)
            {
                perror("\nread\n");
                exit(EXIT_FAILURE);
            }

            buf[size] = '\0';

            char_count += return_char_count(size, buf);
            word_count += return_word_count(size, prev, buf);
            line_count += return_line_count(size, buf);

            prev = buf[size - 1];
        }

        printf("\n");
        printf("\x1b[1;4;33mLines\tWords\tCharacters\tFile Name\x1b[0m\n");
        printf("%d\t%d\t%d\t\tNone\n", line_count, word_count, char_count);
    }
    else
    {
        int total_chars = 0;
        int total_words = 0;
        int total_lines = 0;

        printf("\n");
        printf("\x1b[1;4;33mLines\tWords\tCharacters\tFile Name\x1b[0m\n");

        for (int i=1; i<argc; i++)
        {
            if ((fd = open(argv[i], O_RDONLY)) == -1)
            {
                perror("\nopen\n");
                exit(EXIT_FAILURE);
            }

            char buf[4096];

            size = 1;
            int char_count = 0;
            int word_count = 0;
            int line_count = 0;

            prev = ' ';

            while (size > 0)
            {
                if ((size = read(fd, buf, sizeof(buf))) == -1)
                {
                    perror("\nread\n");
                    exit(EXIT_FAILURE);
                }

                buf[size] = '\0';

                char_count += return_char_count(size, buf);
                word_count += return_word_count(size, prev, buf);
                line_count += return_line_count(size, buf);

                prev = buf[size - 1];
            }

            printf("%d\t%d\t%d\t\t%s\n", line_count, word_count, char_count, argv[i]);

            total_chars += char_count;
            total_words += word_count;
            total_lines += line_count;

            close(fd);
        }

        if (argc > 2) printf("%d\t%d\t%d\t\ttotal\n", total_lines, total_words, total_chars);
    }

  return EXIT_SUCCESS;
}

// FIX: make for loop instead of while
int return_char_count(size_t size, char *file)
{
    int count = 0;

    for (int i=0; i<size; i++)
    {
        if (file[i] == '\0')
            continue;
        else
            count++;
    }

    return count;
}

// FIX: problems with delimiting and process
// make for loop instead of while
int return_word_count(size_t size, char prev, char *file)
{
    int count = 0;
    int is_word = 0;

    // while (1)
    // {
    //     character = file[pos];
    //     if (character == '\0') break;
    //     if (character != ' ' || character != '\t' || character != '\n')
    //     {
    //         word = 1;
    //     }
    //     else
    //     {
    //         word = 0;
    //     }

    //     if (word == 0) count++;

    //     pos++;
    // }

    // count++; // counts last word before EOF

    for (int i=0; i<size; i++)
    {
        char last = (i == 0) ? prev : file[i-1];

        if (isalnum(file[i]) || ispunct(file[i])) is_word = 1;
        else is_word = 0;

        if (!is_word)
        {
            if (isspace(file[i]) && !isspace(last)) count++;
        }
    }

    return count;
}

// FIX: Add size param and make for loop instead of while
int return_line_count(size_t size, char *file)
{
    int count = 0;

    for (int i=0; i<size; i++)
    {
        if (file[i] == '\n') count++;
    }

    return count;
}
