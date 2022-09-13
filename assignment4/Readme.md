
# CS3500: CPU  Scheduling

## Multilevel Queue Scheduling
  
A multilevel queue scheduling algorithm partitions the ready queue into several separate queues. The
processes are permanently assigned to one of the queues, generally based on some property of the
process, such as memory size, process priority, or process type. Each queue has its own scheduling
algorithm.  

This project implements a multilevel queue scheduling algorithm with five queues, listed below:

- System processes (sys)
- Interactive processes (ip)
- Interactive editing processes (iep)
- Batch processes (bp)
- Student processes (sp)
  
Each type of process is given a time slice of CPU to run its processes. That is each queue runs in a round
robin fashion. System process runs in a priority scheduling manner. Interactive and interactive editing
process will work on FCFS basis. Batch and student process on SJF scheduling. All processes
are preemptive.

This project finds the sequence in which CPU schedules the process for execution.

It calculates the following:

- Completion Time (CT)
- Waiting Time (WT)
- Turnaround Time (TAT)

**Completion Time (C.T):** Time at which process completes its execution.  

**Turn Around Time (T.A.T):**
Time Difference between completion time and arrival time.

```Turn Around Time = Completion Time – Arrival Time```

**Waiting Time (W.T):** Time Difference between turnaround time and burst time.

```Waiting Time = Turn Around Time – Burst Time```

### Input Format

Line 1: Round Robin Quantum Time

Line 2: Number of processes (N)

The next N lines contains the following for each line,

- Process_id  (pN : where 'N' is interger)
- Arrival_time (integer)
- Brust_time  (integer)
- Type_of_process (sys, ip, iep, bp, sp)
- priority (integer)

#### Example Test Input

```text
3
20
p1 0 3 sys 1 
p2 0 2 ip 0 
p3 0 2 iep 0 
p4 0 3 bp 0 
p5 0 1 sp 0 
p6 1 2 iep 0 
p7 2 4 sys 2 
p8 2 3 ip 0 
p9 3 2 bp 0 
p10 3 3 sp 0 
p11 3 2 iep 0 
p12 4 3 sys 4 
p13 4 2 sys 3 
p14 5 3 ip 0 
p15 6 5 ip 0 
p16 6 3 bp 0 
p17 6 2 bp 0 
p18 7 5 sp 0 
p19 9 2 ip 0 
p20 10 2 sp 0
```

## Run Locally

Go to the project directory,

Install dependencies,

- g++

```bash
  sudo apt install g++
```

- cmake

```bash
  sudo apt install cmake
```

Run the following command to generate the 'schedule' executable.

```bash
  make
```

Now run the executable.

```bash
  ./schedule
```

Give approprite inputs and it outputs the relevant information.

## Running Tests

The tests are there in 'tests' folder. We can add custom test cases which
satisfies the input criteria in 'name.in' (replace name with anything of your choice) file
inside the tests folder.

To run tests, run the following command

```bash
  make run
```

The ouput for the all the tests cases in 'tests' folder will be stored in the 'output'
folder.

## Authors

- [Soham Tripathy](https://www.github.com/Archaic-Mage)
