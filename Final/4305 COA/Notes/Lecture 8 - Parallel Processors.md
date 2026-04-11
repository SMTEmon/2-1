---
tags: [computer-architecture, parallel-processing, multi-core, amdalhs-law, multithreading]
course: CSE 4305 - Computer Organization and Architecture
instructor: Sabrina Islam
---

# Lecture 8: Parallel Processors

## 1. Introduction to Parallel Processing
The traditional method of making computers faster—simply increasing the clock speed of a single large processor—has hit physical limits (often referred to as the **Power Wall** and the end of **Dennard Scaling**). 

* **The Core Idea:** Create powerful computers by connecting many existing, smaller, and highly efficient processors (cores).
* **The Goal:** Achieve **High Performance** through:
	* **Scalability:** The ability to handle growing amounts of work by adding resources.
	* **Availability:** If one processor fails in an $n$-processor system, it continues to provide service with $n-1$ processors.
	* **Power Efficiency:** Replacing one large, inefficient, heat-generating processor with many smaller ones delivers better performance per joule of energy.
* **The Catch:** This hardware is useless unless the **software can efficiently use them**. Programmers must adapt and write parallel software.

---

## 2. Hardware and Software Terminologies

To understand parallel processing, we must separate how *hardware* executes from how *software* is written.

### Hardware Taxonomy
* **Serial Hardware:** Processes one task at a time, sequentially (e.g., a traditional single-core Pentium processor).
* **Parallel Hardware:** Executes multiple tasks simultaneously using multiple processing units (e.g., a modern Multi-core CPU, GPUs).

### Software Taxonomy
* **Sequential Software:** Executes one instruction at a time in a fixed order. (e.g., A standard `C` program running on a single thread).
* **Concurrent Software:** Multiple instructions can execute at overlapping time intervals. (e.g., A Java-based multi-threaded web server).

> [!important] The Matrix
> * Sequential software can run on serial OR parallel hardware (though it will only utilize one core).
> * Concurrent software can run on serial hardware (via time-slicing/context switching) OR parallel hardware (true simultaneous execution).
> * **In this course context:** "Parallel Processing Program" or "Parallel Software" refers to **either sequential or concurrent software running on parallel hardware**.

### Multiprocessors vs. Multicore
* **Multiprocessor:** A general computer system with at least two processors.
* **Multicore Microprocessor:** Multiple processors (cores) housed inside a *single integrated circuit* (chip).
* **SMP (Shared Memory Processor):** Almost all modern multicores are SMPs. This is a parallel processor architecture where all cores share a **single physical address space** (Uniform Memory Access).

### Task-Level vs. Parallel Processing Programs
* **Task-Level (Process-Level) Parallelism:** Running completely independent programs simultaneously to achieve high throughput (e.g., running Chrome, Spotify, and Word at the same time).
* **Parallel Processing Program:** A *single* program written to run on multiple processors simultaneously to solve a single problem faster. *(This is the focus of this lecture).*

---

## 3. The Challenges of Parallel Programming

Writing parallel software is notoriously difficult. Why not just stick to uniprocessors? 
Because uniprocessor design techniques (like Instruction-Level Parallelism - ILP) have plateaued. We *must* use multiprocessors for better performance.

**Why is parallel software hard to write?**
1. **Partitioning:** Breaking the task into perfectly parallelizable pieces.
2. **Scheduling:** Assigning those pieces to the right processors.
3. **Load Balancing:** Ensuring no processor is sitting idle while another does all the work.
4. **Synchronization:** Managing when processors need to wait for data from each other.
5. **Overhead:** The time wasted communicating between processors instead of doing actual computation.

