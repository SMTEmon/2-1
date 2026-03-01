***

# Java Multithreading & Concurrency

> [!info] Metadata
> **Topics**: Multithreading, Concurrency, Synchronization, Locks, Inter-Thread Communication
> **Language**: Java

## 1. Introduction to Threads
**Multithreading** allows a program to perform **multiple tasks concurrently** within a single process. 
* A **Process** is a program in execution (heavyweight, independent memory).
* A **Thread** is a single sequential flow of control within a process (a "lightweight process").
* **Memory Sharing**: Unlike processes, multiple threads belonging to the same process share the same memory space (heap), but each thread has its own execution call stack.

### Why do we need threads?
1. **Better CPU Utilization**: Keeps the CPU busy while other threads are waiting for I/O operations.
2. **Faster Execution**: Tasks can run in parallel on multi-core processors.
3. **Improved Responsiveness**: In user interfaces, a background thread handles heavy computing so the UI thread doesn't freeze.
4. **Resource Sharing**: Threads naturally share the same memory space.
5. **Scalability**: Allows systems to handle thousands of concurrent operations.

**Example Scenario (Web Server):**
If a web server is single-threaded, requests form a queue. If one request takes too long or hangs (bad request), the whole server hangs, and response time skyrockets. By implementing multithreading, the web server assigns a new thread to each incoming request, serving multiple requests simultaneously.

---

## 2. Creating and Running Threads

In Java, there are two ways to create a thread:
1. Implementing the `Runnable` interface. *(Preferred)*
2. Extending the `Thread` class.

> [!tip] Why `Runnable` is preferred
> Java does not support multiple inheritance. If you extend `Thread`, your class cannot extend any other class. By implementing `Runnable`, you are free to extend another class while still utilizing threading.

### Method 1: Implementing `Runnable`
You must implement the `run()` method, which serves as the entry point for the thread's execution.

```java
class MyRunnable implements Runnable {
    @Override
    public void run() {
        System.out.println("Thread started: " + Thread.currentThread().getName());
    }
}

public class MainClass {
    public static void main(String[] args) {
        // Instantiate the runnable
        MyRunnable myRunnable = new MyRunnable();
        
        // Pass the runnable to a new Thread object
        Thread t = new Thread(myRunnable);
        
        // Use start(), NOT run()
        t.start(); 
    }
}
```

### Method 2: Extending `Thread`
```java
class MyThread extends Thread {
    @Override
    public void run() {
        System.out.println("Thread started: " + Thread.currentThread().getName());
    }
}

public class MainClass {
    public static void main(String[] args) {
        MyThread t = new MyThread();
        t.start();
    }
}
```

> [!warning] `start()` vs `run()`
> Calling `t.run()` **does not start a new thread**. It simply executes the `run()` method in the current main thread like a standard method call. Calling `t.start()` instructs the JVM to allocate a new call stack and begin thread execution.

---

## 3. Thread States & Lifecycle

A thread in Java goes through several states, managed by the JVM.

```mermaid
stateDiagram-v2
    [*] --> New: Thread object created
    New --> Runnable: start() called
    Runnable --> Running: Thread Scheduler picks it
    Running --> Runnable: yield() or time slice ends
    Running --> Waiting/Blocked: sleep(), wait(), or waiting for lock
    Waiting/Blocked --> Runnable: notify(), notifyAll(), sleep finishes, lock acquired
    Running --> Dead: run() method finishes
    Dead --> [*]
```

1. **New**: A `Thread` object has been created, but `start()` has not been called yet.
2. **Runnable**: `start()` has been called. The thread is eligible to run but is waiting for CPU time from the Thread Scheduler.
3. **Running**: The Thread Scheduler has selected the thread, and the CPU is actively executing its `run()` method.
4. **Waiting/Blocked/Sleeping**: The thread is temporarily inactive. It might be sleeping, waiting for an object lock, or waiting for another thread to notify it.
5. **Dead/Terminated**: The `run()` method has completed execution. A dead thread cannot be restarted.

---

## 4. The Thread Scheduler & Priorities

