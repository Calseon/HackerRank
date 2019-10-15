if __name__ == '__main__':
    n = int(raw_input())
    arr = map(int, raw_input().split())

    maxi = -100;
    runner = -100;

    #O(n)
    for num in arr:
        if num > maxi:
            runner = maxi
            maxi = num
            
        elif num > runner and num < maxi:
            runner = num
        #print("maxi:%d runner:%d"%(maxi, runner))
    print(runner)
