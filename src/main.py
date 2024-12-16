
def max():
    m, n = input("请输入两个数: ").split(' ')
    print(m if int(m) > int(n) else n)

max()