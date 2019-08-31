#/bin/env python
# -*- coding: utf-8 -*-
"""
SectionSum
"""

__author__    = "JungHee Son (aceofall@naver.com)"
__copyright__ = "Copyright 2019 JungHee Son. See LISENSE for details."
__date__      = "2019/08/02"
__version__   = "0.0.1"
__usage__     = """Usage: python sectionSum.py """

import sys, math


class SectionSum(object):
    """
    BACKJOON algorithm problem number: 2042 (https://www.acmicpc.net/problem/2042)
    """

    def __init__(self):
        self.input = {"N":0, "operation": []}
        self.nums = []
        self.segtree = []

    def do_operations(self):
        for op in self.input["operation"]:
            if op[0] == 1:
                diff = op[2] - self.nums[op[1]-1]
                self.nums[op[1]-1] = op[2]
                self.change_value(0, 0, self.input["N"]-1, op[1]-1, diff)
                #print(self.nums)
                #print(self.segtree)
            else: # 2
                print(self.calculate_sum(0, 0, self.input["N"]-1, op[1]-1, op[2]-1))

    def change_value(self, index, start, end, changeIndex, diff):
        if changeIndex < start or changeIndex > end:
            return

        self.segtree[index] += diff
        if start != end:
            mid = (start+end)//2
            self.change_value(index*2+1, start, mid, changeIndex, diff)
            self.change_value(index*2+2, mid+1, end, changeIndex, diff)

    def calculate_sum(self, index, start, end, left, right):
        mid = (start+end)//2;
        if left > end or right < start:
            return 0
        elif left <= start and right >= end:
            return self.segtree[index]

        return self.calculate_sum(index*2+1, start, mid, left, right) + \
               self.calculate_sum(index*2+2, mid+1, end, left, right)

    def init_segtree(self, index, start, end):
        mid = (start+end)//2
        if start == end:
            self.segtree[index] = self.nums[start]
        else:
            self.segtree[index] = self.init_segtree(index*2+1,start,mid) + \
                                  self.init_segtree(index*2+2,mid+1,end)
        return self.segtree[index]

    def build_segtree(self):
        treeHeight = math.ceil(math.log(self.input["N"], 2))
        nodeMaxNum = 2 ** (treeHeight+1)
        self.segtree = [0] * nodeMaxNum
        self.init_segtree(0, 0, self.input["N"]-1)
        #print(self.segtree)

    def solve(self, argv=None):
        "SectionSum problem solution"

        self.get_input()
        self.build_segtree()
        self.do_operations()

    def get_input(self):
        self.input["N"], m, k = map(int,sys.stdin.readline().strip().split())
        for _ in range(self.input["N"]):
            self.nums.append(int(sys.stdin.readline().strip()))
        for _ in range(m + k):
            op = [int(x) for x in sys.stdin.readline().strip().split()]
            self.input["operation"].append(op)

if __name__ == '__main__':
    problem = SectionSum()
    problem.solve()
