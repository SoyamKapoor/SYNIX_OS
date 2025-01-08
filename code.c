#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

#define MAX_FILENAME 100
#define MAX_COMMAND 200
#define MEMORY_SIZE 1024 // Simulated memory size

// File Pointer for open/close operations
FILE *open_file_ptr = NULL;

// Simulated Memory Manager
char memory[MEMORY_SIZE];
int memory_used = 0;

// Function Prototypes
void show_menu();
void handle_command(const char *command);

void create_file();
void delete_file();
void write_file();
void read_file();
void rename_file();
void copy_file();
void move_file();
void list_files();
void open_file();
void close_file();
void clear_console();
void memory_status();

int main() {
    char command[MAX_COMMAND];

    printf("Welcome to Mini OS!\n");

    while (1) {
        show_menu();
        printf("\nEnter command: ");
        fgets(command, MAX_COMMAND, stdin);
        command[strcspn(command, "\n")] = '\0'; // Remove trailing newline

        if (strcmp(command, "exit") == 0) {
            printf("Exiting Mini OS. Goodbye!\n");
            break;
        }
        handle_command(command);
    }

    return 0;
}

// Display available commands
void show_menu() {
    printf("\nMini OS Commands:\n");
    printf("  create  - Create a new file\n");
    printf("  delete  - Delete an existing file\n");
    printf("  write   - Write data to a file\n");
    printf("  read    - Read data from a file\n");
    printf("  rename  - Rename a file\n");
    printf("  copy    - Copy a file\n");
    printf("  move    - Move a file\n");
    printf("  list    - List files in the current directory\n");
    printf("  open    - Open a file\n");
    printf("  close   - Close the currently opened file\n");
    printf("  clear   - Clear the console screen\n");
    printf("  exit    - Exit the Mini OS\n");
    printf("  mem     - Show memory status\n");
}

// Handle commands
void handle_command(const char *command) {
    if (strcmp(command, "create") == 0) {
        create_file();
    } else if (strcmp(command, "delete") == 0) {
        delete_file();
    } else if (strcmp(command, "write") == 0) {
        write_file();
    } else if (strcmp(command, "read") == 0) {
        read_file();
    } else if (strcmp(command, "rename") == 0) {
        rename_file();
    } else if (strcmp(command, "copy") == 0) {
        copy_file();
    } else if (strcmp(command, "move") == 0) {
        move_file();
    } else if (strcmp(command, "list") == 0) {
        list_files();
    } else if (strcmp(command, "open") == 0) {
        open_file();
    } else if (strcmp(command, "close") == 0) {
        close_file();
    } else if (strcmp(command, "clear") == 0) {
        clear_console();
    } else if (strcmp(command, "mem") == 0) {
        memory_status();
    } else {
        printf("Invalid command. Please try again.\n");
    }
}

// Command Implementations

void create_file() {
    char filename[MAX_FILENAME];
    printf("Enter the name of the file to create: ");
    fgets(filename, MAX_FILENAME, stdin);
    filename[strcspn(filename, "\n")] = '\0';

    FILE *file = fopen(filename, "w");
    if (file) {
        printf("File '%s' created successfully.\n", filename);
        fclose(file);
    } else {
        perror("Error creating file");
    }
}

void delete_file() {
    char filename[MAX_FILENAME];
    printf("Enter the name of the file to delete: ");
    fgets(filename, MAX_FILENAME, stdin);
    filename[strcspn(filename, "\n")] = '\0';

    if (remove(filename) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        perror("Error deleting file");
    }
}

void write_file() {
    char filename[MAX_FILENAME], data[MAX_COMMAND];
    printf("Enter the name of the file to write to: ");
    fgets(filename, MAX_FILENAME, stdin);
    filename[strcspn(filename, "\n")] = '\0';

    FILE *file = fopen(filename, "a");
    if (file) {
        printf("Enter data to write to the file: ");
        fgets(data, MAX_COMMAND, stdin);
        fputs(data, file);
        printf("Data written to file '%s' successfully.\n", filename);
        fclose(file);
    } else {
        perror("Error writing to file");
    }
}

void read_file() {
    char filename[MAX_FILENAME];
    printf("Enter the name of the file to read from: ");
    fgets(filename, MAX_FILENAME, stdin);
    filename[strcspn(filename, "\n")] = '\0';

    FILE *file = fopen(filename, "r");
    if (file) {
        char buffer[MAX_COMMAND];
        printf("Contents of '%s':\n", filename);
        while (fgets(buffer, MAX_COMMAND, file)) {
            printf("%s", buffer);
        }
        fclose(file);
    } else {
        perror("Error reading file");
    }
}

void rename_file() {
    char old_name[MAX_FILENAME], new_name[MAX_FILENAME];
    printf("Enter the current name of the file: ");
    fgets(old_name, MAX_FILENAME, stdin);
    old_name[strcspn(old_name, "\n")] = '\0';

    printf("Enter the new name for the file: ");
    fgets(new_name, MAX_FILENAME, stdin);
    new_name[strcspn(new_name, "\n")] = '\0';

    if (rename(old_name, new_name) == 0) {
        printf("File '%s' renamed to '%s' successfully.\n", old_name, new_name);
    } else {
        perror("Error renaming file");
    }
}

void copy_file() {
    char source[MAX_FILENAME], destination[MAX_FILENAME];
    printf("Enter the source file: ");
    fgets(source, MAX_FILENAME, stdin);
    source[strcspn(source, "\n")] = '\0';

    printf("Enter the destination file: ");
    fgets(destination, MAX_FILENAME, stdin);
    destination[strcspn(destination, "\n")] = '\0';

    FILE *src = fopen(source, "r");
    FILE *dest = fopen(destination, "w");

    if (src && dest) {
        char buffer[MAX_COMMAND];
        while (fgets(buffer, MAX_COMMAND, src)) {
            fputs(buffer, dest);
        }
        printf("File '%s' copied to '%s' successfully.\n", source, destination);
        fclose(src);
        fclose(dest);
    } else {
        perror("Error copying file");
        if (src) fclose(src);
        if (dest) fclose(dest);
    }
}

void move_file() {
    char source[MAX_FILENAME], destination[MAX_FILENAME];
    printf("Enter the source file: ");
    fgets(source, MAX_FILENAME, stdin);
    source[strcspn(source, "\n")] = '\0';

    printf("Enter the destination file: ");
    fgets(destination, MAX_FILENAME, stdin);
    destination[strcspn(destination, "\n")] = '\0';

    if (rename(source, destination) == 0) {
        printf("File '%s' moved to '%s' successfully.\n", source, destination);
    } else {
        perror("Error moving file");
    }
}

void list_files() {
    printf("Files in the current directory:\n");
#ifdef _WIN32
    system("dir");
#else
    system("ls");
#endif
}

void open_file() {
    char filename[MAX_FILENAME];
    if (open_file_ptr) {
        printf("A file is already open. Close it first.\n");
        return;
    }

    printf("Enter the name of the file to open: ");
    fgets(filename, MAX_FILENAME, stdin);
    filename[strcspn(filename, "\n")] = '\0';

    open_file_ptr = fopen(filename, "r");
    if (open_file_ptr) {
        printf("File '%s' opened successfully.\n", filename);
    } else {
        perror("Error opening file");
    }
}

void close_file() {
    if (open_file_ptr) {
        fclose(open_file_ptr);
        open_file_ptr = NULL;
        printf("File closed successfully.\n");
    } else {
        printf("No file is currently open.\n");
    }
}

void clear_console() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void memory_status() {
    printf("Memory Used: %d/%d bytes\n", memory_used, MEMORY_SIZE);
}