> [!quote] The Reporter Analogy
> <details>
> <summary>Detailed Reporter Analogy</summary>
>
> The **reporter analogy** is a classic teaching tool used to explain key concepts in parallel processing, such as concurrency, shared resources, race conditions, and synchronization. Here’s how it works and what it illustrates.
>
> ### The Setup
> Imagine a busy **newsroom** where several **reporters** (analogous to **threads** or **processes**) are working on the same big story. They all share a single **whiteboard** (analogous to **shared memory** or a **shared resource**) where they can write facts, update the story, or read what others have written. Each reporter works independently and at their own pace.
>
> ### Key Parallel Processing Concepts Illustrated
>
> 1. **Concurrent Execution**
> 	- **Analogy:** Reporters write, read, and erase on the whiteboard simultaneously, often interrupting each other.
> 	- **Parallel concept:** Multiple threads execute seemingly at the same time, interleaving their operations on shared data.
>
> 2. **Race Condition**
> 	- **Analogy:** Two reporters see the same headline on the whiteboard. Both decide to update it by adding a new fact. Reporter A reads the current text, adds “- Source X,” and writes it back. Meanwhile, Reporter B does the same but based on the *original* text. The final whiteboard contains only B’s change – A’s update is **lost** because their operations overlapped.
> 	- **Parallel concept:** A race condition occurs when the outcome depends on the unpredictable timing of thread execution, leading to corrupted data.
>
> 3. **Mutual Exclusion (Lock / Mutex)**
> 	- **Analogy:** To prevent chaos, the editor introduces a **marker** (e.g., a red pen) that only one reporter can hold at a time. To update the whiteboard, a reporter must **acquire the marker**, write their update, then **release it**.
> 	- **Parallel concept:** A mutex (mutual exclusion lock) ensures that only one thread enters a **critical section** (the code that accesses shared data) at a time.
>
> 4. **Deadlock**
> 	- **Analogy:** Two reporters need *two* resources to finish their tasks: the red marker (for writing) and a blue marker (for drawing a diagram). Reporter 1 grabs the red marker, Reporter 2 grabs the blue marker. Each waits forever for the other to release the needed marker. Both are stuck.
> 	- **Parallel concept:** Deadlock occurs when threads hold resources while waiting for others, resulting in a standstill.
>
> 5. **Starvation**
> 	- **Analogy:** A slow, junior reporter always gives up the marker politely whenever a senior reporter asks for it. The senior reporters keep using the marker, and the junior never gets a chance to write.
> 	- **Parallel concept:** Starvation happens when a thread is repeatedly denied access to a resource because other threads with higher priority or more aggressive locking dominate.
>
> 6. **Coordination (Semaphores / Condition Variables)**
> 	- **Analogy:** A **news editor** tells reporters: “Only three of you may work on the whiteboard at once. The rest must wait.” A **countdown token** system manages this.
> 	- **Parallel concept:** A **semaphore** limits concurrent access to a resource. Condition variables allow threads to wait for a specific state (e.g., “wait until the whiteboard has a certain fact”).
>
> ### Why the Analogy Works
> - It’s **intuitive**: Most people understand the chaos of multiple people sharing a single physical board.
> - It clearly shows **interleaving problems** (race conditions) and **solutions** (locks, semaphores).
> - It scales to more complex ideas like **readers-writer locks** (multiple reporters can read the whiteboard simultaneously, but writing requires exclusive access).
>
> ### Limitations of the Analogy
> - Real parallel systems involve **non‑deterministic interleavings** and **memory consistency models** that the whiteboard doesn’t fully capture.
> - The analogy focuses on **shared memory** parallelism, not message‑passing (e.g., MPI).
> - It downplays **performance** aspects like cache coherence and false sharing.
>
> ### Takeaway
> The reporter analogy is a simple, memorable way to grasp why parallel programs need careful synchronization – and what can go wrong without it. Next time you debug a race condition, think of those reporters stepping on each other’s toes at the whiteboard.
> </details>

---

## 4. Amdahl's Law

**Amdahl's Law** dictates the theoretical maximum speed-up you can achieve by parallelizing a system. It states that the performance improvement is limited by the sequential fraction of the program (the part that *cannot* be parallelized).

$$ Speedup = \frac{T_{sequential}}{T_{parallel}} $$
$$ Speedup = \frac{1}{(1 - F_{parallelizable}) + \frac{F_{parallelizable}}{n}} $$

Where:
* $F_{parallelizable}$ = The fraction of the program that can be made parallel.
* $(1 - F_{parallelizable})$ = The sequential fraction (must be run on 1 core).
* $n$ = Number of processors.

