# CS3500: Disk Scheduling Algorithm

## Introduction

Write a program that implements the following disk-scheduling algorithms:

- FCFS
- SSTF
- SCAN
- C-SCAN
- LOOK
- C-LOOK

Your program will service a disk with 5,000 cylinders numbered 0 to 4,999. The program will
generate a random series of 1,000-cylinder requests and service them according to each of the
algorithms listed above. The program will take two arguments, initial position of the disk head
(default value 2000) and the algorithm to be used. The program will output the sequence in
which the requests were served and after the sequence it will print the average & total amount
of head movement for the requests.

## Running Format

The '-h' parameter specifies the initial head position, and '-a' specifies the algorithm used.

The -a parameter can take values only from '1' to '6'

- 1 - FCFS
- 2 - SSTF
- 3 - SCAN
- 4 - C-SCAN
- 5 - LOOK
- 6 - C-LOOk
  
The -h parameter can take values from '0' to '4999' only.

```bash
./algorithm -h 2000 -a 1
```

## Run the program

- First compile the program by the following command

```bash
make
```

- Then run the test cases,

```bash
make run
```

- All test cases are there in the folder tests. The format follow the format of arguments when run normally.

- You can also perform a clean operation to delete the output files and executables.

```bash
make clean
```

The results to the test cases will be there in output folder.

You can also view the plot for the disk head movements by typing the following command.

```bash
make plot
```

## Authors

- [Soham Tripathy](https://www.github.com/Archaic-Mage)