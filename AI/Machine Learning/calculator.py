print("Enter two numbers")
a = int(input("Input number a:"))
b = int(input ("Input number b:"))

choice = int(input("What operation to perform, 1: +, 2: -, 3: *, 4: /"))

if choice == 1:
    sum = a+b
    print (sum)

elif choice == 2:
    diff = a-b
    print(diff)

elif choice == 3:
    mult= a*b
    print(mult)

else:
    div=a/b
    print(div)





