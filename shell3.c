#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for storing aliases
typedef struct alias {
    char *name;
    char *value;
    struct alias *next;
} alias;

alias *head = NULL;

// Function to implement the alias builtin command
void alias_cmd(char *cmd) {
    char *name = strtok(cmd, "=");
    char *value = strtok(NULL, "=");

    if (value == NULL) {
        alias *temp = head;
        while (temp != NULL) {
            if (strcmp(temp->name, name) == 0) {
                printf("%s='%s'\n", temp->name, temp->value);
                return;
            }
            temp = temp->next;
        }
    } else {
        alias *new_alias = malloc(sizeof(alias));
        new_alias->name = strdup(name);
        new_alias->value = strdup(value);
        new_alias->next = head;
        head = new_alias;
    }
}

// Function to handle variables replacement
void var_replace(char *cmd) {
    // Implementation depends on the specific shell variables you want to replace
}

// Function to handle comments
void handle_comments(char *cmd) {
    char *comment_start = strchr(cmd, '#');
    if (comment_start != NULL) {
        *comment_start = '\0';
    }
}

int main(int argc, char **argv) {
    char cmd[1024];

    while (1) {
        printf("$ ");
        fgets(cmd, 1024, stdin);

        handle_comments(cmd);

        if (strncmp(cmd, "alias", 5) == 0) {
            alias_cmd(cmd + 6);
        } else if (strchr(cmd, '$') != NULL) {
            var_replace(cmd);
        } else if (argc > 1) {
            // Handle file input mode
            FILE *file = fopen(argv[1], "r");
            if (file == NULL) {
                perror("Error opening file");
                return 1;
            }

            while (fgets(cmd, sizeof(cmd), file)) {
                printf("%s", cmd);
            }

            fclose(file);
            return 0;
        } else {
            system(cmd);
        }
    }

    return 0;
}