> [!info] Supplementary Knowledge: The Mathematical Limit
> As $n \to \infty$, the term $\frac{F}{n}$ approaches 0. Therefore, the absolute maximum speedup possible is $\frac{1}{1 - F}$. If a program is 95% parallelizable, maximum speedup with *infinite* processors is $1 / 0.05 = 20x$.

### Amdahl's Law Example Calculation
**Problem:** You want to achieve a speed-up of 90x using 100 processors. What percentage of the original computation can be sequential?

**Solution:**
1. $90 = \frac{1}{(1 - F) + \frac{F}{100}}$
2. $90 \times ((1 - F) + \frac{F}{100}) = 1$
3. $90 \times (1 - F + 0.01F) = 1$
4. $90 \times (1 - 0.99F) = 1$
5. $90 - 89.1F = 1$
6. $89.1F = 89 \implies F = \frac{89}{89.1} = 0.9988 \approx 0.999$
7. Fraction Sequential $= 1 - 0.999 = 0.001$ (or **0.1%**)

*Conclusion: To get a 90x speedup from 100 cores, 99.9% of your code must be perfectly parallel!*

---

## 5. Scaling: Strong vs. Weak Scaling

Speeding up is challenging when the problem size is fixed, but as problem sizes grow, parallelization becomes much more effective.

