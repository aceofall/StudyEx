#/bin/env python
# -*- coding: utf-8 -*-
"""
Kiwi Juice Problem
"""

__author__ = "JungHee Son (aceofall\x40naver\x2Ecom)"
__copyright__ = "Copyright 2017 JungHee Son. See LISENSE for details."
__date__ = "2017/08/11"
__version__ = "0.0.1"
__usage__ = """Usage: python kiwi.py [input_file]"""

import os, sys, getopt, re, string, logging, inspect

DefaultFile = "input.txt"
InputParams = {'capacities':[], 'bottles':[], 'fromId':[], 'toId':[]}
OutputData = []

class kiwiJuice:
    "Top coder algorithmn problem number 1 class"
    def __init__ (self):

        self.logger = logging.getLogger('kiwiLogger')
        fileHandler = logging.FileHandler('./kiwi.log')
        streamHandler = logging.StreamHandler()

        formatter = logging.Formatter('[%(levelname)s|%(filename)s:%(lineno)s] %(asctime)s > %(message)s')
        fileHandler.setFormatter(formatter)
        streamHandler.setFormatter(formatter)

        self.logger.addHandler(fileHandler)
        self.logger.addHandler(streamHandler)

        #self.logger.setLevel(logging.DEBUG)
        self.logger.setLevel(logging.INFO)
        return

    def debugLog(self, msg):

        callerframerecord = inspect.stack()[1]    # 0 represents this line
                                                  # 1 represents line at caller
        frame = callerframerecord[0]
        info = inspect.getframeinfo(frame)
        #print info.filename                       # __FILE__     -> Test.py
        #print info.function                       # __FUNCTION__ -> Main
        #print info.lineno                         # __LINE__     -> 13

        self.logger.debug('['+ info.filename + '][' + info.function + '][' + str(info.lineno) + ']: ' + msg)
        return

    def localPrint(self, msg):
        self.logger.info( msg)
        return



    def solve(self, argv=None):
        "Solve kiwiJuice problem"

        if argv is None:
            argv = sys.argv

        if len(argv) == 2:
            argInputFile = argv[1]
        else:
            argInputFile = DefaultFile

        self.debugLog('argFile: ' + argInputFile)
        self.parseInput(argInputFile)

        OutputData = InputParams['bottles']

        # Move bottle water
        moveCount = len(InputParams['fromId'])
        for moveIndex in range(moveCount):
            src = int(InputParams.get('fromId')[moveIndex])
            dest = int(InputParams.get('toId')[moveIndex])
            srcWater = int(InputParams.get('bottles')[src])
            destWater = int(InputParams.get('bottles')[dest])
            destMaxWater = int(InputParams.get('capacities')[dest])

            if destMaxWater >= destWater + srcWater:
                OutputData[dest] = destWater + srcWater
                OutputData[src] = 0
            else:
                OutputData[dest] = destMaxWater
                OutputData[src] = destWater + srcWater - destMaxWater

            InputParams['bottles'] = OutputData
            self.debugLog('current: ' + str(OutputData))

        self.localPrint('Result: ' + str(OutputData))

        return

    def parseInput(self, inputFile):
        """ Parse input file data
            ex) input data
            capacities = 20, 20
            bottles = 5, 8
            fromId = 0
            toId = 1
        """
        inFile = open(inputFile,'r')
        readLines = inFile.readlines()
        inFile.close()

        for line in readLines:
            self.localPrint(line.rstrip())
            for param in InputParams.keys():
                if line.lower().find(param.lower()) != -1:
                    tempStr = ''.join(line.split('=')[1])
                    self.debugLog(tempStr)
                    InputParams[param] = tempStr.split(',')

if __name__ == '__main__':
    problem = kiwiJuice()
    problem.solve()
