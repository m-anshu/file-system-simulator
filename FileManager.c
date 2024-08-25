#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PATH_LENGTH 256
#define MAX_NAME_LENGTH 50
#define MAX_FILES_IN_DIRECTORY 100
#define MAX_DIRECTORIES 50


struct Directory;

typedef struct File
{
    char name[MAX_NAME_LENGTH];
    char data[100];
    int size;
    char creation_date[20];
    char modification_date[20];
} File;

typedef struct Directory
{
    char name[MAX_NAME_LENGTH];
    File files[MAX_FILES_IN_DIRECTORY];
    int file_count;
    struct Directory *directories[MAX_DIRECTORIES];
    struct Directory *parent_directory;
} Directory;

typedef struct
{
    char name[MAX_NAME_LENGTH];
    Directory root_directory;
} FileSystem;

FileSystem fileSystem;
Directory *current_directory;

void initializeFileSystem()
{
    strcpy(fileSystem.name, "C:\\");
    fileSystem.root_directory.file_count = 0;
}

void createDirectory(char name[])
{
    if (current_directory->file_count < MAX_FILES_IN_DIRECTORY)
    {
        Directory *newDirectory = malloc(sizeof(Directory));
        strcpy(newDirectory->name, name);
        newDirectory->file_count = 0;
        newDirectory->parent_directory = current_directory;

        current_directory->directories[current_directory->file_count] = newDirectory;
        current_directory->file_count++;
        printf("Directory '%s' created successfully.\n", name);
    }
    else
    {
        printf("Directory is full, cannot create more directories.\n");
    }
}

void createFile(char name[])
{
    if (current_directory->file_count < MAX_FILES_IN_DIRECTORY)
    {
        File newFile;
        strcpy(newFile.name, name);
        newFile.size = rand() % 1024 + 1; 

        time_t t = time(NULL);
        struct tm *tm_info = localtime(&t);
        strftime(newFile.creation_date, sizeof(newFile.creation_date), "%Y-%m-%d %H:%M:%S", tm_info);
        strftime(newFile.modification_date, sizeof(newFile.modification_date), "%Y-%m-%d %H:%M:%S", tm_info);

        current_directory->files[current_directory->file_count] = newFile;
        current_directory->file_count++;
        printf("File '%s' created successfully. Size: %d bytes\n", name, newFile.size);
        printf("Creation Date: %s\n", newFile.creation_date);
        printf("Modification Date: %s\n", newFile.modification_date);
    }
    else
    {
        printf("Directory is full, cannot create more files.\n");
    }
}


void printAbsolutePath(Directory *directory)
{
    if (directory->parent_directory != NULL)
    {
        printAbsolutePath(directory->parent_directory);
        printf("\\%s\\", directory->name);
    }
    else
    {
        printf("C:%s\\", directory->name);
    }
}

File *getFileByPath(char relative_path[])
{
    for (int i = 0; i < current_directory->file_count; i++)
    {
        if (strcmp(current_directory->files[i].name, relative_path) == 0)
        {
            return &current_directory->files[i];
        }
    }
    return NULL;
}

void listFilesInDirectory()
{
    printf("Files in directory '%s':\n", current_directory->name);
    for (int i = 0; i < current_directory->file_count; i++)
    {
        printf("- %s\n", current_directory->files[i].name);
    }
}

void changeDirectory(char name[])
{
    if (strcmp(name, "..") == 0)
    {

        if (current_directory != &fileSystem.root_directory)
        {
            current_directory = current_directory->parent_directory;
            printf("Changed to parent directory: %s\n", current_directory->name);
        }
        else
        {
            printf("Already in the root directory.\n");
        }
    }
    else
    {

        for (int i = 0; i < current_directory->file_count; i++)
        {
            if (current_directory->directories[i] != NULL && strcmp(current_directory->directories[i]->name, name) == 0)
            {
                current_directory->directories[i]->parent_directory = current_directory;
                current_directory = current_directory->directories[i];
                printf("Changed to directory: %s\n", current_directory->name);
                return;
            }
        }
        printf("Directory not found.\n");
    }
}

void openFile(File *file)
{
    printf("Opening file: %s\n", file->name);

}

void editFile(File *file)
{
    char copy[100];
    printf("Editing file: %s\n", file->name);
    printf("Enter the contents you want to add: ");


    if (scanf(" %[^\n]", copy) != 1)
    {
        printf("Error reading input.\n");
        return;
    }


    if (strlen(file->data) + strlen(copy) < sizeof(file->data))
    {
        strcat(file->data, copy);
        time_t t = time(NULL);
        struct tm *tm_info = localtime(&t);
        strftime(file->modification_date, sizeof(file->modification_date), "%Y-%m-%d %H:%M:%S", tm_info);

        printf("File edited successfully.\n");
    }
    else
    {
        printf("Error: Insufficient space in the file to add the contents.\n");
    }


}