The **Thread Scheduler** is a part of the JVM (or mapped directly to the underlying OS) that decides which `Runnable` thread should run at any given moment. 
* On a single-processor machine, only **one thread** can execute at a time.
* The scheduler controls time-slicing and takes threads out of the running state to let others run.

### Thread Priorities
You can suggest to the scheduler which threads are more important using priorities ranging from `1` to `10`.

```java
Thread.MIN_PRIORITY    // = 1
Thread.NORM_PRIORITY   // = 5 (Default)
Thread.MAX_PRIORITY    // = 10
```

```java
Thread t = new Thread(new MyRunnable());
t.setPriority(Thread.MAX_PRIORITY); // Set priority to 10
t.start();
```
> [!info] Note on Priority
> Setting priority is **not a guarantee**. The underlying OS thread scheduler ultimately decides the execution order. It is just a hint.

---

## 5. Controlling Thread Execution

You can influence thread execution using three primary methods: `sleep()`, `yield()`, and `join()`.

### 1. `Thread.sleep(milliseconds)`
Pauses the current thread for a specified amount of time. It throws an `InterruptedException` which must be handled.

```java
class NameRunnable implements Runnable {
    public void run() {
        for (int x = 1; x <= 3; x++) {
            System.out.println("Run by " + Thread.currentThread().getName());
            try {
                Thread.sleep(1000); // Sleep for 1 second
            } catch (InterruptedException ex) {
                ex.printStackTrace();
            }
        }
    }
}
```

### 2. `Thread.yield()`
A hint to the scheduler that the current thread is willing to yield its current use of a processor. It moves the thread from **Running** back to **Runnable** to allow other threads of the *same priority* to get their turn.

### 3. `join()`
Lets one thread "join onto the end" of another thread. If thread `A` calls `B.join()`, thread `A` will pause execution and wait until thread `B` is completely dead before resuming.

```java
Thread t1 = new Thread(new MyRunnable());
t1.start();

// The main thread will pause here until t1 is completely finished.
t1.join(); 
System.out.println("t1 has finished. Main thread resuming.");
```

---

## 6. Synchronization (Thread Safety)

When multiple threads share access to the same memory/objects, we run into **Race Conditions**. 

### The Race Condition Problem
Imagine a `Counter` class being accessed by two threads at the same time.
```java
public class Counter {
    private int count = 0;

    public int getCount() { return count; }
    public void setCount(int count) { this.count = count; }
}
```
If Thread A reads `count` (0), adds 1, but gets swapped out before saving... and Thread B reads `count` (still 0), adds 1, and saves (1). When Thread A resumes, it saves (1). Two additions happened, but the count is only 1! This is a **data inconsistency**.

### Fixing it with `synchronized`
In Java, **every object has an intrinsic lock (monitor lock)**. 
To obtain the lock, you synchronize on the object. When a thread enters a `synchronized` method, it grabs the object's lock. No other thread can enter *any* synchronized method on that same object until the lock is released.

```java
public class Counter {
    private int count = 0;

    // Both methods are now synchronized.
    public synchronized int getCount() { return count; }
    
    public synchronized void setCount(int count) { this.count = count; }
}
```

### Object Locking (Synchronized Blocks)
Instead of locking the entire method, you can lock a specific block of code to improve performance.

```java
public void doWork() {
    System.out.println("This is not synchronized, multiple threads can be here");
    
    synchronized(this) { 
        // Critical Section
        // Only one thread can execute this block at a time for this instance
        this.count++;
    }
}
```

### Static Synchronization
What happens if the method is `static`? 
Instance variables belong to objects, but `static` variables belong to the class. 

```java
public class Counter {
    private static int count = 0;

    // Locks the Counter.class object, NOT the instance!
    public static synchronized void increment() {
        count++;
    }
}
```
> [!danger] Common Synchronization Mistake
> If you have one `static synchronized` method and one non-static `synchronized` method, **they do not block each other**.
> * The static method places a lock on the `Class` object (`Counter.class`).
> * The non-static method places a lock on the `Instance` object (`this`).
> Because they lock on *different objects*, two threads can execute them simultaneously, potentially causing a race condition on shared static data.

---

## 7. Inter-Thread Communication (`wait`, `notify`, `notifyAll`)

Sometimes threads need to communicate. For example, Thread B can't do its calculations until Thread A finishes downloading the data. 

