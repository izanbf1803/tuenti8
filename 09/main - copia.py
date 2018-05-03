from PIL import Image, ImageChops
from random import shuffle
import sys

im = Image.open("submit.png")
inp = im.convert("RGB")
w, h = inp.size
out = Image.new("RGB", (w, h))
out.paste(im)
a = inp.load()
b = out.load()

# for i in range(w):
#     for j in range(h):
#         b[i,j]
# out.save("out.png")
# sys.exit(0)
# for i in range(1, 100):
#     for j in range(1, 100):
#         b[i,j] = (i,j,i+j)
# print(ImageChops.difference(inp, out))

def memoize(f):
    """ Memoization decorator for functions taking one or more arguments. """
    class memodict(dict):
        def __init__(self, f):
            self.f = f
        def __call__(self, *args):
            return self[args]
        def __missing__(self, key):
            ret = self[key] = self.f(*key)
            return ret
    return memodict(f)

@memoize
def error(k, l):
    d = 0
    for i in range(h):
        d += abs(a[k,i][0]-a[l,i][0]) + abs(a[k,i][1]-a[l,i][1]) + abs(a[k,i][2]-a[l,i][2])
    return d**2

@memoize
def heuristic(y, k):
    p = a[k,y]
    h = 256**2 * p[2]
    h += 256 * p[0]
    h += p[1]
    return h

def copy(bcol, acol):
    img1 = im.crop((acol, 0, acol+1, h))
    out.paste(img1, (bcol, 0))

def swap(x1, x2, size):
    img1 = im.crop((x1, 0, x1+size, h))
    img2 = im.crop((x2, 0, x2+size, h))
    out.paste(img1, (x2, 0))
    out.paste(img2, (x1, 0))

# cols = [i for i in range(1, w)]
# fcols = [0]
# while len(cols) > 0:
#     maxe = -10**12
#     index = -1
#     lastcol = fcols[-1]
#     for i in range(len(cols)):
#         col = cols[i]
#         e = error(col, lastcol)
#         if e > maxe:
#             index = i
#             maxe = e
#     fcols.append(cols[index])
#     cols.pop(index)
#     if len(fcols)%10 == 0: print(len(fcols))
# print(fcols)

for y in range(0, h, 100):
    cols = [i for i in range(w)]
    cols = sorted(cols, key=lambda k: heuristic(y, k))
    for i in range(w):
        copy(i, cols[i])

    out.save("o{k}.png".format(k=y))