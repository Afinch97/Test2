def q8(): 
    a = 1
    print("Starting a = " + str(a))
    def sub1():
            a = 8
            b = 2
            print(" Sub 1: a = " + str(a) + ", b = " + str(b))
            def sub2():
                b = 24
                c = 3
                print(" Sub 2: a = " + str(a) + ", b = " + str(b) + ", c = " + str(c))
                def sub3():
                    c = 81
                    d = 4
                    print(" Sub 3: a = " + str(a) + ", b = " + str(b) + ", c = " + str(c) + ", d = " + str(d))
                sub3()
            sub2()
    sub1()
q8()