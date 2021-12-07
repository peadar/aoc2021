import sys
positions = [ int(x) for x in open(sys.argv[1] if len(sys.argv) > 1 else ".input").read().split(",") ]
positions.sort()
def part1cost(target, positions):
    return sum(abs(target - p) for p in positions)
centreval = positions[len(positions)//2]
print("part1: %d" % part1cost(centreval, positions))
def part2cost(target, positions):
    def onecost(val):
        return int((val * (val + 1)) // 2)
    return sum(onecost(abs(target - p)) for p in positions)
print("part2: %d" % part2cost( sum(p for p in positions) // len(positions) , positions))
