# validating if number is binary function
def val_num(bn_str): 
    flaglist = []
    i = 0
    j = 0
    add = 0
    while i < len(bn_str):
        if  bn_str[i] == '0' or bn_str[i] == '1':
            flaglist.append(1)
            i+=1    
        else:
            break
        
    while j < len(flaglist):
        add += flaglist[j]
        j +=1
        
    if add == len(bn_str):
        return True
    else:
        return False
    
# one's complement function
def comp1(bn_str): 
    int(bn_str)
    comp1  = ''
    i      = 0
    while i < len(bn_str):
        if bn_str[i] == '0':
            comp1 += '1'
        elif bn_str[i] == '1':
            comp1 += '0'
        i+=1

    print('\n')
    print('The Result is: ', comp1,'\n')

# two's complement function
def comp2(bn_str): 
    int(bn_str)
    comp1  = ''
    i      = -1
    while i >= -(len(bn_str)):
        if bn_str[i] == '0':
            comp1 += '0'
        elif bn_str[i] == '1':
            comp1 += '1' 
            j=i-1
            while j >= -(len(bn_str)):
                if bn_str[j] == '0':
                    comp1 += '1'
                elif bn_str[j] == '1':
                    comp1 += '0'
                j-=1
                i = j
        i-=1
        
    return(comp1[::-1])
    
# addition calculater function
def addition(bn_str,bnstr2): 
    bn_str = bn_str[::-1]
    bnstr2 = bnstr2[::-1]
    if len(bn_str) < len(bnstr2):
        bn_str+= '0'*(len(bnstr2)-len(bn_str))
    elif len(bn_str) > len(bnstr2):
        bnstr2+= '0'*(len(bn_str)-len(bnstr2))
    result = ''
    carry = 0
    i = 0
    while i < len(bn_str):
        add = int(bn_str[i]) + int(bnstr2[i]) + carry
        if add == 2:
            carry   = 1
            result += '0'
        elif add == 1:
            carry = 0
            result += '1'
        elif add == 0:
            carry = 0
            result += '0' 
        else:
            carry = 1
            result += '1'
        if (i == (len(bn_str)-1)) and (bn_str[i] != '0' and bnstr2[i] != '0'):
            result += '1'
            
        i += 1
    return(result[::-1])

# making sure the 2 numbers are the same number of bits function
def equate(bnstr1,bnstr2): 
    bnstr1 = bnstr1[::-1]
    bnstr2 = bnstr2[::-1]
    if len(bnstr1) < len(bnstr2):
        bnstr1+= '0'*(len(bnstr2)-len(bnstr1))
    elif len(bnstr1) > len(bnstr2):
        bnstr2+= '0'*(len(bnstr1)-len(bnstr2))
    return (bnstr1[::-1], bnstr2[::-1])
            
    



# Main Program
while True: # menu 1
    print ("** Binary calculator ** \n")
    print ("A) insert new number")
    print ("B) Exit")
    choice1 = input()
    
    if choice1 == 'A':

        while True:
            bn_str = input("Please insert a binary number: \n")
            result = val_num(bn_str) # validation of first number
            if result:# menu 2
                print ("** Please select the operation ** \n")
                print ("A) Compute one's complement")
                print ("B) Compute two's complement")
                print ("C) Addition")
                print ("D) Subtraction")
                choice2 = input()
                if choice2=='A': # 1's complement
                    comp1(bn_str) #calling 1's complement function
                elif choice2 =='B':# 2's complement
                    print ("the result is: ",comp2(bn_str),'\n') #calling and printing 2's complement function
                elif choice2 == 'C': # addition
                    
                    while True: 
                        bn_str2 = input("Please insert a second binary number: \n")
                        val_num(bn_str2) # calling validation function 
                        if val_num(bn_str2): # adding
                            bn_str, bn_str2 = equate (bn_str, bn_str2)
                            print("The result is: ", addition(bn_str,bn_str2),'\n') # calling addition function 
                            break
                        else:
                            print("Please insert a valid secondary number \n")
                            continue
                elif choice2 == 'D': # subtract
                    # validation of second number
                    while True:
                        bn_str2 = input("Please insert a second binary number: \n")
                        if val_num(bn_str2): # subtracting with second complement 
                            bn_str, bn_str2 = equate (bn_str, bn_str2) # making sure the 2 numbers are the same number of bits function
                            bn_str2 = str(comp2(bn_str2)) # calling 2#s complement function
                            result = (addition(bn_str,bn_str2))
                            if len(result) > len(bn_str):
                                print("The result is: ",result[1:],'\n') # removing the carry if there is
                                break
                            else:
                                print("The result is: ", str(comp2(result)), '\n') # getting the 2's complement if there is not a carry 
                                break
                        else:
                            print("Please insert a valid secondary number \n")
                            continue
                else:
                    print ("please select a valid choice")
                break
            
            elif result == False:
                print("Please insert a valid number \n")
                continue
                

            
    elif choice1 =='B':
        break
    
    
    else:
        print("Please select a valid choice")

    
