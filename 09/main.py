from PIL import Image
from random import shuffle
import sys
from scipy.misc import imread
from scipy.linalg import norm
from scipy import sum, average
import numpy as np

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

__inp = Image.open("test.png").convert("RGB")
__w, __h = __inp.size

def copy(__im, __out, bcol, acol, __h):
    __img1 = __im.crop((acol, 0, acol+1, __h))
    __out.paste(__img1, (bcol, 0))

def save_with_cols(__cols, __id):
    __out = Image.new("RGB", (__w, __h))
    __out.paste(__inp)
    for i in range(__w):
        copy(__inp, __out, i, __cols[i], __h)
    __out.save("o{id}.png".format(id=__id))


pix = np.array(__inp)
w = __w

def mean_error(cola, colb):
    return (pix[:,cola] - pix[:,colb]).mean()**2

cols = [i for i in range(1, w)]
fcols = [0]
while len(cols) > 0:
    col = fcols[-1]
    mine = 10**8
    index = -1
    for i in range(len(cols)):
        if cols[i] != col:
            e = mean_error(col, cols[i])
            if e < mine:
                mine = e
                index = i
    fcols.append(index)
    cols.pop(index)

print(fcols)
save_with_cols(fcols, 0)

# def to_grayscale(arr):
#     "If arr is a color image (3D array), convert it to grayscale (2D array)."
#     if len(arr.shape) == 3:
#         return average(arr, -1)  # average over the last axis (color channels)
#     else:
#         return arr

# def normalize(arr):
#     rng = arr.max()-arr.min()
#     amin = arr.min()
#     return (arr-amin)*255/rng

# def compare_images(img1, img2):
#     # normalize to compensate for exposure difference, this may be unnecessary
#     # consider disabling it
#     img1 = normalize(img1)
#     img2 = normalize(img2)
#     # calculate the difference and its norms
#     diff = img1 - img2  # elementwise for scipy arrays
#     m_norm = sum(abs(diff))  # Manhattan norm
#     z_norm = norm(diff.ravel(), 0)  # Zero norm
#     return (m_norm, z_norm)

# def main():
#     file1, file2 = "test.png", "y700.png"
#     # read images as 2D arrays (convert to grayscale for simplicity)
#     img1 = to_grayscale(imread(file1).astype(float))
#     img2 = to_grayscale(imread(file2).astype(float))
#     # compare
#     n_m, n_0 = compare_images(img1, img2)
#     print ("Manhattan norm:", n_m, "/ per pixel:", n_m/img1.size)
#     print ("Zero norm:", n_0, "/ per pixel:", n_0*1.0/img1.size)

# main()