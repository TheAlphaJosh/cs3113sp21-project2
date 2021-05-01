Joshua Gonzales

using the makefile, the code should read in from what the terminal is supplying, in the form of $[file executable] [algoritm] [number of bytes] [script file to read]

First Fit will find the first available memory slot to put the process in. It always starts from the beginning of the table and goes until it finds a suitable spot, otherwise it will return a fail.

Best Fit will find the best fit for the process out of all possible slots, giving the process to the slot that leaves the smallest memory hole behind. It will always start from the beginning and go through the entire memory. If suitable no slots are found it will return a fail.

Worst Fit will find the worst fit for the process out of all possible slots, giving the process to the slot that leaves the largest memory hole behind. It will always start from the beginning and go through the entire memory. If suitable no slots are found it will return a fail.

Next Fit runs much like first fit, except it starts from where it last left off. It will find the first next fit for the process starting from this point. If it reaches the end, it will loop back to the beginning of the table. If it reaches its previous spot, it will return a fail. If it fails, it will start from the beginning of memory next time.

All algorithms use a table made from a doubly linked list. Calculations for all algorithms are similar in calculation, using the value of the next start byte and current sizes from the current start byte.

Bugs will arise if the input is not in the format expected. Otherwise, calculation errors may arise to create bugs, but these are not expected.
