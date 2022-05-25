#!/usr/bin/env python3
import operator, math, sys

class TargetArea:
    def __init__(self, target):
        self.rangex=target[0]
        self.rangey=target[1]

    def between(self, pos, tup):
        return pos >= min(tup) and pos <= max(tup)

    def inrange(self, position):
        return all((self.between(*axis) for axis in zip(position,
                                                [self.rangex, self.rangey])))

def sumofints(x):
    '''
    For what N is the some of 1...N == x?
    sum of ints to n is x = (n(n+1))/2
    2x               = n(n+1)
                     = (n+1/2)^2 - 1/4
    2x-1/4           = (n+1/2)^2
    sqrt(2x-1/4)     = n+1/2
    sqrt(2x-1/4)-1/2 = n
    '''
    return math.sqrt(x * 2 - 1/4) - 1/2

class Probe:
    def __init__(self, velocity):
        self.velocity = velocity
        self.location = (0,0)
        self.highest = (0,0)

    def step(self):
        self.location = tuple(map(operator.add, self.velocity, self.location))
        if self.location[1] > self.highest[1]:
            self.highest = self.location
        if self.velocity[0] < 0:
            newx = self.velocity[0] + 1
        elif self.velocity[0] > 0:
            newx = self.velocity[0] - 1
        else:
            newx = 0
        self.velocity = (newx, self.velocity[1]-1)

    def __str__(self):
        return f"location={self.location},velocity={self.velocity}, highest: {self.highest}"
    def __repr__(self):
        return str(self)

class TestCase:
    def __init__(self, velocity, target):
        self.probe = Probe(velocity)
        self.targetArea = TargetArea(target)

    def inrange(self):
        return self.targetArea.inrange(self.probe.location)

    def run(self):
        inrangeCount = 0
        stepno = 0
        while self.probe.location[1] >= min(self.targetArea.rangey):
            self.probe.step()
            if self.inrange():
                #print(f"in range after {stepno} steps: {self.probe}")
                return True
            # print(f"\t{self.probe.location} ({inrangeCount})")
            stepno += 1
        # print(f"not in range after {stepno} steps: {self.probe}")
        return False

ta = ((119,176), (-141,-84))

total = 0
for xvel in range(math.ceil(sumofints(min(ta[0]))), max(ta[0])+1):
    print(".", file=sys.stderr, end="")
    sys.stderr.flush()
    for yvel in range(-141, 141):
        total += TestCase((xvel , yvel), ta).run()
print(f"total is {total}")
