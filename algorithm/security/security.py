#/bin/env python
# -*- coding: utf-8 -*-
"""
Security Problem
"""

__author__ = "JungHee Son (aceofall\x40naver\x2Ecom)"
__copyright__ = "Copyright 2017 JungHee Son. See LISENSE for details."
__date__ = "2017/08/21"
__version__ = "0.0.1"
__usage__ = """Usage: python security.py [input_file]"""

import os, sys, getopt, logging, inspect

DefaultFile = "input.txt"
InputParams = {'numbers':[]}
OutputData = {}

class Security:
    "Top coder algorithmn problem number 3 class"
    def __init__ (self):

        self.logger = logging.getLogger('securityLogger')
        fileHandler = logging.FileHandler('./security.log')
        streamHandler = logging.StreamHandler()

        formatter = logging.Formatter('[%(levelname)s|%(filename)s:%(lineno)s] %(asctime)s > %(message)s')
        fileHandler.setFormatter(formatter)
        streamHandler.setFormatter(formatter)

        self.logger.addHandler(fileHandler)
        self.logger.addHandler(streamHandler)

        self.logger.setLevel(logging.DEBUG)
        #self.logger.setLevel(logging.INFO)
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
        self.logger.info(msg)
        return



    def solve(self, argv=None):
        "Solve enjoyParty problem"

        if argv is None:
            argv = sys.argv

        if len(argv) == 2:
            argInputFile = argv[1]
        else:
            argInputFile = DefaultFile

        self.debugLog('argFile: ' + argInputFile)
        self.parseInput(argInputFile)

        # Get numbers data
        limitNum = pow(2,62)
        multiNumbers = [int(x) for x in InputParams['numbers']]
        multiNumbers.sort()

        # Calculate numbers
        for min in multiNumbers:
            tempNumbers = multiNumbers
            tempNumbers.remove(min)

            totalMultiSum = 1
            for multi in tempNumbers:
                totalMultiSum *= multi

            totalMultiSum *= min + 1
            self.debugLog(str(totalMultiSum))
            self.debugLog(str(limitNum))
            if totalMultiSum < limitNum:
                break

        self.localPrint('## Calculate Returns: ' + str(totalMultiSum))
        return

    def parseInput(self, inputFile):
        """ Parse input file data
            ex) input data
            numbers = {1000, 999, 998, 997, 996, 995}
        """
        inFile = open(inputFile,'r')
        readLines = inFile.readlines()
        inFile.close()

        for line in readLines:
            self.debugLog(line.rstrip())
            for param in InputParams.keys():
                if line.lower().find(param.lower()) != -1:
                    tempStr = ''.join(line.split('=')[1])
                    tempStr = tempStr.strip()
                    tempStr = tempStr.replace('{', '')
                    tempStr = tempStr.replace('}', '')
                    self.debugLog(tempStr)
                    InputParams[param] = tempStr.split(', ')

if __name__ == '__main__':
    problem = Security()
    problem.solve()
