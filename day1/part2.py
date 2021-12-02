#!/bin/python
import sys
inc = 0
dec = 0
tot = 0
win = 0

values = [ int(l.strip()) for l in sys.stdin ]

for i,v in enumerate(values):
    newwin = win + v
    if i >= 3:
        newwin -= values[i - 3]
        tot += 1
        if newwin > win:
            inc += 1
        elif newwin < win:
            dec += 1
    win = newwin

print("total: %d, increase: %d, decrease: %d\n" % (tot, inc, dec ) )
