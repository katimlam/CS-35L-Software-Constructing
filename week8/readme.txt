In this homework, the primary technique I used is to create a thread
funciton. Then, I put the "for every pixel loop" into the function, including
the variables declared that the loop depend on. In the original version, the 
loop will printf the pixel floating points in order. But when doing
multithread, we cannot do that. So I create a three dimension array to contain
the data and printf them out in order at the end.

The challenging part of this homework is to figure out which variables the
loop will depend on and how to place them. Some of them will be put in the 
thread_function. Some of them will be declared globally. Also, I have to be
aware of the variables that are shared among threads and make sure they
remain constant.

A bug took me kinda long to figure out is that the .ppm have nothing about
the pixel. I finally realized that I forgot to change when it should printf
newline.

Here are the results of time used to with different numbers of threads. These
show multithreading can accelerate an embarrassingly parallel program multiple
times faster.

1 thread:
real    0m51.374s
user    0m51.365s
sys     0m0.003s

2 thread:
real    0m26.200s
user    0m51.708s
sys     0m0.003s

4 thread:
real    0m13.887s
user    0m54.638s
sys     0m0.006s

8 thread:
real    0m7.280s
user    0m56.307s
sys     0m0.002s
