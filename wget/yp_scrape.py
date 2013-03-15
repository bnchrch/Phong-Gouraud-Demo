#!/usr/bin/python
import re
import sys
import optparse

def main():
    p = optparse.OptionParser()
    options, arguments = p.parse_args()

    """
    fp = open (filename, 'r')
    
    if not fp:
        print "didnt work"
        exit()
    for data in fp:
    """
    
    filename = arguments[0]
    fp = open (filename, 'r')
   
    
    for data in fp:
        matchobj=re.search(r"<div class=.busCardLeftLinks.>.*href=..gourl.(.*).>$",data)
        if matchobj:
            print matchobj.group(1)
    
        matchobj=re.search(r"busPhoneNumber.>(.*)</span></a>",data)
        if matchobj:
            print matchobj.group(1)
        
        matchobj=re.search(r"<title>(.*)\s-\s{2}(.*)</title>",data)
        if matchobj:
            print matchobj.group(1)
            print matchobj.group(2)
        
        matchobj=re.search(r"<tr><td>(\w{6,9}).*nbsp;(\d*.\d*\s\w{2}).*nbsp;(.\s\d*.\d*\s\w{2})",data)
        if matchobj:
            print matchobj.group(1), matchobj.group(2), matchobj.group(3)
            
if __name__ == "__main__":
    main()
