#/bin/env python
# -*- coding: utf-8 -*-
"""
Reference: http://interactivepython.org/runestone/static/everyday/2013/01/3_password.html
"""
import random

alphabet = "abcdefghijklmnopqrstuvwxyz"
upperalphabet = alphabet.upper()
pw_len = 8
pwlist = []

for i in range(pw_len//3):
    pwlist.append(alphabet[random.randrange(len(alphabet))])
    pwlist.append(upperalphabet[random.randrange(len(upperalphabet))])
    pwlist.append(str(random.randrange(10)))
    for i in range(pw_len-len(pwlist)):
        pwlist.append(alphabet[random.randrange(len(alphabet))])
        random.shuffle(pwlist)
        pwstring = "".join(pwlist)
        print(pwstring)
