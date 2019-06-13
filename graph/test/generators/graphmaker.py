from random import *

'''
n = 20
m = 20


ed = set()

def gp(): return tuple(sorted((randint(1, n), randint(1, n))))

for i in range(m):
    p = gp()
    while (p in ed) or (p[0] == p[1]):
        p = gp()
    ed.add(p)

print(n, m)
for a, b in ed:
    print(a, b)
'''

'''
from io import StringIO
import sys

sys.stdin = StringIO(\'\'\'20 15
1 2
10 17
1 13
5 7
3 11
7 18
11 18
1 5
3 18
1 19
3 9
1 8
12 16
13 19
7 8
\'\'\')

def geti(): return map(int, input().split())

EDGE_ID = True

n, m = geti()
print('g.init(%d, %d);' % (n, m))

ctr = 0
for i in range(m):
    a, b = geti()
    if EDGE_ID:
        print('g.addEdge(%d, %d, %d); g.addEdge(%d, %d, %d);'
              % (a, b, ctr, b, a, ctr))
    else:
        print('g.addEdge(%d, %d); g.addEdge(%d, %d);' % (a, b, b, a))
    ctr += 1
'''

'''
from io import StringIO
import sys

sys.stdin = StringIO(\'\'\'20 21
11 3
17 20
1 6
12 16
15 19
6 7
7 15
13 16
12 17
7 10
9 20
4 14
7 18
3 19
4 11
2 17
15 12
20 6
16 20
2 15
3 4
\'\'\')

def geti(): return map(int, input().split())

n, m = geti()
print('g.init(%d, %d);' % (n, m))

for i in range(m):
    a, b = geti()
    print('g.addEdge(%d, %d);' % (a, b))
'''

from io import StringIO
import sys

sys.stdin = StringIO('''20 20
4 7
4 8
15 19
3 7
6 14
2 19
5 18
8 20
1 10
7 14
2 6
3 13
4 16
6 12
14 20
2 14
15 17
6 19
4 6
6 8
''')

def geti(): return map(int, input().split())

n, m = geti()
print('g.init(%d, %d);' % (n, m))

for i in range(m):
    a, b = geti()
    print('g.addEdge(%d, %d);' % (a, b))

