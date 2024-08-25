# File System Simulation in C

This project is a simple file system simulation written in C, allowing you to create directories and files, navigate between directories, and perform various file operations. The simulation mimics basic file system functionality, including directory management, file creation, editing, and copying.

## Features

- **Directory Operations**:
  - Create directories.
  - Change directories.
  - List files in the current directory.
  - Navigate back to the parent directory.

- **File Operations**:
  - Create new files with random sizes.
  - Edit file contents.
  - Copy files between directories.
  - Display file contents and metadata (size, creation date, modification date).
  - Retrieve and print the absolute or relative path of the current directory.

## Code Structure

- `File` struct: Represents a file with attributes such as name, size, data, creation date, and modification date.
- `Directory` struct: Represents a directory containing files and subdirectories, and has a reference to its parent directory.
- `FileSystem` struct: Represents the entire file system, starting with the root directory.

## How to Use

### Running the Program

1. **Clone the repository**:
    ```bash
    git clone https://github.com/yourusername/filesystem-simulation.git
    cd filesystem-simulation
    ```

2. **Compile the code**:
    ```bash
    gcc -o filesystem filesystem.c
    ```

3. **Run the executable**:
    ```bash
    ./filesystem
    ```

### Menu Options

1. **Create Directory**: Create a new directory within the current directory.
2. **Create File**: Create a new file within the current directory.
3. **Change Directory**: Change the current directory to a specified directory or go back to the parent directory.
4. **List Files in Current Directory**: Display all files and subdirectories in the current directory.
5. **Present Working Directory**: Display the absolute path of the current directory.
6. **Print Relative Path**: Display the relative path from the root to the current directory.
7. **File Actions**: 
   - Open a file.
   - Edit file contents.
   - Copy a file to another directory.
   - Display file contents.
   - Display file metadata.
8. **Exit**: Exit the program.

### Example Usage

- **Creating a Directory**:
    ```sh
    Enter directory name: Documents
    Directory 'Documents' created successfully.
    ```

- **Creating a File**:
    ```sh
    Enter file name: myfile.txt
    File 'myfile.txt' created successfully. Size: 512 bytes
    ```

- **Editing a File**:
    ```sh
    Enter the contents you want to add: Hello, world!
    File edited successfully.
    ```

- **Copying a File**:
    ```sh
    Enter destination directory name: Documents
    File copied successfully.
    ```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
