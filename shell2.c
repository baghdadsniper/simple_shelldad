#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while (1)
    {
        printf("$ ");
        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            printf("\n");
            break;
        }
        else if (read > 1)
        {
            line[read - 1] = '\0';
            if (strcmp(line, "exit") == 0)
            {
                exit(0);
            }
            else if (strncmp(line, "cd ", 3) == 0)
            {
                chdir(line + 3);
            }
            else if (access(line, X_OK) == 0)
            {
                char *argv[] = {line, NULL};
                if (fork() == 0)
                {
                    execve(line, argv, NULL);
                }
                else
                {
                    wait(NULL);
                }
            }
            else
            {
                printf("%s: No such file or directory\n", line);
            }
        }
    }

    free(line);
    return (0);
}
