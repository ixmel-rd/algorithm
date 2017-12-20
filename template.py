'''
	memo
	ord("a")=97
	chr(97)='a'

'''


import sys
import math as mas

def gcd(a,b):
	a,b=max(a,b),min(a,b)
	while a%b:
		a,b=b,a%b
	return b
def lcm(a,b):
	return a//gcd(a,b)*b
	
def sieve(n):
	p=[True for i in range(n+1)]
	p[0]=p[1]=False
	end=int(n**0.5)
	for i in range(2,end+1):
		if p[i]:
			for j in range(i*i,n+1,i):
				p[j]=False
	return p

def nCr(a,b):
	if b<0:return 0
	if a<b:return 0
	tmp=1
	for i in range(a,a-b,-1):tmp*=i
	for i in range(1,b+1,1):tmp//=i
	return tmp


	
import itertools
n,m=map(int,input().split())
s=[list(map(int,input().split())) for _ in range(m)]
print(max([sum([c if t[a]<t[b] else 0 for a,b,c in s]) for t in itertools.permutations(range(n))]))
#for i in sys.stdin:
#	a,b=map(int,i.split())
#	print(gcd(a,b),lcm(a,b))
#	sys.stdout.flush()
