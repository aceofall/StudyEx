#/bin/env python
# -*- coding: utf-8 -*-
"""
Virus Problem
"""

__author__ = "JungHee Son (aceofall\x40naver\x2Ecom)"
__copyright__ = "Copyright 20179JungHee Son. See LISENSE for details."
__date__ = "2019/05/11"
__version__ = "0.0.1"
__usage__ = """Usage: python virus.py """
#__usage__ = """Usage: python virus.py [input_file]"""

import os, sys, getopt, logging, inspect

DefaultFile = "input.txt"
InputParams = {'com_nums':[], 'connection_nums': [], 'connection_pair': []}
OutputData = {}
CONNECTED = 1
UNCONNECTED = 0
INFECTED = 1
UNINFECTED = 0


class Virus(object):
    """
    BACKJOON algorithm problem number: 2606 (https://www.acmicpc.net/problem/2606).
    """

    def __init__ (self):

        self.logger = logging.getLogger('securityLogger')
        fileHandler = logging.FileHandler('./security.log')
        streamHandler = logging.StreamHandler()

        formatter = logging.Formatter('[%(levelname)s|%(filename)s:%(lineno)s] %(asctime)s > %(message)s')
        fileHandler.setFormatter(formatter)
        streamHandler.setFormatter(formatter)

        self.logger.addHandler(fileHandler)
        self.logger.addHandler(streamHandler)

        #self.logger.setLevel(logging.DEBUG)
        self.logger.setLevel(logging.INFO)

        self.connection_map = []
        self.infection_status = []
        self.infection_count = 0
        return

    def debugLog(self, msg):

        callerframerecord = inspect.stack()[1]    # 0 represents this line
                                                  # 1 represents line at caller
        frame = callerframerecord[0]
        info = inspect.getframeinfo(frame)
        #print info.filename                       # __FILE__     -> Test.py
        #print info.function                       # __FUNCTION__ -> Main
        #print info.lineno                         # __LINE__     -> 13
        if isinstance(msg, str) is False:
            msg = str(msg)

        self.logger.debug('['+ info.filename + '][' + info.function + '][' + str(info.lineno) + ']: ' + msg)
        return

    def localPrint(self, msg):
        self.logger.info(msg)
        return



    def solve(self, argv=None):
        "Virus problem solution"

        if argv is None:
            argv = sys.argv

        if len(argv) == 2:
            argInputFile = argv[1]
        else:
            argInputFile = DefaultFile

        self.debugLog('argFile: ' + argInputFile)
        self.parseInput(argInputFile)
        #self.getInput()
        print(InputParams)

        for x in range(InputParams['com_nums']) :
            self.connection_map.append([UNCONNECTED] * InputParams['com_nums'])

        self.infection_status.append([UNINFECTED] * InputParams['com_nums'])

        # Set map connection info
        for x, y in InputParams['connection_pair']:
            self.debugLog("x: %d, y: %d" % (x,y))
            self.connection_map[x-1][y-1] = CONNECTED
            self.connection_map[y-1][x-1] = CONNECTED

        self.printMap(self.connection_map)
        self.printMap(self.infection_status)
        self.checkVirus(1)
        self.printMap(self.infection_status)

        print("Infection Count: %d" % self.infection_count)


    def checkVirus(self, startPoint=1):
        self.debugLog("Called Point: %d" % startPoint)

        for checkPoint in range(startPoint, InputParams['com_nums']):
            if self.connection_map[startPoint-1][checkPoint] == CONNECTED:
                self.debugLog("startPoint: %d, checkPoint: %d" % (startPoint, checkPoint+1))

                if self.infection_status[0][checkPoint] == UNINFECTED:
                    self.infection_status[0][checkPoint] = INFECTED
                    self.checkVirus(checkPoint+1)
                    self.infection_count += 1


    def printMap(self, map):
        for row in map:
            self.debugLog(row)


    def getInput(self):
        """
        Parse input stdio
         ex) input data
         7
         6
         1 2
         2 3
         1 5
         5 2
         5 6
         4 7
        """

        InputParams['com_nums'] = int(input('computer numbers?: '))
        InputParams['connection_nums'] = int(input('connection numbers?: '))
        pairs = []
        for i, _ in enumerate(range(InputParams['connection_nums']), 1):
            connection = []
            connection.append([ int(x) for x in (input("%dth connextion (ex: 1 2): " % i).strip().split(' ')) ])
            pairs.append(connection)

        InputParams['connection_pair'] = pairs


    def parseInput(self, inputFile):
        """
        Parse input file data
         ex) input data
         7
         6
         1 2
         2 3
         1 5
         5 2
         5 6
         4 7
        """
        inFile = open(inputFile,'r')
        readLines = inFile.readlines()
        inFile.close()

        InputParams['com_nums'] = int(readLines[0])
        InputParams['connection_nums'] = int(readLines[1])
        pairs = []
        for line in readLines[2:]:
            self.debugLog(line.rstrip())
            connection = [ int(x) for x in line.strip().split(' ') ]
            pairs.append(connection)

        InputParams['connection_pair'] = pairs

if __name__ == '__main__':
    problem = Virus()
    problem.solve()
