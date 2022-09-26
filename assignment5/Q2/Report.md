# Report - Multiple Producer-Consumer Problem

## Authors

- [Soham Tripathy](https://github.com/Archaic-Mage)

## Introduction

There are P number of producers and C number of consumers. The capacity of each producer is given by PC and capacity of each consumer is given by CC. All these values will be given as command line arguments. All the producers and consumers will have a
shared buffer which you can consider to be a stack like data structure. Whenever a producer produces an item (a number in our case), it is placed on top of the stack. And similarly, whenever a consumer wants to consume an item, it picks a number from the top of the stack. All the producers and consumers should be implemented as threads. Each producer will only produce a PC number of items and then stop producing. Each consumer will try to consume a CC number of items and then stop consuming. The program ends once all producers are done with producing a PC number of items and all consumers are done consuming a CC number of items. You can assume that (P * PC >= C * CC).

## Results

### Without Sleep(5) -  Producer

When the program is run, without putting producers to the sleep for 5 seconds the output is given as follows.
```
Producer 1 produced 507
Producer 1 produced 906
Consumer 1 consumed 906
Consumer 2 consumed 507
Producer 2 produced 605
Producer 2 produced 987
Consumer 2 consumed 987
Producer 3 produced 613
Producer 3 produced 552
Consumer 1 consumed 552
Producer 4 produced 990
Producer 4 produced 557
```
### With sleep(5) - Producer

When the program is run, with putting producers to sleep for 5 seconds, the ouput is as follows.

```
Could not retrieve data, Stack is empty.
Consumer 1 consumed 0
Could not retrieve data, Stack is empty.
Consumer 1 consumed 0
Could not retrieve data, Stack is empty.
Consumer 2 consumed 0
Could not retrieve data, Stack is empty.
Consumer 2 consumed 0
Producer 1 produced 507
Producer 3 produced 906
Producer 3 produced 605
Producer 1 produced 987
Producer 2 produced 613
Producer 2 produced 552
Producer 4 produced 990
Producer 4 produced 557
```

## Observations

When producer is not kept to sleep, then the whenever a consumer consumes we generally ensure that the producers have filled the stack with appropriate quantity.

This case is not satisfied when producers are kept to sleep for 5 seconds.

Thus empty stack error is faced.


The following code ensures that consumers will access the stack only when the stack has atleast one element.

```cpp
if(isempty()) {
    sem_post(&is_stack_available);
    continue;
}
```

Now, the output is as expected. The only difference is in the runtime. The sleep(5) change in code takes approximately 5 seconds extra to get executed.

```
Producer 2 produced 507
Producer 2 produced 906
Consumer 2 consumed 906
Consumer 2 consumed 507
Producer 3 produced 605
Producer 3 produced 987
Producer 4 produced 613
Producer 4 produced 552
Consumer 1 consumed 552
Consumer 1 consumed 613
Producer 1 produced 990
Producer 1 produced 557
```

## Conclusions

We can delay the start of different threads. This can significantly change the output of the program and can also change the use case of them.