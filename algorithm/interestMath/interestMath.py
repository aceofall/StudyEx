#/bin/env python
# -*- coding: utf-8 -*-
"""
Enjoy Party Problem
"""

__author__ = "JungHee Son (aceofall\x40naver\x2Ecom)"
__copyright__ = "Copyright 2017 JungHee Son. See LISENSE for details."
__date__ = "2017/09/01"
__version__ = "0.0.1"
__usage__ = """Usage: python interestMath.py [input_file]"""

import os, sys, getopt, logging, inspect

DefaultFile = "input.txt"
InputParams = {'base':[]}
OutputData = {}

class InterestMath:
    "Top coder algorithmn problem number 4 class"
    def __init__ (self):

        self.logger = logging.getLogger('interestMath')
        fileHandler = logging.FileHandler('./interestMath.log')
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

    def convert(self, n, base):
        T = "0123456789ABCDEF"
        q, r = divmod(n, base)
        if q == 0:
            return T[r]
        else:
            return convert(q, base) + T[r]


    def solve(self, argv=None):
        "Solve InterestMath problem"

        if argv is None:
            argv = sys.argv

        if len(argv) == 2:
            argInputFile = argv[1]
        else:
            argInputFile = DefaultFile

        self.debugLog('argFile: ' + argInputFile)
        self.parseInput(argInputFile)

        # Get math system
        mathSystem = int(InputParams['base'])

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
            base = 10
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
                    self.debugLog(tempStr)
                    InputParams[param] = tempStr

if __name__ == '__main__':
    problem = InterestMath()
    problem.solve()
