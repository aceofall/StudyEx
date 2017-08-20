#/bin/env python
# -*- coding: utf-8 -*-
"""
Enjoy Party Problem
"""

__author__ = "JungHee Son (aceofall\x40naver\x2Ecom)"
__copyright__ = "Copyright 2017 JungHee Son. See LISENSE for details."
__date__ = "2017/08/14"
__version__ = "0.0.1"
__usage__ = """Usage: python enjoyParty.py [input_file]"""

import os, sys, getopt, logging, inspect

DefaultFile = "input.txt"
InputParams = {'first':[], 'second':[]}
OutputData = {}

class EnjoyParty:
    "Top coder algorithmn problem number 2 class"
    def __init__ (self):

        self.logger = logging.getLogger('enjoyLogger')
        fileHandler = logging.FileHandler('./enjoyParty.log')
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

        # Count Friends number
        friendsNum = len(InputParams['first'])

        # Find common favorites item
        for friend in range(friendsNum):
            like1 = InputParams.get('first')[friend]
            like2 = InputParams.get('second')[friend]
            likeKey = list(set([like1.strip(), like2.strip()]))

            for key in likeKey:
                likeItemCount = 0
                if key in OutputData:
                    likeItemCount = OutputData[key]
                    likeItemCount += 1
                    OutputData[key] = likeItemCount
                else:
                    likeItemCount = 1
                    OutputData[key] = likeItemCount

        compareCount = 0
        for likeItem in OutputData.keys():
            self.debugLog(likeItem + ' : ' + str(OutputData[likeItem]))
            if OutputData[likeItem] > compareCount:
                compareCount = OutputData[likeItem]
                highestLikeItem = likeItem

        self.localPrint('## Most favorite Item: ' + highestLikeItem + " => count: " + str(compareCount))

        return

    def parseInput(self, inputFile):
        """ Parse input file data
            ex) input data
            first = {'fishing', 'gardening', 'swimming', 'fishing'}
            second = {'hunting', 'fishing', 'fishing', 'biting'}
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
                    tempStr = tempStr.replace('\'', '')
                    self.debugLog(tempStr)
                    InputParams[param] = tempStr.split(',')

if __name__ == '__main__':
    problem = EnjoyParty()
    problem.solve()
