def main():
    cough(4)
    sneeze(4)

def cough(n):
    say("cough", n)
    
def sneeze(n):
    say("achoo!", n)
    
def say(string, n):
    for i in range(n):
        print(string)
    
if __name__ == "__main__":
    main()