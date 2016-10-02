#!/usr/local/cs/bin/python3

import random, sys, locale, string
from optparse import OptionParser

class comm:
    def __init__(self, arg1, arg2):
        if arg1 == "-" :
            f1 = sys.stdin
        else :
            f1 = open(arg1, 'r')
        if arg2 == "-" :
            f2 = sys.stdin
        else :
            f2 = open(arg2, 'r')
        self.file1 = f1.readlines()
        self.file2 = f2.readlines()
        f1.close()
        f2.close()
    ##########################################################
    def output(self, c1, c2, c3, u):
        output_list = []
        # output_list contain each line following by its column number
        # for example [ "Line0", 0, "Line1", 2, "Line2", 2]
        if u == True:   
            i = 0
            while i < len(self.file1):
                j=0
                while j < len(self.file2):
                    if self.file1[i] == self.file2[j]:
                        output_list.append(self.file1[i])
                        output_list.append(2)
                        self.file2.pop(j)
                        break
                    j+=1
                else:
                    output_list.append(self.file1[i])
                    output_list.append(0)
                i+=1
            for line in self.file2:
                output_list.append(line)
                output_list.append(1)
	
        elif u == False:
            #check if file1 and file2 are in sorted order
            for i in range(len(self.file1)-1):
                if self.file1[i] > self.file1[i+1]:
                    return True
            for i in range(len(self.file2)-1):
                if self.file2[i] > self.file2[i+1]:
                    return False
            
            while len(self.file1) != 0 and len(self.file2) != 0:
                word1 = self.file1[0]
                while len(self.file2) != 0:
                    word2 = self.file2[0]
                    if word1 == word2:
                        output_list.append(word1)
                        output_list.append(2)
                        self.file1.pop(0)
                        self.file2.pop(0)
                        break
                    elif word1 > word2 :
                        output_list.append(word2)
                        output_list.append(1)
                        self.file2.pop(0)
                    else:
                        output_list.append(word1)
                        output_list.append(0)
                        self.file1.pop(0)
                        break
                
            
            for line in self.file1:
                output_list.append(line)
                output_list.append(0)   
            for line in self.file2:
                output_list.append(line)
                output_list.append(1)
                
        
        output_string = ""
        for k in range(len(output_list)):
            if k%2==1:
                indent = self.determine_indent(c1, c2, c3, output_list[k])
                if indent >= 0:
                    output_string += " "*indent*8
                    output_string += output_list[k-1]		
        return output_string
    #############################################################
    def determine_indent(self,c1,c2,c3,col):
        rt = col
        if rt==0:
            if c1==True:
                return -1
        elif rt==1:
            if c2==True:
                return -1
            elif c1==True:
                return 0
        elif rt==2:
            if c3==True:
                return -1
            else:
                if c1==True:
                    rt-=1
                if c2==True:
                    rt-=1
        return rt       
                

######################################################################
def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [-123] file1 file2"""

    parser = OptionParser(version=version_msg,
usage=usage_msg)
    parser.add_option("-1",
action="store_true", dest="SuppressCol1", default=False,
help = "Suppress the output column of lines unique to file1.")
    parser.add_option("-2", 
action="store_true", dest="SuppressCol2", default=False,
help = "Suppress the output column of lines unique to file2.")
    parser.add_option("-3",
action="store_true", dest="SuppressCol3", default=False,
help = "Suppress the output column of lines duplicated in file1 and file2.")
    parser.add_option("-u",
action="store_true", dest="unsorted", default=False, help = "")
    options, args = parser.parse_args(sys.argv[1:])
    
    if len(args) != 2 :
        parser.error("wrong number of operands")
    elif args[0] == "-" and args[1] == "-":
        parser.error("both operands are standard input")
    input_file1 = args[0]
    input_file2 = args[1]

    try:
        generator = comm(input_file1, input_file2)
        output = generator.output(options.SuppressCol1, 
options.SuppressCol2, options.SuppressCol3, options.unsorted)
        if output == True:
            parser.error("file 1 is not in sorted order")
        if output == False:
            parser.error("file 2 is not in sorted order")
        sys.stdout.write(output)
    except IOError as e:
        parser.error("I/O error({0}): {1}".format(e.errno, e.strerror))
#######################################################################   
if __name__ == "__main__": main()
