import sys
import cs50

def main():
    if len(sys.argv) != 2:
        print("Usage: caesar.py key")
        sys.exit(1)

    try:
        k = int(float(sys.argv[1]))
        if k < 0:
            raise ValueError
    except:
        print("Key must be a non-negative integer")
        sys.exit(2)
        
    print("plaintext: ", end='')
    plaintext = cs50.get_string()
    
    print("ciphertext: ", end='')
    for c in plaintext:
        if c.isalpha():
            if c.islower():
                alpha_shift = 97
            elif c.isupper():
                alpha_shift = 65
            print(chr(alpha_shift 
                      + ((ord(c) 
                          - alpha_shift 
                          + k) % 26)), end='')
        else:
            print(c, end='')
    print()

if __name__ == "__main__":
    main()