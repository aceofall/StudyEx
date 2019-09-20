#/bin/env python
# -*- coding: utf-8 -*-
"""
freshman
"""

__author__    = "JungHee Son (aceofall@naver.com)"
__copyright__ = "Copyright 2019 JungHee Son. See LISENSE for details."
__date__      = "2019/09/20"
__version__   = "0.0.1"
__usage__     = """Usage: python freshman.py """

import sys

class Freshman(object):
    """
    BACKJOON algorithm problem number: 5557 (https://www.acmicpc.net/problem/5557)
    """

    def __init__(self):
        self.is_called = [[-1 for x in range(100)] for y in range(21)]

    def find_formula(self, index, sum):
        if self.n-1 == index:
            return 1 if sum == self.nums[index] else 0

        if self.is_called[index][sum] != -1:
            return self.is_called[index][sum]

        self.is_called[index][sum] = 0

        if sum+self.nums[index] <= 20:
            self.is_called[index][sum] += self.find_formula(index+1, sum+self.nums[index])
        if sum-self.nums[index] >= 0:
            self.is_called[index][sum] += self.find_formula(index+1, sum-self.nums[index])

        return self.is_called[index][sum]

    def solve(self, argv=None):
        "Freshman problem solution"

        self.get_input()
        self.is_called[0][self.nums[0]] = 0
        print(self.find_formula(1, self.nums[0]))

    def get_input(self):
        self.n = int(sys.stdin.readline().strip())
        self.nums = [int(x) for x in sys.stdin.readline().strip().split()]

if __name__ == '__main__':
    problem = Freshman()
    problem.solve()

'''
class Freshman(object):
    """
    BACKJOON algorithm problem number: 5557 (https://www.acmicpc.net/problem/5557)
    """

    def __init__(self):
        self.nums = []
        self.formula_num = 0

    def find_formula(self, nums, sum):
        if len(nums) == 0:
            return

        if len(nums) == 1 and sum == nums[0]:
            self.formula_num += 1

        if sum+nums[0] <= 20:
            self.find_formula(nums[1:], sum+nums[0])
        if sum-nums[0] >= 0:
            self.find_formula(nums[1:], sum-nums[0])

    def solve(self, argv=None):
        "Freshman problem solution"

        self.get_input()
        self.find_formula(self.nums, 0)
        print(self.formula_num)

    def get_input(self):
        n = int(sys.stdin.readline().strip())
        self.nums = [int(x) for x in sys.stdin.readline().strip().split()]
        assert len(self.nums) == n

if __name__ == '__main__':
    problem = Freshman()
    problem.solve()

input();s,*A,e=map(int,input().split());d={s:1}
for a in A:
 f={}
 for k in range(21):v=d.get(k,0);f[k+a]=v+f.get(k+a,0);f[k-a]=v+f.get(k-a,0)
 d=f
print(d.get(e,0))
'''
