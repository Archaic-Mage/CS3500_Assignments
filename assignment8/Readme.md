# CS3500: Disk Scheduling Algorithm

## Introduction

The objective of this assignment is to implement a simulated file system.

## File Information

A file is viewed as a sequence of bytes, with the first byte numbered 0. File is allocated
space on the disk, one block at a time. All references to files in this assignment will be by their fully
expanded names (i.e. including complete directory tree information), as in /dir1/file2.h. For filenames,
extensions are optional and can include up to three characters.

## Inode

- Directory name or Filename: Up to 16 bytes total for a fully expanded filename (including the
two ’/’ characters). The directory name can have up to 4 characters (bytes).
Thus, di4, dir3 are valid directory names, while direc3 is not; Likewise, /dir3/filename.c is valid
since it contains 16 total characters.
- Type: Directory (value = 1) or File (value = 0): Use 1 byte to store this value.
- File size: recorded using 4 bytes. Theoretical maximum file size is 232 bytes, but in practice, the
file sizes for this project will not exceed 4,480 Bytes.
- Date Created: Output of date command of Linux - requires a 28-byte string.
- Date Last Modified: Output of date command of Linux - requires a 28-byte string.
- Direct block addresses: 3 4-byte integers, that will point to the first three data blocks of the file.
- Index block address: 1 4-byte integer, that will point to one index block, which can contain up to
32 block addresses (Since each block size is 128 bytes and each block address needs 4 bytes).
These addresses in the index block point to blocks 4, 5, 6, etc. of the file.

## Problem Statement

You must implement a disk directory structure, which will store information about all files on the
directory and the inodes for the files. The specific inode structure and data maintained for directory
level information is left open to the implementer.

## System commands

- **load:** It creates the file with the given file name.

```bash
load $filename
```

- **delete:** It deletes the file with the given file name.

```bash
delete $filename
```

- **append:** It takes 2 arguments. This appends the given string into the end of the file.

```bash
append $filename $string
```

- **display:** Prints the name of the files in the disk & its size.

```bash
display
```

- **freespace:** Prints the number of available free block & total free size.

```bash
freespace
```

- **printinode:** Print the inode contents for the specified file.

```bash
printinode $filename
```

- **exit:** Exit the system.

```bash
exit
```

## Run the program

- First compile the program by the following command

```bash
make
```

- Run the executable using the following command

```bash
./main
```

Give approprite commands and it simulates a directory structure.

- The outputs of some manual test cases are there in the folder 'screenshots'.

- You can also perform a clean operation to delete the temp files.

```bash
make clean
```

## Results

![Test1](screenshots/Screenshot%20from%202022-11-03%2011-11-57.png)

![Test2](screenshots/Screenshot%20from%202022-11-03%2011-15-30.png)

## Authors

- [Soham Tripathy](https://www.github.com/Archaic-Mage)
