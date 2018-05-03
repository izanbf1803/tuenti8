c = int(input())
for case in range(1, c+1):
    n, m = map(int, input().split())
    print("Case #{case}: {res}".format(case=case, res=(n-1)*(m-1)))