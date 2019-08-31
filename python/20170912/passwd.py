#/bin/env python
# -*- coding: utf-8 -*-
"""
Password validator
"""
import re

pw_rule = [
re.compile("[\S]{8,}"),
#re.compile("[0-9^a-zA-Z]{1,8}"),
re.compile("[\w]{9,}"),
re.compile("\w{,8}"),
re.compile("^source_.+ := (.*)"),
re.compile("^ *([a-zA-Z0-9_\-/]+\.[chCH]) *")
]
pw_msg = { 0:"very weak", 1:"weak", 2:"strong", 3:"very strong"}

def main():

    while 1:
        pw = input("The password ")
        if  pw == '':
            print("Exit...")
            break;

        case = passwordVaildator(pw)
        print ("\b is a " + pw_msg[case] + " password.")

def passwordVaildator(password):
    case = 0
    length = len(password)
    en_char = pw_rule[0].match(password)
    print(en_char)
    if length > 8 and en_char:
        return 3

#    password.
    return case

if __name__ == '__main__':
    main()
