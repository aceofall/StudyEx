#/bin/env python
# -*- coding: utf-8 -*-
"""
Tax
TargetHearRate = (((220-age) -restingHR) * intensity) + restingHR
"""
import os, sys, string

def main():
    age = raw_input("What is your age?: ")
    restingHR = raw_input("What is the normal heart beat?: ")
    print '\n'

    print 'Resting Pulse: ' + restingHR + ' Age:' + age
    print 'Intensity      | Rate'
    print '---------------|---------'
    for intensity in range(55,100,5):
        targetHearRate = (((220-int(age)) - int(restingHR)) * intensity* 0.01) + int(restingHR)
        print str(intensity) + '%            | ' + str(int(targetHearRate)) + ' bpm'

if __name__ == '__main__':
    main()
