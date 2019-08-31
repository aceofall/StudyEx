#/bin/env python
# -*- coding: utf-8 -*-
"""
Filtering Record
"""
class Record:
    def __init__(self, first, last, pos, date=""):
        self.first_name = first
        self.last_name = last
        self.position = pos
        self.seperation_date = date

data_set = [
Record("John", "Johnson", "Manager", "2016-12-31"),
Record("Tou", "Xiong", "Software Engineer", "2016-10-15"),
Record("Michaeja", "Michaelson", "District Manager", "2015-12-19"),
Record("Jake", "Jacobson", "Programmer"),
Record("Jacquelyn", "Jackson", "DBA"),
Record("Sally", "Weber", "Web Developer", "2015-12-18") ]

def main():
    search_str = input("Enter a search string: ")
    print("Results:")
    print("{:30}| {:20}| {:25}".format("Name", "Position", "Seperation Date"))
    print("-"*30+"|"+"-"*21+"|"+"-"*26)
    for data in data_set:
        if search_str in data.first_name or search_str in data.last_name:
            print("{:30}| {:20}| {:25}".format(data.first_name + ' ' + data.last_name, data.position, data.seperation_date))

if __name__ == '__main__':
    main()
