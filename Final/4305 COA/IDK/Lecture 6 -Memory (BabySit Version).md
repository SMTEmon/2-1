---
tags:
  - computer-architecture
  - tutorial
  - memory-hierarchy
  - cache
date: 2023-10-25
---

---

## 1. The Core Problem: Fast vs. Cheap
Imagine you are building a computer. You want the memory to be **huge** (so you can run giant games) and **lightning fast** (so there's no lag). 

Here is the problem: Physics and economics won't let you have both.
* **Fast memory (SRAM)** is incredibly expensive and physically bulky. You can only afford a tiny bit of it.
* **Slow memory (Magnetic Disk / Standard DRAM)** is cheap and holds terabytes of data, but it takes forever to load.

> [!success] The Solution: The Hierarchy
> We compromise! We put a massive, slow, cheap memory at the bottom, and a tiny, blazing-fast, expensive memory right next to the CPU. 
> 
> The trick is to **copy** the data we are actively using right now into the fast memory. 

---

## 2. Why does this actually work? (The Principle of Locality)
You might wonder: *"If the fast memory is so small, won't the CPU constantly have to wait for the slow memory anyway?"*

Actually, no. Human beings write programs in very predictable ways. We don't access data randomly. We exhibit **Locality**.

### ⏱️ Temporal Locality (Time)
If you look at a piece of data right now, you will probably look at it again in a few milliseconds.
* **Programming Example:** Think of a `for` loop `(for i=0; i<100; i++)`. The CPU reads the exact same instruction 100 times in a row! 
* **The Trick:** The first time it reads it, it's slow. But we keep a copy in the fast memory. The next 99 reads are instant.

### 📏 Spatial Locality (Space)
If you look at a piece of data right now, you will probably look at the data sitting *right next to it* very soon.
* **Programming Example:** Arrays! If you read `array[0]`, you are almost certainly going to read `array[1]` next.
* **The Trick:** When the CPU asks for `array[0]`, the memory system says, "Here is `array[0]`, and I brought `array[1]`, `array[2]`, and `array[3]` into the fast memory as well, just in case."

> [!example] The Ultimate Analogy: The Library 📚
> - **The Library (Main Memory/Hard Drive):** Huge, slow. It takes hours to go there and find a book.
> - **Your Desk (The Cache):** Tiny, lightning fast. You can grab a book in a second.
> - **Temporal Locality:** You keep opening the same textbook on your desk over and over while doing homework.
> - **Spatial Locality:** You went to the library for a history book, but you also grabbed the three books sitting next to it on the shelf, assuming they might be useful.

---

## 3. Cache Basics: Hits and Misses
The "Desk" in our computer is called the **Cache** (pronounced *cash*). 
Data is moved into the cache in chunks called **Blocks**.

When the CPU asks for a memory address, two things can happen:
1. 🟢 **Cache Hit:** The data is already in the cache! Fast execution.
2. 🔴 **Cache Miss:** The data is *not* in the cache. The CPU freezes (incurring a **Miss Penalty**) while the system runs all the way down to main memory to fetch the block.

---

## 4. How do we organize the Cache? (Direct-Mapped)
If the cache is a tiny parking lot, and main memory is a massive city of cars, how do we decide which car gets to park in which spot?

The simplest method is a **Direct-Mapped Cache**. 
*Rule: Every address in main memory has exactly ONE specific spot it is allowed to go to in the cache.*

### The Modulo Math
If your cache has 4 slots (Slot 0, 1, 2, 3), where does Memory Address 14 go?
We use the remainder (modulo) operator:
`Address MOD Cache_Size = Cache_Index`
`14 % 4 = 2`
Address 14 is only allowed to go to **Cache Slot 2**.

### The Binary Cheat Code 🧑‍💻
Computers don't do division easily, but they love binary. 
If your cache has $2^k$ blocks, you just look at the **last $k$ bits** of the binary address.
* Cache has 4 blocks. $4 = 2^2$. Therefore, $k = 2$.
* Look at Address 14 in binary: `1110`.
* Look at the last 2 bits: `10`.
* `10` in binary is the number `2`. Address 14 goes to Slot 2!

---

## 5. Identifying the Data: Tags and Valid Bits
We have a massive problem. 
Using `mod 4`, Address 2 goes to Slot 2. But Address 6 goes to Slot 2. Address 10 goes to Slot 2. Address 14 goes to Slot 2!

If the CPU looks at Slot 2, how does it know *which* address is currently parked there?

**1. The Tag (The License Plate):**
Since we used the *lower bits* to find the parking spot, we take the *remaining upper bits* of the address and store them in the cache alongside the data. This is called the **Tag**. 

**2. The Valid Bit (Is there a car here?):**
When you turn on your computer, the cache has random electrical garbage in it. We add one single bit called the **Valid Bit**.
* `0` = This slot is empty (ignore the garbage data).
* `1` = I have intentionally put real data here.

> [!info] The Golden Rule of a Cache Hit
> For a Cache Hit to occur, TWO things must be true:
> 1. The **Valid Bit** must be `1`.
> 2. The **Tag** requested by the CPU must perfectly match the **Tag** stored in the slot.

---

## 6. Walkthrough: The Classroom Example
Let's actually do the problem from slides 33-42. 

**The Setup:**
* Our cache has **8 slots** ($8 = 2^3$, so we look at the **last 3 bits** for the Index).
* Our addresses are **5 bits** long.
* So, every address looks like this: `[2 Tag Bits][3 Index Bits]`

The CPU asks for a series of addresses. Let's process them:

### Step 1: Address 22 (Binary `10110`)
* **Split it:** Tag = `10`, Index = `110` (Slot 6).
* **Look at Slot 6:** It's empty (Valid bit is 0).
* **Result:** 🔴 **MISS**. 
* **Action:** Load memory into Slot 6. Set Valid = 1, Tag = `10`.

### Step 2: Address 26 (Binary `11010`)
* **Split it:** Tag = `11`, Index = `010` (Slot 2).
* **Look at Slot 2:** It's empty.
* **Result:** 🔴 **MISS**.
* **Action:** Load memory into Slot 2. Set Valid = 1, Tag = `11`.

### Step 3: Address 22 (Binary `10110`)
* **Split it:** Tag = `10`, Index = `110` (Slot 6).
* **Look at Slot 6:** Valid is 1! Stored tag is `10`. CPU wants tag `10`. It matches!
* **Result:** 🟢 **HIT!** (Because of Temporal Locality).

### Step 4: Address 26 (Binary `11010`)
* **Split it:** Tag = `11`, Index = `010` (Slot 2).
* **Look at Slot 2:** Valid is 1. Tag is `11`. Matches!
* **Result:** 🟢 **HIT!**

### Step 5: Address 16 (Binary `10000`)
* **Split it:** Tag = `10`, Index = `000` (Slot 0).
* **Look at Slot 0:** Empty.
* **Result:** 🔴 **MISS**.
* **Action:** Load into Slot 0. Valid = 1, Tag = `10`.

### Step 6: Address 3 (Binary `00011`)
* **Split it:** Tag = `00`, Index = `011` (Slot 3).
* **Look at Slot 3:** Empty.
* **Result:** 🔴 **MISS**.
* **Action:** Load into Slot 3. Valid = 1, Tag = `00`.

### Step 7: Address 16 (Binary `10000`)
* **Split it:** Tag = `10`, Index = `000` (Slot 0).
* **Look at Slot 0:** Valid is 1. Tag `10` matches.
* **Result:** 🟢 **HIT!**

### Step 8: Address 18 (Binary `10010`) ⚠️ PAY ATTENTION HERE
* **Split it:** Tag = `10`, Index = `010` (Slot 2).
* **Look at Slot 2:** Valid is 1. BUT the stored tag is `11` (from Address 26 earlier). The CPU wants tag `10`. They do not match!
* **Result:** 🔴 **MISS**. 
* **Action:** We must **Evict** the old data. We overwrite Slot 2 with Address 18. New Tag = `10`. Address 26 is now gone from the cache.

### Step 9: Address 16 (Binary `10000`)
* **Split it:** Tag = `10`, Index = `000` (Slot 0).
* **Result:** 🟢 **HIT!** (Still sitting safely in Slot 0).

***

### 🏁 Final State of the Cache
If your professor asks what the cache looks like at the end, here is your answer:

| Index | V (Valid) | Tag | Data Stored Inside |
| :--- | :--- | :--- | :--- |
| **000** | 1 | 10 | Mem[10000] *(This is Address 16)* |
| **001** | 0 | | |
| **010** | 1 | 10 | Mem[10010] *(This is Address 18. It kicked out 26!)* |
| **011** | 1 | 00 | Mem[00011] *(This is Address 3)* |
| **100** | 0 | | |
| **101** | 0 | | |
| **110** | 1 | 10 | Mem[10110] *(This is Address 22)* |
| **111** | 0 | | |

You now know how to map memory to a cache, how to calculate hits/misses, and why caches exist in the first place!