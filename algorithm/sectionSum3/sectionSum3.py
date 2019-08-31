#/bin/env python
# -*- coding: utf-8 -*-
"""
sectionSum3
"""

__author__    = "JungHee Son (aceofall@naver.com)"
__copyright__ = "Copyright 2019 JungHee Son. See LISENSE for details."
__date__      = "2019/08/11"
__version__   = "0.0.1"
__usage__     = """Usage: python sectionSum3.py """

import sys

class FenwickTree2D(object):

    def __init__(self, size):
        self.size = size
        self.data = [[0]*(size+1) for _ in range(size+1)]

    def update(self, x, y, val):
        diffVal = val - self.sum_matrix(x, y, x, y)
        while x <= self.size:
            indexY = y
            while indexY <= self.size:
                self.data[x][indexY] += diffVal
                indexY += indexY & -indexY
            x += x & -x

    def sum(self, x, y):
        ret = 0
        while x:
            indexY = y
            while indexY:
                ret += self.data[x][indexY]
                indexY -= indexY & -indexY
            x -= (x & -x)
        return ret

    def sum_matrix(self, startX, startY, endX, endY):
        ret = self.sum(endX, endY) - self.sum(startX-1, endY) - \
            self.sum(endX, startY-1) + self.sum(startX-1, startY-1)
        return ret


class sectionSum3(object):
    """
    BACKJOON algorithm problem number: 11658 (https://www.acmicpc.net/problem/11658)
    """

    def __init__(self):
        self.input = {"N":0, "operation": []}
        self.nums = []
        self.fenwickTree = None

    def do_operations(self):
        for op in self.input["operation"]:
            if op[0] == 0: # change value
                self.fenwickTree.update(op[1], op[2], op[3])
            elif op[0] == 1: # make sum
                print(self.fenwickTree.sum_matrix(op[1], op[2], op[3], op[4]))

    def build_tree(self, n):
        self.fenwickTree = FenwickTree2D(n)
        for x in range(1, n+1):
            for y, val in enumerate(sys.stdin.readline().strip().split(), 1):
                self.fenwickTree.update(x, y, int(val))

    def solve(self, argv=None):
        "SectionSum3 problem solution"

        self.get_input()
        self.do_operations()

    def get_input(self):
        self.input["N"], m = map(int,sys.stdin.readline().strip().split())
        self.build_tree(self.input["N"])
        for _ in range(m):
            op = [int(x) for x in sys.stdin.readline().strip().split()]
            self.input["operation"].append(op)

if __name__ == '__main__':
    problem = sectionSum3()
    problem.solve()
