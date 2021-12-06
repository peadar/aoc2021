counts = [0]*9
for initial in ( int(split) for split in open(".input").read().split(",") ):
    counts[initial]+=1
for i in range(0, 256):
    spawning = counts[i%9]
    counts[(i + 9) % 9] = spawning
    counts[(i + 7) % 9] += spawning
    if i == 79 or i == 255:
        print("day %d: %d" % (i+1, sum(counts)))
