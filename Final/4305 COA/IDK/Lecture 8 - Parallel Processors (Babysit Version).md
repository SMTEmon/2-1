---
tags: [tutorial, computer-architecture, parallel-processing, multi-core, amdalhs-law]
course: CSE 4305 - Computer Organization and Architecture
description: A beginner-friendly breakdown of Lecture 8.
---

---

## 1. The Big Picture: Why do we even need this?

For a long time, computer engineers made computers faster by just increasing the clock speed of a single processor (think 1GHz to 2GHz to 3GHz). But eventually, they hit a wall: if they made it any faster, the chip would literally melt. 

**The Solution:** Instead of building one giant, power-hungry, super-fast processor, what if we put **several smaller, efficient processors** onto a single chip? 
* This is called a **Multicore Microprocessor**.
* Most modern chips use **SMP (Shared Memory Processing)**, meaning all these little cores share the same physical RAM.

**The Catch:** Having 8 cores is great, but ==if your software is only written to use 1 core, the other 7 will just sit there doing nothing.== This lecture is all about the struggle of getting software to actually use all these cores effectively.

---

## 2. Hardware vs. Software (Getting the terms straight)

Before we get into the math, we have to separate the physical machine from the code.

### The Hardware (The Engine)
* **Serial Hardware:** Only has one core. It can physically only do one thing at a time.
* **Parallel Hardware:** Has multiple cores (like your laptop's CPU or your graphics card/GPU). It can physically do multiple things at the exact same time.

### The Software (The Instructions)
* **Sequential Software:** Code written in a straight line. "Do step A, then step B, then step C." 
* **Concurrent Software:** Code written to overlap. "Start step A, and while that's loading, start step B."

> [!tip] The Golden Rule
> You can run *Sequential Software* on *Parallel Hardware*, but it will only run on one core. When we talk about **Parallel Processing Programs** in this class, we mean software that is specifically designed to spread its work across multiple hardware cores.

---

## 3. Amdahl's Law (The Ultimate Buzzkill)

Imagine you have a task: You need to read a 100-page book and then write a 1-page summary. 
* You can hire 100 people to each read 1 page at the same time (Parallel). 
* But only 1 person can write the final summary (Sequential). 

**Amdahl's Law** is a mathematical formula that says: *No matter how many cores you add, your maximum speedup is bottlenecked by the part of the code that CANNOT be parallelized.*

Here is the formula:
$$ Speedup = \frac{1}{(1 - F) + \frac{F}{n}} $$
* **$F$** = The fraction of your code that is parallelizable (e.g., 0.80 for 80%).
* **$(1 - F)$** = The fraction of your code that is sequential (e.g., 0.20 for 20%).
* **$n$** = The number of processors.

### Let's do the math from the slide:
**The Question:** You want your program to run 90 times faster using 100 processors. What percentage of your code is allowed to be sequential?

**The Step-by-Step Solution:**
1. Plug in what we know: $Speedup = 90$, and $n = 100$.
2. $90 = \frac{1}{(1 - F) + \frac{F}{100}}$
3. Multiply both sides by the denominator: $90 \times ((1 - F) + 0.01F) = 1$
4. Simplify the inside: $1 - 1F + 0.01F$ becomes $1 - 0.99F$.
5. Now we have: $90 \times (1 - 0.99F) = 1$
6. Distribute the 90: $90 - 89.1F = 1$
7. Solve for F: $89.1F = 89 \implies F = 0.999$
8. If $F$ (parallel part) is 0.999, then the sequential part is $1 - 0.999 = 0.001$.

**The Takeaway:** To get a 90x speedup from 100 cores, **99.9% of your code must be parallelizable.** Only 0.1% can be sequential. This proves how incredibly hard it is to get perfect speedups!

---

## 4. Scaling: How to cheat Amdahl's Law

Since Amdahl's law is so brutal, how do supercomputers work? The secret is **Scaling**. If you make the problem *bigger*, the parallelizable portion usually grows much faster than the sequential portion.

* **Strong Scaling:** Keeping the problem the *same size* but throwing more cores at it. (Hard to get good speedups here).
* **Weak Scaling:** Increasing the problem size proportionally as you add cores. (This yields much better speedups!).

> [!example] The Matrix Math Example Simplified
> Let's say your code does 10 sequential additions, and then a bunch of parallel matrix additions. Let `t` = time to do one addition.
> 
> **Small Problem (10x10 matrix = 100 parallel additions):**
> * 1 core takes: 10t + 100t = 110t.
> * 40 cores take: 10t + (100t / 40) = 12.5t.
> * Speedup: $110 / 12.5 =$ **8.8x faster**. (Not great for 40 cores).
> 
> **Big Problem (20x20 matrix = 400 parallel additions):**
> * 1 core takes: 10t + 400t = 410t.
> * 40 cores take: 10t + (400t / 40) = 20t.
> * Speedup: $410 / 20 =$ **20.5x faster**. 
> 
> *See? By making the problem bigger, the 40 cores became much more useful.*

---

## 5. Load Balancing (The "Group Project" Problem)

In the previous example, we assumed all 40 cores split the 400 additions perfectly (each did 10 additions). 
But what if the work isn't balanced? What if this is a group project and one core does way more work?

**Scenario:** We have 400 parallel tasks and 40 cores. 
Instead of doing 2.5% of the work, **one core gets stuck doing 12.5% of the work (50 tasks).** The other 39 cores split the remaining 350 tasks.

* The busy core takes `50t` to finish.
* The 39 lazy cores take `350t / 39 = 9t` to finish.
* Because they run at the same time, the whole system has to wait for the slowest core. So the parallel part takes **50t**.
* Total time = 10t (sequential) + 50t (parallel) = **60t**.
* **New Speedup:** $410t / 60t =$ **7x faster**.

**The Takeaway:** Because *one* core got overloaded, our speedup dropped from **20.5x down to 7x**. This is why **Load Balancing** is crucial in parallel programming!

---

## 6. Software: Processes vs. Threads

Okay, let's pivot. How does the Operating System organize this work? It uses Processes and Threads.

| Concept     | What is it?                     | Analogy                          | Memory                                                                         | Crash Risk                                                         |
| :---------- | :------------------------------ | :------------------------------- | :----------------------------------------------------------------------------- | :----------------------------------------------------------------- |
| **Process** | A whole running program.        | Opening the Google Chrome App.   | Has its own private memory. Slow to talk to other processes.                   | Safe. If one process crashes, the computer keeps running.          |
| **Thread**  | A mini-task *inside* a process. | Opening multiple Tabs in Chrome. | Shares memory with other threads in the same process. Very fast communication. | Dangerous. If one thread crashes, the whole Process (app) crashes. |

---

## 7. Hardware Multithreading (Tricking the CPU)

Here is a wild fact: CPUs are so incredibly fast that they spend most of their time sitting around waiting for data to arrive from the RAM. 
**Hardware Multithreading** is a trick to keep the CPU busy when a thread is stalled (waiting for RAM).

There are three ways to do this:

### 1. Fine-Grained Multithreading
* **How it works:** The CPU switches between threads every single clock cycle. (Thread A, then Thread B, then Thread C, repeat). If a thread is stalled, it just skips it.
* **Analogy:** A fast waiter bouncing between 3 tables.
* **The Good:** No CPU cycles are ever wasted.
* **The Bad:** It slows down individual threads. Even if Thread A has everything it needs, it has to wait its turn in the cycle.

### 2. Coarse-Grained Multithreading
* **How it works:** The CPU runs Thread A continuously until Thread A hits a massive roadblock (like needing to fetch data from RAM). Only *then* does the CPU switch to Thread B.
* **Analogy:** Checking out at the grocery store. You check out all your items until your credit card declines. You step aside to call the bank (long stall), and the cashier starts scanning the next customer.
* **The Good:** Doesn't slow down a thread unnecessarily. 
* **The Bad:** When switching, the CPU has to flush its pipeline and load the new thread, which has a start-up time penalty.

### 3. Simultaneous Multithreading (SMT)
* **How it works:** Modern CPU cores have multiple execution units inside them (like having 4 ALUs). SMT allows instructions from *multiple different threads* to run at the **exact same time** on a single core by filling in the empty slots.
* **Analogy:** A chef boiling pasta (Thread A) on the stove while chopping onions (Thread B) on the cutting board at the exact same time.
* **The Good:** Unbelievably efficient. Maximizes CPU usage perfectly.
* **The Bad:** Threads share the same hardware resources, so they might fight over them (contention). 

---

## 8. Does SMT actually work? (The Proof)

The lecture ends with a chart looking at the **Intel Core i7 960** (which uses SMT, though Intel calls their version "Hyper-Threading").

**The Results:**
1. **Speedup:** On average, turning on SMT gives a **1.31x speedup** (31% faster). This is amazing because adding SMT logic to a CPU chip barely takes up any physical space!
2. **Energy:** It improves energy efficiency by **1.07x**. It gets the job done faster, allowing the CPU to go back to sleep sooner, saving battery.

***
**TL;DR Summary for the Exam:**
1. Parallel hardware is useless without parallel software.
2. **Amdahl's Law:** Un-parallelizable code bottlenecks your maximum speed.
3. **Weak Scaling** (bigger problems) beats Amdahl's Law.
4. **Load balancing** is essential; you are only as fast as your slowest worker.
5. **Threads** share memory; **Processes** do not.
6. **SMT** executes multiple threads at the exact same time on one core, boosting performance by ~31%.