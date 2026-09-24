/*
11. MEMORY ALLOCATION STRATEGIES

At one instant, the memory map of a 4 MB (4000 KB) RAM looks as in Figure 1.

Processes (P1, P2, etc.) request the operating system for memory and also release the allocated memory after completing execution.

Sample execution trace:

P7 requests for 115 KB
P10 requests for 650 KB
P3 completes execution
P1 completes execution
P6 completes execution
P8 requests for 200 KB
P5 completes execution
P2 completes execution
P9 requests for 37 KB
P10 completes execution
P9 completes execution
P4 completes execution

Task:
Which strategy among the following performs the best here?

- First Fit
- Best Fit
- Worst Fit

*/