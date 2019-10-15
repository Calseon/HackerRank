if __name__ == '__main__':
    x = 3
    y = 3
    z = 3
    n = 6

    print( [ [ i, j, k] 
        for i in range( x + 1) 
        for j in range( y + 1) 
        for k in range( z + 1)
        if ( ( i * j * k) != 9 )])


    print([x for x in 'shark'])
    print([y for y in "someword"])
