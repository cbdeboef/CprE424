"""
Demo to Show the Uses of Python Lists
Caleb DeBoef
8/30/22
"""

L = [1]
print(L)

L.append([0, 0, 0])
print(L)

L[1] = 'A'
appendedList = L.copy()
print(appendedList)

print('Number of As: ',L.count('A'))
L.pop(0)
x = ['X', 'Y', 'Z']
L.extend(x)
L.index('X')
extendedList = L.copy()
print(extendedList)

L.reverse()
reversedList = L.copy()
print(reversedList)

L.sort()
sortedList = L.copy()
print(sortedList)

L.clear()
clearedList = L.copy()
print(clearedList)
