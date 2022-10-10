# CS3500 Assignment: Memory Usage and Page Faults

Write a program to implement the transpose of a matrix with tracking of memory usage and page
faults by the process.
In your program you will be performing transpose of 5 square matrices of n*n(1000<= n <= 5000)
dimensions for 10 iterations in 2 different settings. These matrices are allocated dynamically (malloc
/ calloc) and are filled with random long values. Use Inplace operations for matrix transpose.

Two different settings:

- Memory allocated only once in 10 iterations
- Memory allocated each time in 10 iterations

Your program must output the memory usage and the number of page faults after each iteration.

## Input

Line - 1: Size of matrix

Line - 2: Choice of allocation type

Choice of allocation:

- Memory allocated once: Code = 1
- Memory allocated in each itertion: Code = 2

## Running the Program

First compile the program using the following command,

```bash
make 
```

Run the code using,

```bash
./memory_usage
```

Now, enter the test cases individually. After running the tests clean the temp files using the command bellow.

```bash
make clean
```

### Given test results

The assignment folder contains some default test cases for n=1000 and memory allocation type 1 and type 2, in folder 'tests' under the name 'T1.tst' and 'T2.tst' respectively. The results of those are there in folder 'results' under the name 'T1.out' and 'T2.out' respectively.

You can add custom test cases, using the input format specfied in the 'tests' folder with extension '.tst'.

To run those test cases, type the following command:

```bash
make run
```

## Author

- [Soham Tripathy](www.github.com/Archaic-Mage)