void copyFile(File *source, Directory *destinationDirectory)
{
    printf("Copying file: %s\n", source->name);

    if (destinationDirectory->file_count < MAX_FILES_IN_DIRECTORY)
    {
        destinationDirectory->files[destinationDirectory->file_count] = *source;
        destinationDirectory->file_count++;
        printf("File copied successfully.\n");
    }
    else
    {
        printf("Destination directory is full, cannot copy the file.\n");
    }
}
void display_meta(File *file)
{
    printf("File Metadata:\n");
    printf("Size: %d bytes\n", file->size);
    printf("Creation Date: %s\n", file->creation_date);
    printf("Modification Date: %s\n", file->modification_date);
}
void printRelativePath(Directory *current_directory1)
{

    if (current_directory1 == NULL || strcmp(current_directory1->name, "C:\\") == 0)
    {
        printf("Relative Path: .\n");
        return;
    }

    char relative_path[MAX_PATH_LENGTH] = "";
    
  
    while (current_directory1 != NULL)
    {
 
        char temp[MAX_PATH_LENGTH];
        snprintf(temp, sizeof(temp), "%s\\%s", current_directory1->name, relative_path);
        strcpy(relative_path, temp);


        current_directory1 = current_directory1->parent_directory;
    }

    printf("Relative Path: ..%s\n", relative_path);
}


void printMenu()
{
    printf("\nOptions:\n");
    printf("1. Create Directory\n");
    printf("2. Create File\n");
    printf("3. Change Directory\n");
    printf("4. List Files in Current Directory\n");
    printf("5. Present Working Directory\n");
    printf("6. Print relative path\n");
    printf("7. File Actions\n");
    printf("8. Exit\n");
    printf("Enter your choice: ");
}
void display(File *file)
{
    printf("The file contents are:\n");
    printf("%s\n", file->data);
}

int main()
{

    initializeFileSystem();


    current_directory = &fileSystem.root_directory;
    current_directory->parent_directory = NULL;

    int choice;
    do
    {
        printMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            char name[MAX_NAME_LENGTH];
            printf("Enter directory name: ");
            scanf("%s", name);
            createDirectory(name);
            break;
        }
        case 2:
        {
            char name[MAX_NAME_LENGTH];
            printf("Enter file name: ");
            scanf("%s", name);
            createFile(name);
            break;
        }
        case 3:
        {
            char name[MAX_NAME_LENGTH];
            printf("Enter directory name (use '..' to go back): ");
            scanf("%s", name);
            changeDirectory(name);
            break;
        }
        case 4:
            listFilesInDirectory();
            break;
        case 5:
            printAbsolutePath(current_directory);
            printf("\n");
            break;
        case 6:
            printRelativePath(current_directory);
            printf("\n");
            break;
        case 7:
        {
            char fileName[MAX_NAME_LENGTH];
            printf("Enter file name: ");
            scanf("%s", fileName);

            File *accessedFile = getFileByPath(fileName);
            if (accessedFile != NULL)
            {
                int fileAction;
                do
                {
                    printf("\nFile Actions:\n");
                    printf("1. Open File\n");
                    printf("2. Edit File\n");
                    printf("3. Copy File\n");
                    printf("4. Display the File contents\n");
                    printf("5. Display the metadata contents\n");
                    printf("6. Back to Main Menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &fileAction);

                    switch (fileAction)
                    {
                    case 1:
                        openFile(accessedFile);
                        break;
                    case 2:
                        editFile(accessedFile);
                        break;
                    case 3:
                    {
                        char destinationDirectory[MAX_NAME_LENGTH];
                        printf("Enter destination directory name: ");
                        scanf("%s", destinationDirectory);

                        Directory *destination = NULL;
                        for (int i = 0; i < current_directory->file_count; i++)
                        {
                            if (current_directory->directories[i] != NULL &&
                                strcmp(current_directory->directories[i]->name, destinationDirectory) == 0)
                            {
                                destination = current_directory->directories[i];
                                break;
                            }
                        }

                        if (destination != NULL)
                        {
                            copyFile(accessedFile, destination);
                        }
                        else
                        {
                            printf("Destination directory not found.\n");
                        }
                        break;
                    }
                    case 4:
                        display(accessedFile);
                        break;
                    case 5:
                        display_meta(accessedFile);
                        break;
                    case 6:
                        printf("Returning to Main Menu.\n");
                        break;
                    default:
                        printf("Invalid choice. Please enter a number between 1 and 5.\n");
                    }
                } while (fileAction != 6);
            }
            else
            {
                printf("File not found.\n");
            }
            break;
        }

        case 8:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Please enter a number between 1 and 8.\n");
        }
    } while (choice != 8);

    return 0;
}