* **Strong Scaling:** Achieving speed-up on a multiprocessor *without* increasing the size of the problem. (Governed by Amdahl's Law).
* **Weak Scaling:** Achieving speed-up by increasing the size of the problem *proportionally* to the increase in the number of processors. (Governed by Gustafson's Law).

> [!warning] Hardware Interference in Weak Scaling
> Weak scaling can suffer if the memory hierarchy interferes. If a scaled-up dataset no longer fits in the Last Level Cache (LLC) of a multicore processor, the cache miss rate skyrockets, making performance worse than expected.

### Scaling Example (Matrix Addition)
Assume a sum of 10 scalar variables (sequential) and a matrix sum (parallel). Let $t$ be the time for one addition.

**Scenario A: 10x10 Matrix (100 parallel additions, 10 sequential)**
* $T_{single\_core} = 10t + 100t = 110t$
* With 10 processors: $T_{10} = 10t + \frac{100t}{10} = 20t \implies Speedup = \frac{110}{20} = 5.5x$
* With 40 processors: $T_{40} = 10t + \frac{100t}{40} = 12.5t \implies Speedup = \frac{110}{12.5} = 8.8x$
*(We get 55% potential with 10 cores, but only 22% potential with 40 cores).*

**Scenario B: 20x20 Matrix (400 parallel additions, 10 sequential)**
* $T_{single\_core} = 10t + 400t = 410t$
* With 10 processors: $T_{10} = 10t + \frac{400t}{10} = 50t \implies Speedup = \frac{410}{50} = 8.2x$
* With 40 processors: $T_{40} = 10t + \frac{400t}{40} = 20t \implies Speedup = \frac{410}{20} = 20.5x$
*(Utilization improves drastically as the problem size scales up!).*

---

## 6. The Importance of Load Balancing

What happens if one processor does more work than the others? It becomes a bottleneck.

**Using Scenario B (20x20 matrix, 400 additions, 40 processors):**
Perfect balance = Each core does 10 additions ($2.5\%$ load). $Speedup = 20.5x$.

**Unbalanced Scenario 1: One core does 5% (20 additions), the other 39 share the rest.**
* $T_{parallel} = Max(\frac{380t}{39}, 20t) = 20t$ (The 39 cores finish in ~9.7t and sit idle waiting for the busy core).
* $T_{total} = 10t (seq) + 20t (par) = 30t$
* **New Speedup:** $410t / 30t = 14x$ *(Dropped from 20.5x to 14x!)*

**Unbalanced Scenario 2: One core does 12.5% (50 additions), the other 39 share the rest.**
* $T_{parallel} = Max(\frac{350t}{39}, 50t) = 50t$
* $T_{total} = 10t (seq) + 50t (par) = 60t$
* **New Speedup:** $410t / 60t = 7x$ *(The 39 cores are utilized less than 20% of the time).*

---

## 7. Processes vs. Threads

Before understanding hardware multithreading, we must distinguish the software concepts of processes and threads.

| Feature | Process | Thread |
| :--- | :--- | :--- |
| **Definition** | An independent execution unit representing a running program. | A lightweight execution unit *within* a process. |
| **Memory Space** | Independent. Each has its own code, data, and stack space. | Shared. Threads within the same process share memory (code/data), but have their own registers and stack. |
| **Communication** | Slower. Requires IPC (Inter-Process Communication). | Faster. They communicate directly via shared memory. |
| **Failure Isolation**| High. If one process crashes, others are unaffected. | Low. If a thread crashes (e.g., segfault), it usually crashes the entire process. |
| **Analogy** | Multiple instances of a web browser running. | Multiple tabs running inside a single browser instance. |

---

## 8. Hardware Multithreading

**Hardware Multithreading** is a technique to increase processor utilization by switching to another thread when the current thread is stalled (e.g., waiting on a cache miss). 
*Do not confuse this with multiprocessing (having physical multiple cores).*

### Approach 1: Fine-Grained Multithreading
* **Mechanism:** The CPU switches between threads at *every single clock cycle* in a round-robin fashion, skipping stalled threads.
* **Analogy:** A restaurant with multiple waiters; the chef takes one order from waiter A, then one from waiter B, back to A, etc.
* **Pros:** Highly efficient at hiding both short and long stalls. No CPU cycles are wasted.
* **Cons:** Slows down the execution of an individual thread. Even if a thread has no stalls, it is delayed waiting for its turn in the round-robin cycle.

### Approach 2: Coarse-Grained Multithreading
* **Mechanism:** The CPU runs one thread continuously until it hits a *significant, long stall* (like a trip to main memory). Only then does it switch to a new thread.
* **Analogy:** Checkout counters at a supermarket. You check out completely until your card declines, then you step aside and the next person goes while you figure it out.
* **Pros:** Individual threads aren't slowed down unnecessarily. Great for handling long memory accesses.
* **Cons:** Pipeline start-up costs. When a stall occurs, the CPU must flush its pipeline and refill it with the new thread's instructions. Inefficient for short stalls.

### Approach 3: Simultaneous Multithreading (SMT)
*(Intel calls this "Hyper-Threading")*
* **Mechanism:** Advanced technique where a single CPU core executes instructions from *multiple threads in the exact same clock cycle*. 
* **Concept:** Modern "Superscalar" processors have multiple execution units (e.g., 4 ALUs). A single thread rarely uses all 4 at once. SMT fills the unused execution slots with instructions from another thread.
* **Analogy:** A Chef with multiple workstations. While boiling pasta (Thread A) on the stove, they are chopping vegetables (Thread B) on the counter simultaneously.
* **Pros:** Maximizes CPU usage. Dramatically improves throughput and hides stalls perfectly.
* **Cons:** Shared resources can lead to contention (threads fighting for the same ALU). Not beneficial if running purely single-threaded tasks.

### Visualizing the Issue Slots

Imagine a CPU that can issue 4 instructions per clock cycle. The colored blocks represent an instruction from a thread being executed.

* **No Multithreading:** Lots of empty white space (wasted cycles) when a thread stalls.
* **Coarse MT:** Solid blocks of one color, then a gap (pipeline flush), then solid blocks of another color.
* **Fine MT:** Rows alternate colors every cycle. (Blue, Green, Blue, Green).
* **SMT:** A single row (clock cycle) contains multiple colors (e.g., 2 Blue instructions, 1 Green, 1 Empty). 

---

## 9. SMT Performance and Energy Metrics

Based on data from the Intel Core i7 960 (which uses SMT):
* **Performance:** Hardware multithreading yields an average speed-up of **1.31x** (a 31% improvement). This is highly cost-effective given that adding SMT requires less than 5% extra chip area.
* **Energy Efficiency:** The average improvement in the energy efficiency ratio is **1.07**. 
*(An energy efficiency ratio of >1 indicates an improvement, meaning SMT completes tasks faster and goes to a low-power state sooner, saving energy overall).*

---
**References:**
1. Lecture Notes: Sabrina Islam, IUT.
2. *Computer Architecture: A Quantitative Approach* (RISC-V Edition) by David A. Patterson and John L. Hennessy.