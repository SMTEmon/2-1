### 1.55 Solution

The **Minimum Pumping Length ($p$)** is the smallest integer such that any string $s$ in the language with length $|s| \ge p$ can be "pumped" (split into $xyz$ where $xy^iz$ is also in the language for all $i \ge 0$).

---

**a. $0001^*$**

- **Minimum Pumping Length: 4**
        
- **Justification:** The string $s = 000$ (length 3) is in the language but cannot be pumped.
    
    - If we pump any `0`, we change the number of leading zeros (must be exactly 3).
        
    - We can only pump the `1`s. The first `1` appears at index 4. Therefore, $p$ must be at least 4 to include the first `1` in the pumpable section $y$.
        

**b. $0^*1^*$**

- **Minimum Pumping Length: 1**
    
- **Justification:** Any string in this language has length $\ge 0$. For any string $s$ with length $\ge 1$:
    
    - If $s$ contains a `0`, we can pump the `0` ($0 \to 00$ or remove it).
        
    - If $s$ consists only of `1`s, we can pump a `1`.
        
    - Since we can always pump a single character found in the string, $p=1$.
        

**c. $001 \cup 0^*1^*$**

- **Minimum Pumping Length: 1**
    
- **Justification:** Note that the string $001$ is already included in the set $0^*1^*$. Therefore, the language simplifies to just $0^*1^*$, which matches problem (b). The answer is the same.
    

**d. $0^*1^+0^+1^* \cup 10^*1$**

- **Minimum Pumping Length: 3**
    
- **Justification:** Consider the string $s=10$ (from the left part) and $s=11$ (from the right part). Both have length 2.
    
    - $s=10$: Removing either character (pumping down) results in `1` or `0`, neither of which is in the language. Thus, strings of length 2 cannot be guaranteed to pump.
        
    - This forces $p > 2$.
        
    - For length 3 strings (e.g., $101$, $010$), we can always find a pumpable character (like the middle digit).
        

**e. $(01)^*$**

- **Minimum Pumping Length: 2**
    
- **Justification:** Consider the string $s = 01$ (length 2).
    
    - If $p=1$, we would have to pump just `0` or just `1`, creating `001` or `011`, which violates the pattern.
        
    - If $p=2$, we can choose $y = 01$. Pumping gives $0101$, and removing gives $\epsilon$, both of which are valid.
        

**f. $\varepsilon$**

- **Minimum Pumping Length: 1**
    
- **Justification:** The language contains only the empty string (length 0).
    
    - The pumping lemma condition applies to strings where $|s| \ge p$.
        
    - If $p=1$, there are no strings with length $\ge 1$, so the condition is "vacuously true" (there are no strings to fail the test).
        
    - $p$ cannot be 0 because we cannot split length 0 into $xyz$ with $|y| > 0$.
        

**g. $1^*01^*01^*$**

- **Minimum Pumping Length: 3**
    
- **Justification:** This language requires exactly two `0`s.
    
    - Consider $s = 00$ (length 2). We cannot pump the `0`s because that would change the count (e.g., to 3 zeros).
        
    - We must pump `1`s. Since $s=00$ has no `1`s, it cannot be pumped.
        
    - Therefore, $p$ must be strictly greater than 2. For length 3 strings (e.g., $001$), we can reach a `1` to pump.
        

**h. $10(11^*0)^*0$**

- **Minimum Pumping Length: 4**
    
- **Justification:** Consider the string $s = 100$ (length 3).
    
    - It consists of the prefix `10`, an empty middle loop, and suffix `0`.
        
    - We cannot pump the `1` or `0` in the fixed prefix/suffix without breaking the structure.
        
    - We cannot pump internal parts because there are none.
        
    - Therefore, $p > 3$. The next valid string is length 5 ($10100$), where we can pump the `1`.
        

**i. $1011$**

- **Minimum Pumping Length: 5**
    
- **Justification:** This is a finite language. The Pumping Lemma says if a string has length $\ge p$, it can be pumped to produce infinite variations.
    
    - Since finite languages cannot be pumped infinitely, $p$ must be larger than the length of the longest string to ensure the condition $|s| \ge p$ is never met.
        
    - Length is 4, so $p = 4 + 1 = 5$.
        

**j. $\Sigma^*$**

- **Minimum Pumping Length: 1**
    
- **Justification:** This language contains _all_ strings.
    
    - We can take any character in any string and repeat it (or remove it), and the result will still be a string in $\Sigma^*$.
        
    - For any string with length $\ge 1$, we can simply pick the first character as $y$.