while True:
    try:
        x = int(input("Please enter a number: "))
        print("this is after the error baby")
        break
    except ValueError:
        print("Goodnight!")