To achieve this without race conditions, we use `wait()` and `notify()`.

> [!important] The "Why???" from the slides: Why are `wait/notify` in `Object` and not `Thread`?
> Because these methods operate on **Locks**. Since *every object* in Java has a lock, the methods to manipulate those locks must reside in the base `Object` class. 
> 
> *Note: You can ONLY call `wait()`, `notify()`, or `notifyAll()` from inside a `synchronized` block/method.*

* **`wait()`**: Causes the current thread to release the lock it holds and go to sleep until another thread wakes it up.
* **`notify()`**: Wakes up *one* single thread that is waiting on this object's lock.
* **`notifyAll()`**: Wakes up *all* threads waiting on this object's lock (The thread with the highest priority generally gets the lock next). **Always prefer `notifyAll()` over `notify()` to prevent threads from being orphaned.**

### Example: Calculator and Reader

**The Calculator Thread (Does the work and notifies):**
```java
class Calculator extends Thread {
    int total;

    @Override
    public void run() {
        synchronized(this) { // Obtain lock on itself
            for(int i = 0; i < 100; i++) {
                total += i;
            }
            // Work is done, wake up any threads waiting on this Calculator object
            notifyAll(); 
        }
    }
}
```

**The Reader Thread (Waits for the calculation):**
```java
class Reader extends Thread {
    Calculator c;

    public Reader(Calculator calc) {
        this.c = calc;
    }

    @Override
    public void run() {
        // Must obtain the lock on the Calculator object to wait on it
        synchronized(c) { 
            try {
                System.out.println("Waiting for calculation...");
                c.wait(); // Releases the lock on 'c' and pauses execution
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println("Total is: " + c.total);
        }
    }
}

// Main class to run it
public class Main {
    public static void main(String[] args) {
        Calculator calculator = new Calculator();
        
        // Start 3 readers waiting on the same calculator
        new Reader(calculator).start();
        new Reader(calculator).start();
        new Reader(calculator).start();
        
        // Start the calculator
        calculator.start();
    }
}
```
> [!info] `sleep()` vs `wait()`
> * `Thread.sleep(ms)`: Thread goes to sleep but **KEEPS the lock**.
> * `object.wait()`: Thread goes to sleep and **RELEASES the lock** so other threads can use the object.

---

## 8. Thread Deadlock

**Deadlock** occurs when two or more threads are blocked forever, each waiting for the other's lock. 

### Deadlock Scenario
* Thread 1 acquires the lock for `Resource A`.
* Thread 2 acquires the lock for `Resource B`.
* Thread 1 needs `Resource B` to finish, so it waits.
* Thread 2 needs `Resource A` to finish, so it waits.
* **Result**: Neither can run until the other gives up its lock. They sit there forever.

### Code Example (Deadlock Risk)

```java
public class DeadlockRisk {
    private static class Resource {
        public int value;
    }

    private Resource resourceA = new Resource();
    private Resource resourceB = new Resource();

    // Thread 1 calls this
    public int read() {
        synchronized(resourceA) { // Locks A
            // Thread pauses here... Thread 2 locks B
            synchronized(resourceB) { // Tries to lock B (Blocked!)
                return resourceB.value + resourceA.value;
            }
        }
    }

    // Thread 2 calls this
    public void write(int a, int b) {
        synchronized(resourceB) { // Locks B
            // Thread pauses here... Thread 1 locked A
            synchronized(resourceA) { // Tries to lock A (Blocked!)
                resourceA.value = a;
                resourceB.value = b;
            }
        }
    }
}
```

### How to prevent Deadlock:
1. **Lock Ordering**: Ensure that all threads acquire locks in the exact same order (e.g., always lock A, then lock B).
2. **Timeouts**: Use concurrency utilities (like `ReentrantLock.tryLock(timeout)`) that give up if a lock isn't acquired within a certain timeframe.

---
## Further Reading
* [Oracle Java Docs on Concurrency](http://docs.oracle.com/javase/tutorial/essential/concurrency/sync.html)
* [Synchronization in Java (JavaRevisited)](http://javarevisited.blogspot.com/2011/04/synchronization-in-java-synchronized.html)