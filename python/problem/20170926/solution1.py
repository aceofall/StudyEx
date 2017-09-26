#/bin/env python
# -*- coding: utf-8 -*-
"""
Reference: http://interactivepython.org/runestone/static/everyday/2013/01/3_password.html
"""
import random

alphabet = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
pw_length = 8
mypw = ""

for i in range(pw_length):
    next_index = random.randrange(len(alphabet))
    mypw = mypw + alphabet[next_index]

    print(mypw)
