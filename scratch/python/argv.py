import sys

for s in sys.argv:
    for c in s:
        print(c)
    print()

'''
#argv-1.py
for i in range(len(sys.argv)):
    print(sys.argv[i])
'''

'''
#argv-0.py
if len(sys.argv) == 2:
    print("hello, {}".format(sys.argv[1]))
else:
    print("hey")
'''
