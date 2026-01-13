![[telegram-cloud-photo-size-5-6284960257561791740-y.jpg]]

Solution:

```
beq  x22, x0, CASE0      # if x==0 -> CASE0
addi t0, x0, 1
beq  x22, t0, CASE1      # if x==1 -> CASE1
addi t0, x0, 2
beq  x22, t0, CASE2      # if x==2 -> CASE2
beq  x0, x0, DEFAULT     # otherwise -> default
  
CASE0:

addi x19, x0, 10         # f=10
beq  x0, x0, EXIT
 

CASE1:
addi x19, x0, 20         # f=20
beq  x0, x0, EXIT
 

CASE2:
addi x19, x0, 30         # f=30
beq  x0, x0, EXIT  

DEFAULT:
addi x19, x0, 40         # f=40  

EXIT:
```

### Nested Conditionals
![[telegram-cloud-photo-size-5-6284960257561791738-y.jpg]]

```
	bne x22, x23, ELSE1
	bit x20, x21, THEN
	addi x19, x0, 2
	bea xO, xO, EXIT
	THEN: addi x19, xO, 1;
	bea xO, xO, EXIT
	ELSE1: addi x19, x0, 0
	EXIT
```

