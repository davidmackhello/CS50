import sys

def history(a, b):
    print("These are history's hardcoded instructions, with args {} and {}".format(a, b))
    
def decorator(f):
    
    def decorated_function(*args, **kwargs):
        if len(sys.argv) == 2:
            return print("Decorated function executed. Sys.argc is 2")
        return f(*args, **kwargs)
    return decorated_function