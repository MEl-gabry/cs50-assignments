import math
number = input("Number: ")
total = 0
times = 0
for digit_str in reversed(number):
    digit = int(digit_str)
    if times % 2 == 0:
        total += int(digit)
    else:
        digit *= 2
        if digit >= 10:
            total += digit % 10
            total += math.floor(digit / 10)
        else:
            total += digit  
    times += 1  
if total % 10 != 0:
    print("INVALID")
elif 51 <= int((number[0] + number[1])) <= 55:
        print("MASTERCARD")
elif int(number[0]) == 4:
    print("VISA")
else:
    print("AMEX") 
