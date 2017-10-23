PART 1: Thread Creation

The output from the unmodified thr1.cc were random A, B, and C's that were not in a certain sequence:
eg: "CBBBBCBACBCBABCBABCBABCBACBBAAAAAACBABBBCBBBBCBCBCBCBBCBCBABABACBAB", there ae random context switches.

In thr2.cc, the printC("C"); line is reached before the thread creation lines in the MAIN thread
therefore, we are stuck in the infinite loop that is in the method printC. The other two threads are
never created.



/////


PART 3:

I am not passing the test, and I am close to the deadline, but I feel I have implemented the correct idea, is it possible to get partial grade?
