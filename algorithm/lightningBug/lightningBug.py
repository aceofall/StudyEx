#/bin/env python
# -*- coding: utf-8 -*-
"""
LightningBug Problem
"""

__author__    = "JungHee Son (aceofall@naver.com)"
__copyright__ = "Copyright 2019 JungHee Son. See LISENSE for details."
__date__      = "2019/05/24"
__version__   = "0.0.1"
__usage__     = """Usage: python lightningBug.py """

BREAK_WALL_MIN_COUNT = 200000

class LightingBug(object):
    """
   BACKJOON algorithm problem number: 3020 (https://www.acmicpc.net/problem/3020)
   """

    def __init__ (self):
        self.inputParams = { "cave_width": 0, "cave_height": 0, "stone_bottom": [], "stone_up": []}
        self.results = ()

    def solve(self, argv=None):
        "LightingBug problem solution"

        self.get_input()
        self.break_walls()
        print("%d %d" % self.results)

    def break_walls(self):
        minData = BREAK_WALL_MIN_COUNT
        minDataCount = 0
        for bugLine in range(self.inputParams['cave_height']):
            breakCount = 0
            for stone in range(self.inputParams['cave_width']//2):
                if self.inputParams['stone_bottom'][stone] > bugLine:
                    breakCount += 1
                if self.inputParams['cave_height'] - self.inputParams['stone_up'][stone] <= bugLine:
                    breakCount += 1

            if minData > breakCount:
                minData = breakCount
                minDataCount = 0

            if breakCount == minData:
                minDataCount += 1

        self.results = (minData, minDataCount)

    def get_input(self):
        cave_length = [ int(x) for x in input().strip().split(' ') ]
        self.inputParams['cave_width'] = cave_length[0]
        self.inputParams['cave_height'] = cave_length[1]

        for idx in range(1, self.inputParams['cave_width']+1):
            if idx % 2 == 1:
                self.inputParams["stone_bottom"].append(int(input().strip()))
            elif idx % 2 == 0:
                self.inputParams["stone_up"].append(int(input().strip()))

if __name__ == '__main__':
    problem = LightingBug()
    problem.solve()
