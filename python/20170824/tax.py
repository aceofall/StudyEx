#/bin/env python
# -*- coding: utf-8 -*-
"""
Tax
"""

import os, sys, string

def main():
    product_price = 1.0
    wi_tax = 0.055

    count = raw_input("What is the order amount?: ")
    state = raw_input("What is the state?: ")

    mount = int(count) * product_price

    if 'WI' == state.upper():
        print 'The subtotal is $' + str(mount)
        print 'The tax is $' + str(mount * wi_tax)

    total = mount * wi_tax + mount
    print 'The total is $' + str(total)

if __name__ == '__main__':
    main()
