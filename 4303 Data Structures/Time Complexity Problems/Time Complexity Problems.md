1. Find the time complexity:
   ```
   int a = 0, i = N;
   while (i>0) {
	   a += i;
	   i /= 2;
	}
   ```
### Solution-1
   The loop starts at i = N, and in each iteration, i /= 2 until i = 0
   *key* : Write out the values of N: 
   
   $(n, n/2, n/4, ... 1)$
   
   This follows a geometric sequence where i is halved in each step. so r = 1/2. This also tells us that i <=1
   
   We can write i as $i = N/2^k$
   and find k such that $N/2^k <=1$
   
   This gives, $k>= log_2N.$ Hence, K = $\lceil (log_2N) \rceil$

2. Which of the following is not bounded by $O(n^2)$?
		a. $15^{10}*n+12099$
		b. $n^{1.98}$
		c. $\frac{n^3}{\sqrt{ n }}$
		d. $2^{20}*n$
### Solution-2

Bounded by O(n^2) also means not more than O(n^2). Answer is c.

3. 