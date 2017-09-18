import cs50

def main():
    # get int between 0 and 23 from user
    while True:
        print("Height: ", end="")
        height = cs50.get_int()
        if -1 < height < 24:
            break
    
    # calculate width of pyramid base
    base_width = height + 1
    
    # assign starting width of top row, then increment until base width reached
    for this_row in range(2, base_width + 1):
    
        # print pyramid row, right justified
        print((this_row * '#').rjust(base_width))
        
if __name__ == "__main__":
    main()