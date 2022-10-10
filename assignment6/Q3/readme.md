# CS3500 Assignment: Contiguous Memory Allocations

A page fault will happen if a program tries to access a piece of memory that does not exist in
physical memory (main memory). The fault specifies the operating system to trace all data into
virtual memory management and then relocate it from secondary memory to its primary memory,
such as a hard disk.If the physical memory is full then the process replaces the current page with the new requested
page.

- **FIFO page replacement:** The simplest page-replacement algorithm is a first-in, first-out (FIFO)
algorithm. When a page must be replaced, the oldest page is chosen.
- **Optimal Page Replacement:** Replace the page that will not be used for the longest period of time.
- **LRU Page Replacement:** Replace the page that has not been used for the longest period of time.

Write a program to implement the above three strategies for a given sequence of reference strings
(strings of memory references) and page frame size (Assume each frame size is 100 bytes). Assume
initially everything is in virtual memory.

## Input

Line - 1: Sequence Length

Line - 2: Sequence of page access

Line - 3: Page frame size

Line - 4: Page replacement Policy code

- **FIFO** - 1
- **Optimal** - 2
- **LRU** - 3

## Running the Program

First compile the program using the following command,

```bash
make 
```

Run the code using,

```bash
./memoryAllocator
```

Now, enter the test cases individually. After running the tests clean the temp files using the command bellow.

```bash
make clean
```

### Given test results

The assignment folder contains some default test cases in folder 'tests' under the name 'T1.tst', 'T2.tst' and 'T3.tst'. The results of those tests are there in folder 'results' under the name 'T1.out', 'T2.out' and 'T3.tst' respectively.

You can add custom test cases, using the input format specfied in the 'tests' folder with extension '.tst'.

To run those test cases, type the following command:

```bash
make run
```

## Author

- [Soham Tripathy](www.github.com/Archaic-Mage)
