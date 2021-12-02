#!/bin/python
import sys
inc = 0
dec = 0
tot = 0
prev = -1

for l in sys.stdin:
  l = l.strip()
  i = int(l)
  tot += 1
  if prev != -1:
      if i > prev:
          inc += 1
      elif i < prev:
          dec += 1
  prev = i

print("increase: %d, decrease: %d, total: %d" % (inc, dec, tot) )
