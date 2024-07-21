def getNumberByValue(dyp,number):
    if number in dyp:
        for i in dyp:
            if i==number:
                for k in dyp[i]:
                    print(k,end=":")
                    print(dyp[i][k])

def addCar(dyp,number,car):
    dyp[number] = car
    return dyp

def getNumberByFails(dyp,number):
    for i in dyp:
        if i==number:
            for k in dyp[i]:
                if k=="Fails":
                    for d in dyp[i][k]:
                        print(d)

def deleteCarByNumber(dyp,number):
    
    if number in dyp:
        dyp.pop(number)
    return dyp


def showDyp(dyp):
    for i in dyp:
        print(i)
        for k in dyp[i]:
            print(k,end=":")
            print(dyp[i][k])
        print()
    



def display():
    print("!!!!  D Y P  !!!!")
    print("1.Check car by number")
    print("2.Add car system")
    print("3.Check car fails by number")
    print("4.Delete car system by number")
    print("5.Show Dyp")
