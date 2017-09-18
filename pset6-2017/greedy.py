import cs50

def main():
    # get positive float from user
    while True:
        print("How much change is owed ($)?: ")
        user_owed = cs50.get_float()
        if (user_owed >= 0):
            break

    # clean input and determine min number of coins
    cents = int(round(100 * user_owed))
    print(coin_count(cents))

def coin_count(cents):
    """Return minimum number of coins (quarters, dimes, and nickels) given 
    non-negative input in cents
    """
    if cents < 5:
        return cents
    else:
        if 5 <= cents < 10:
            coin = 5
        elif 10 <= cents < 25:
            coin = 10
        elif cents >= 25:
            coin = 25

        return (cents // coin) + coin_count(cents % coin)

if __name__ == "__main__":
    main()