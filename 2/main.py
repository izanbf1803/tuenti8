# Always solve like this:
# n = length of string - 1
# maxv = n * base^n + (n-1) * base^(n-1) + ... + 1 * base + 0
# minv = 1 * base^n + 0 * base^(n-1) + 2 * base(n-2) + ... + n
# But i use powers array to precompute powers

t = int(input())
for case in range(1, t+1):
    s = input()
    minv, maxv = 0, 0
    base = len(s)
    powers = [0 for i in range(base)]
    powers[0] = 1
    for i in range(1, base):
        powers[i] = base * powers[i-1]
    minv += powers[base-1]
    maxv += (base-1) * powers[base-1] + (base-2) * powers[base-2]
    for i in range(2, base):
        minv += i * powers[base-i-1]
        maxv += (base-i-1) * powers[base-i-1]
    print("Case #{case}: {res}".format(case=case, res=abs(maxv-minv)))