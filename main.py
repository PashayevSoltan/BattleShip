import os
from controller import *
from model import *



def start():
    global Dyp
    global Fails
    display()
    choice = input("Choice:")
    if choice=="1":
        number = input("Number:")
        getNumberByValue(Dyp,number)
    elif choice=="2":
        print("car propety input")
        key = input("car number:")
        marka = input("marka:")
        model = input("model:")
        year = int(input("year:"))
        fails = []
        car = {"Marka":marka,"Model":model,"Year":year,"Fails":fails}
        Dyp=addCar(Dyp,key,car)
    elif choice=="3":
        number = input("Number:")
        getNumberByFails(Dyp,number)
    elif choice=="4":
        number = input("Number:")
        Dyp = deleteCarByNumber(Dyp,number)
    elif choice=="5":
        showDyp(Dyp)
    else:
        print("Incorrect choice!!!")
    
    next = input("For continue press ebter.")
    os.system("cls")
    start()




start()