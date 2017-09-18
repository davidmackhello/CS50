import cs50
import sys

if len(sys.argv) != 2:
    print("Missing command-line argument buddy!")
    exit(1)
    
print("hello, {}".format(sys.argv[1]))
exit(0)