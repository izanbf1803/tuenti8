def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

def egcd(a, b): # extended gcd
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)
        return (g, x - (b // a) * y, y)

def modinv(a, m): # modular inverse
    g, x, y = egcd(a, m)
    if g != 1: return -1 # Error
    return x % m

def lcm(arr, n):
    ans = arr[0]
    for i in range(1, n):
        ans = (ans * arr[i]) // gcd(ans, arr[i])
    return ans

def crt(a, m, n):
    a1 = a[0]
    m1 = m[0]

    for i in range(1, n):
        a2 = a[i]
        m2 = m[i]

        g = gcd(m1, m2)

        if a1 % g != a2 % g:
            return -1

        _, p, q = egcd(m1//g, m2//g)

        mod_ = m1 // g * m2

        x = (a1*(m2//g)*q + a2*(m1//g)*p) % mod_

        a1 = x
        if a1 < 0:
            a1 += mod_
        m1 = mod_

    return a1


c = int(input())
for case in range(1, c+1):
    d = int(input())
    a = []
    m = []
    valid = True

    for i in range(d):
        p, t = map(int, input().split())
        # Chinese remainder theorem variables:
        m.append(p)
        a.append((-t-i)%p)

    n = len(a)

    r = crt(a, m, n)
    if r == -1:
        r = "NEVER"
        
    print("Case #{case}: {r}".format(case=case, r=r))