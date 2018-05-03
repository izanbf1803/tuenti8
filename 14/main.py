from fractions import Fraction
from scipy.spatial import Voronoi, voronoi_plot_2d
import matplotlib.pyplot as plt
import math
import sys
from heapq import *
from collections import defaultdict

debug = False

inf = float("inf")

def parseFrac(f):
    return float(Fraction(f))

def parsePoint(s):
    sx, sy = s.split()
    return (parseFrac(sx), parseFrac(sy))

def array_remove(arr, discard):
    res = []
    for e in arr:
        if e != discard:
            res.append(e)
    return res

def gen_graph(vor, adj, locked):
    for i in range(len(vor.ridge_vertices)):
        if i not in locked:
            region = vor.ridge_vertices[i]
            reg = array_remove(region, -1)
            if len(reg) == 2:
                try:
                    adj[reg[0]].add(reg[1])
                    adj[reg[1]].add(reg[0])
                except:
                    print("reg error", reg, len(adj))

def dist(a, b):
    dx = a[0] - b[0]
    dy = a[1] - b[1]
    return math.sqrt(dx*dx + dy*dy)

def closest_point_index(plist, p):
    index = 0
    mind = inf
    for i in range(len(plist)):
        d = dist(plist[i], p)
        if d < mind:
            mind = d
            index = i
    return index

def hash(p):
    return int(p[0]) * (1<<32) + int(p[1])

def dijkstra(points, edges, locked, f, t):
    g = defaultdict(list)
    for l in range(len(edges)):
        for r in edges[l]:
            d = dist(points[l], points[r])
            g[l].append((d, r))
            g[r].append((d, l))

    q, seen = [(0,f,())], set()
    while q:
        cost, v1, path = heappop(q)
        if v1 not in seen:
            seen.add(v1)
            path = (v1, path)
            if v1 == t: return (cost, path)

            for c, v2 in g.get(v1, ()):
                if v2 not in seen:
                    heappush(q, (cost+c, v2, path))

    return inf


file = open("submitInput.txt")
testcases = int(file.readline())
for tc in range(1, testcases+1):
    n = int(file.readline())
    points = [None for i in range(n)]
    for i in range(n):
        points[i] = parsePoint(file.readline())
    radius = parseFrac(file.readline())
    start_p = parsePoint(file.readline())
    end_p = parsePoint(file.readline())

    vor = Voronoi(points)

    adj = [set() for i in range(len(vor.vertices))]

    locked = set()

    for i in range(len(vor.ridge_points)):
        ridge = vor.ridge_points[i]
        d = dist(points[ridge[0]], points[ridge[1]])
        if debug:
            print(ridge[0], ridge[1], d, radius)
        if d < 2*radius:
            locked.add(i)

    if debug: 
        print("locked", locked)

    gen_graph(vor, adj, locked)
    start = closest_point_index(vor.vertices, start_p)
    end = closest_point_index(vor.vertices, end_p)

    res = dijkstra(vor.vertices, adj, locked, start, end)
    if res == inf:
        print("Case #{tc}: IMPOSSIBLE".format(tc=tc))
    else:
        print("Case #{tc}: {r:.3f}".format(tc=tc, r=res[0]))

    if debug:
        print("vertices", vor.vertices)
        print("ridge vertices", vor.ridge_vertices)
        print("ridge points", vor.ridge_points)
        print("adj", adj)
        print()

        voronoi_plot_2d(vor)
        plt.plot(start_p[0], start_p[1], "ro")
        plt.plot(end_p[0], end_p[1], "ro")
        for i in range(len(vor.vertices)):
            p = vor.vertices[i]
            plt.text(p[0]*1.01, p[1]*1.01, "v"+str(i), fontsize=12)
        for i in range(len(points)):
            p = points[i]
            plt.text(p[0]*1.01, p[1]*1.01, "p"+str(i), fontsize=12)

        plt.show()