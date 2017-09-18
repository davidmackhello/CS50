import sys
import cs50
from itertools import cycle

def main():
    if len(sys.argv) != 2:
        print("Usage: vigenere.py <key>")
        sys.exit(1)

    if not sys.argv[1].isalpha():
        print("Key must be an alphabetic string.")
        sys.exit(2)

    key_cycle = cycle([(ord(x) - 65) for x in sys.argv[1].upper()])

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
                          + next(key_cycle)) % 26)), end='')
        else:
            print(c, end='')
    print()

if __name__ == "__main__":
    main()