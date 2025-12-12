#include <stdio.h>
#include <stdlib.h>

// Function to create a new empty file
void createFile(char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error creating file!\n");
        return;
    }
    fclose(fp);
    printf("File '%s' created successfully.\n", filename);
}

// Function to delete a file
void deleteFile(char *filename) {
    if (remove(filename) == 0)
        printf("File '%s' deleted successfully.\n", filename);
    else
        printf("Error deleting file!\n");
}

// Function to copy a file
void copyFile(char *source, char *dest) {
    FILE *fs = fopen(source, "r");
    if (fs == NULL) {
        printf("Source file not found!\n");
        return;
    }

    FILE *fd = fopen(dest, "w");
    char ch;

    while ((ch = fgetc(fs)) != EOF) {
        fputc(ch, fd);
    }

    fclose(fs);
    fclose(fd);
    printf("File copied from '%s' to '%s'.\n", source, dest);
}

// Function to move a file (copy + delete)
void moveFile(char *source, char *dest) {
    copyFile(source, dest);
    deleteFile(source);
    printf("File moved from '%s' to '%s'.\n", source, dest);
}

int main() {
    int choice;
    char file1[50], file2[50];

    while (1) {
        printf("\n--- File Operation Menu ---\n");
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. Copy File\n");
        printf("4. Move File\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter filename to create: ");
                scanf("%s", file1);
                createFile(file1);
                break;

            case 2:
                printf("Enter filename to delete: ");
                scanf("%s", file1);
                deleteFile(file1);
                break;

            case 3:
                printf("Enter source filename: ");
                scanf("%s", file1);
                printf("Enter destination filename: ");
                scanf("%s", file2);
                copyFile(file1, file2);
                break;

            case 4:
                printf("Enter source filename: ");
                scanf("%s", file1);
                printf("Enter destination filename: ");
                scanf("%s", file2);
                moveFile(file1, file2);
                break;

            case 5:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

