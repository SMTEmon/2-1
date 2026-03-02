***

# Java Multithreading & Synchronization (Java 6)

## 1. Thread Basics
A thread is a lightweight process with its own call stack. Threads share access to memory within a single process.
- **Why use threads?** Better CPU utilization, faster execution, improved responsiveness.

### Creating & Starting Threads
**Two Ways to Create:**
1. `extends Thread`
2. `implements Runnable` (**Preferred:** allows extending other classes).

```java
class MyThread implements Runnable {
    public void run() {
        System.out.println("Thread Running");
    }
}

// How to instantiate and start:
Thread t = new Thread(new MyThread());
t.start(); 
```

> [!danger] Exam Trap: `start()` vs `run()`
> - Calling `t.start()` creates a new thread and executes the `run()` method.
> - Calling `t.run()` **does NOT** create a new thread. It just acts as a normal method call on the main thread. Output behavior (order) is **never guaranteed**.

---

## 2. Thread Lifecycle & Scheduler
The **Thread Scheduler** (part of JVM/OS) decides which eligible thread actually runs. On a single-CPU machine, only one thread/stack executes at a time.

### Thread States
`New` ➔ `Runnable` ⟷ `Running` ➔ `Dead`
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ⬑ `Waiting/Blocking` ⬏

### Thread Priorities
Used by the scheduler to determine which thread to run.
- `Thread.MIN_PRIORITY` = **1**
- `Thread.NORM_PRIORITY` = **5** (Default)
- `Thread.MAX_PRIORITY` = **10**
- *Usage:* `t.setPriority(8);`

---

## 3. Controlling Execution
Methods to prevent a thread from executing:

| Method | Behavior |
| :--- | :--- |
| **`sleep(ms)`** | Pauses thread for `x` milliseconds. Throws `InterruptedException`. |
| **`yield()`** | Sends current thread back to *Runnable* to allow other threads of the **same priority** to run. |
| **`join()`** | `t.join()` means the current thread stops and waits for thread `t` to finish (die) before continuing. |

---

## 4. Synchronization (Solving Race Conditions)
Every object in Java has a **lock**. Synchronization ensures only one thread can execute a locked method/block at a time.

- **How it works:** Thread attempts to get the lock. If locked by another thread, it goes to sleep/blocks until the lock is released. 
- **Non-synchronized methods:** Can still be accessed freely by other threads, even if an object is locked.

### Instance vs. Static Locks
> [!important] Crucial Concept
> - **Instance Method (`public synchronized void doX()`)**: Locks the specific object instance (`this`). 
> - **Static Method (`public static synchronized void doY()`)**: Locks the Class object (`ClassName.class`). Applies across *all* instances of the class.

> [!warning] Common Exam Mistake
> Mixing a `static synchronized` method and a `synchronized` (non-static) method. Because they use **two different locks** (Class vs. Instance), two threads CAN access them simultaneously!

### Synchronized Blocks
You can lock on a specific object instead of a whole method:
```java
synchronized(myInstance) { // myInstance is the object whos key u r gonna grab,
							// if available
    // critical section
}
```

```java
public synchronized void deposit(int amount) { // kinda like synchronized(this)
							// locks its own key
	this.balance += amount;
}
```

These two are exactly the same thing. Adding synchronized to a method header is just a shorter way of wrapping the whole method body in synchronized(this).



## 5. Inter-Thread Communication
Threads communicate using `wait()`, `notify()`, and `notifyAll()`. 
- **Rule 1:** They **must** be called from within a `synchronized` context. 
- **Rule 2:** They are methods of the `Object` class (not `Thread`), because locks operate on objects.

### Wait vs. Sleep
| Feature | `wait()` | `Thread.sleep()` |
| :--- | :--- | :--- |
| **Releases Lock?** | **YES** - releases lock so others can run. | **NO** - holds the lock while sleeping. |
| **Class** | `Object` | `Thread` |

### Notify vs NotifyAll
- `notify()`: Wakes up exactly *one* thread waiting in the queue for that object's lock.
- `notifyAll()`: Wakes up *all* waiting threads. The one with the highest priority generally gets the lock next.

### Classic ITC Example
```java
// Inside Thread B (Doing the work)
synchronized(this) {
    total += i;
    notify(); // Tells Thread A that work is done
}

// Inside Thread A (Waiting for result)
synchronized(b) {
    b.wait(); // Releases lock and waits for Thread B to notify
    System.out.println("Total: " + b.total);
}
```

---

## 6. Deadlock
Occurs when two or more threads are blocked forever, each waiting for a lock held by the other.
- *Example:* Thread 1 locks `Resource A` and wants `Resource B`. Thread 2 locks `Resource B` and wants `Resource A`. Neither can proceed.