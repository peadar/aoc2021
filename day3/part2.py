import sys
from bisect import bisect_left
with open(sys.argv[1]) if len(sys.argv) > 1 else sys.stdin as f: values = [ int(l.strip(), 2) for l in f ]
values.sort()
maxbits = 1
while 1 << maxbits < values[-1]:
    maxbits+=1
out = 1
for p in range(2):
    top, bottom, shift, key = 0, len(values), maxbits - 1, 0
    while bottom - top > 1:
        key |= 1 << shift
        partition = bisect_left(values, key, top, bottom)
        if (partition - top <= bottom - partition) == (p == 1):
            top = partition
        else:
            bottom = partition
            key &= ~(1 << shift)
        shift -= 1
    out *= values[top]
print(out)
