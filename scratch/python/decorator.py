import sys

def backup():
    print("I'm backup")

def decorator(f):
    if len(sys.argv) == 2:
        return backup
    else:
        return f

def some_func():
    print("I'm somefunc baseline")