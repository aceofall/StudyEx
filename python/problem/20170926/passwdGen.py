#/bin/env python
# -*- coding: utf-8 -*-
"""
Password generator
"""
import random
from string import ascii_letters

ramdomNum = [r for r in '0123456789']
ramdomAlpha = [r for r in list(ascii_letters)]
randomSpec = [r for r in '!@#$%^&*']
ramdomLen = [ r for r in '123456789']

def main():
    minLen = int(input("What's the minimum length? "))
    specLen = int(input("How many special characters? "))
    numLen = int(input("How many numbers? "))

    random.shuffle(ramdomLen)
    random.shuffle(randomSpec)
    random.shuffle(ramdomNum)
    random.shuffle(ramdomAlpha)

    addLen = int(random.choice(ramdomLen))
    alphaLen = minLen - specLen - numLen + addLen

    shufflePass = []
    for d in range(specLen):
        shufflePass.append(random.choice(randomSpec))
    for d in range(numLen):
        shufflePass.append(random.choice(ramdomLen))
    for d in range(alphaLen):
        shufflePass.append(random.choice(ramdomAlpha))

    random.shuffle(shufflePass)
    passwd = ''.join(shufflePass)
    print("Passwd: " + passwd)

if __name__ == '__main__':
    main()
