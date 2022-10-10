# CS3500 Assignment: Contiguous Memory Allocations

One of the simplest methods for allocating memory is to divide memory into several fixed-sized
partitions. Each partition may contain exactly one process. Thus, the degree of multiprogramming is
bound by the number of partitions. In this multiple partition method, when a partition is free, a
process is selected from the input queue and is loaded into the free partition.
The first-fit, best-fit, and worst-fit strategies are the ones most commonly used to select a free hole
from the set of available holes.

- **First fit.** Allocate the first hole that is big enough. Searching can start at the beginning of the set of
holes. We can stop searching as soon as we find a free hole that is large enough. For initial allocation
start from the beginning of the fixed holes
- **Best fit.** Allocate the smallest hole that is big enough. We must search the entire list, unless the list
is ordered by size. This strategy produces the smallest leftover hole.
- **Worst fit.** Allocate the largest hole. Again, we must search the entire list, unless it is sorted by size.
This strategy produces the largest leftover hole, which may be more useful than the smaller leftover
hole from a best-fit approach.

Given details of memory blocks and process sizes, write a program to implement the above three
strategies to assign processes to memory blocks.

## Input

Line - 1: Number of Blocks

Line - 2: Block sizes

Line - 3: Number of Processes

Line - 4: Processes Sizes

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

The assignment folder contains some default test cases for,

Enter Number of Blocks: 5

Enter 5 block sizes: 200 600 300 400 700

Enter Number of Process: 4

Enter 4 Process Sizes: 330 520 210 550,

in folder 'tests' under the name 'T1.tst' respectively. The results of those are there in folder 'results' under the name 'T1.out' respectively.

You can add custom test cases, using the input format specfied in the 'tests' folder with extension '.tst'.

To run those test cases, type the following command:

```bash
make run
```

## Author

- [Soham Tripathy](www.github.com/Archaic-Mage)
