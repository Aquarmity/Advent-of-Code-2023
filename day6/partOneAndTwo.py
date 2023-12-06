import math

c = 0
i = 0
solutions = []
s = 1

while c != -1:
    b = float(input("Time: "))
    c = float(input("Distance (-1 to quit): "))

    b *= -1
    if c != -1:
        ansOne = -1*b / 2
        ansTwo = math.sqrt(abs((b**2 - 4*c))) / 2

        print(ansOne + ansTwo)
        print(ansOne - ansTwo)

        solutions.append(math.floor(ansOne + ansTwo) - math.floor(ansOne - ansTwo))
        print(solutions[i])
        i += 1

for j in solutions:
    s *= j

print (s)