# Philozophers
![](https://developer.android.com/courses/extras/images/multi-threading-2.png)
---

Philosophers an individual project at [42](https://www.42.fr/42-network/) about introduction to the basics of process threading, and how work on the same memory space.
And learn about mutexes, semaphores, and shared memory.

## About the project
This project serves as an introduction to [multithreading](https://en.wikipedia.org/wiki/Multithreading_(computer_architecture)).
The purpose was to build 2 different programs to solve [the dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem), each with different constraints.

## Introduction

In computer science, the dining philosophers problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.

It was originally formulated in *1965 by Edsger Dijkstra* as a student exam exercise, presented in terms of computers competing for access to tape drive peripherals. Soon after, Tony Hoare gave the problem its present formulation

[More informations](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

## Installation 🖥

To test the project, go to one of the folders __*philo*__ or __*philo_bonus*__ and make a `make`. Then, you can test the project using an executable.

__example :__

`./philo_one 4 500 200 200`

__usage :__

`./philo Number_of_philosophers Time_to_die Time_to_eat Time_to_sleep [Number_of_times_each_philosopher_must_eat]`
arguments in square brackets are not required (number_of_time_each_philosophers_must_eat)

![alt text](https://i.ibb.co/HTpDZBc/Screenshot-2021-10-12-182745.png)

## Resources

* [Parallel Computing](https://computing.llnl.gov/tutorials/parallel_comp/)
* [POSIX Threads](https://computing.llnl.gov/tutorials/pthreads/) ([pthread routines](https://computing.llnl.gov/tutorials/pthreads/#AppendixA))
* [Working example](https://timmurphy.org/2010/05/04/pthreads-in-c-a-minimal-working-example/)
* [French tutorial](https://franckh.developpez.com/tutoriels/posix/pthreads/)
* [Semaphores in C](http://greenteapress.com/thinkos/html/thinkos012.html)
* [Semaphores example in French](http://jean-luc.massat.perso.luminy.univ-amu.fr/ens/docs/thread-sem.html)
* [fork() example](https://timmurphy.org/2014/04/26/using-fork-in-cc-a-minimum-working-example/)
* [fork() multiple childs](https://stackoverflow.com/questions/876605/multiple-child-process)
* [Semaphore when programs end](https://stackoverflow.com/questions/9537068/sem-close-vs-sem-unlink-when-process-terminates)
