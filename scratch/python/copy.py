import cs50

print("s: ", end = "")
s = cs50.get_string()
if s == None:
    exit(1)

s = s.capitalize()

print("new s: {}".format(s))

exit(0)