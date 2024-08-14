"""
// Program: A combeined program of the 6 games required
            1. Game (1) Grade calculater
            2. Game (2) Armstrong
            3. Game (3) Pi sequence
            4. Game (4) Encryption
            5. Game (5) List comparison
            6. Game (6) Number's factor
// Authors: Mohannad Essam (Problems 3 and 6) 
// Moamen Wael (Problems 2 and 4)
// Ahmed Abdalsamea (Problems 1 and 5)
// Version: 1.0
// Date: 26/2/2024
"""

# function for game 5 checking if the 2 lists are equal
def check_list(firstlist,secondlist):
    for x in firstlist: # searching for every number of the first list in the second list
            if x not in secondlist : # returnings to use
                return False
    return True 


# Start of program 
while True:
# Main menu display    
    print("Welcome to main menu \n")
    print("1. Game (1) Grade calculater")
    print("2. Game (2) Armstrong")
    print("3. Game (3) Pi sequence")
    print("4. Game (4) Encryption")
    print("5. Game (5) List comparison ")
    print("6. Game (6) Number's factor \n")
    print("Note: Type any other number to quit")
    choice = int(input("Please choose a number from (1 --> 6) with respect to the game you want to play: " ))
    # Asking which game the user wants
    
    
#Game (1)    
    if choice == 1: # if the user chose 1 then ask for mark
        grade_average=int(input("please enter your mark : "))
        if 0<= grade_average <=100: # making sure the input is in the valid range 
            if grade_average >= 90: # Range of A+
                print("your grade is A+ \n")
            elif  grade_average >= 85 :# Range of A
                print("your grade is A \n")
            elif grade_average >= 80 :# Range of B+
                print("your grade is B+ \n")
            elif grade_average >= 75 :# Range of B
                print("your grade is B \n") 
            elif grade_average >= 70 :# Range of C+
                print("your grade is C+ \n")
            elif grade_average >= 65 :# Range of C
                print("your grade is C \n")
            elif grade_average >= 60 :# Range of D
                print("your grade is D \n")
            elif grade_average < 60 :# Range of F
                print("your grade is F \n")   
        else: # if he entered a non valid number
            print("please enter a valid mark")
                
                
# Game (2)                
    elif choice == 2:# if the user chose 2 then ask for number
          num=input("enter a number to check if it is armstrong or not ")
          sum = 0 # empty variable to add on
          if int(num) > 0: # making sure the input is positive
              power=len(num) # the power of the number size
              int_num=int(num)
              for i in num: 
                sum +=  int(i)**power # adding the power of the numbers to the sum
              if sum == int_num: # checking if the sum is equal to the number
                  print(num, "it is an armstrong number \n")
              else: # if the sum is not equal to the number   
                  print("it is not an armstrong number \n")      
          else: # if he entered a non valid number
              print("please insert a valid number ")
              
                  
# Game (3)                
    elif choice == 3:# if the user chose 3 then ask for number of terms
        n=int(input("enter number of terms you want to calculate the pi: "))
        pi = 0 # pi variable to add on
        j = 1 # variable for the number of times to add 
        i = 1 # variable for the numbers to add
        while j <= n:
            if i % 2 != 0: # Making sure to only use odd numbers
                 pi += (pow(-1,j+1))*(1/i) # the power part is to flip the sign every number and then multiplying it to the inverse of the number
                 j+=1 # moving on to next
                 i+=1 # moving on to next
            else:
                 i+=1 # moving on to next
                 
        print(pi*4,"\n") # the (pi) variable only holds the Pi/4 so we print (pi)*4
        

# Game (4)                            
    elif choice == 4: # if the user chose 4 then ask for a message
        n = input("Please enter a message you want to encrypt: ")
        k = "" # empty sting to add the ecrypted version to
        for i in n:
            ASCII_num = ord(i) # putting the ASCII code in a variable
            if ASCII_num == 32: # making sure not to change the spaces since ASCII code of spaces are equal to (32)
                k += str(chr(ASCII_num)) # adding it to the empty variable
            else:
                ASCII_num +=1 # changing the letter to the one following it
                k += str(chr(ASCII_num)) # adding it to the empty variable
        print("Your encrypted message: ", k, "\n")
        
            
 # Game (5)       
    elif choice == 5: # if the user chose 5 then ask for number of elements
        n=int(input("enter how many elements you want in the first and second list: "))
        my_list1 = [] # first empty list to add on
        for i in range(n):
            m=int(input("enter a number to put in the first list : "))
            my_list1.append(m) # taking every input and adding it to the empty list
        print("first list :",my_list1)        

        my_list2 = [] # second empty list to add on
        for i in range(n):
            m=int(input("enter a number to put in the second list : "))
            my_list2.append(m) # taking every input and adding it to the empty list
                
        print("second list", my_list2)   


                
        if check_list(my_list1,my_list2) : # calling the function to check if the 2 lists are equal
           print("true, all elements are in the list \n")
        else:
           print("false, maybe one element or more not in the list \n")
 
 
# Game (6)
    elif choice == 6: # if the user chose 6 then ask for a number
        n = int(input("Please enter your number: "))
        mlist = [] # empty list to add the factors to 
        for i in range (1,n+1): # going through every number until reaching the input
            if n % i == 0 : # if the input can be devided by the number then its a factor
                mlist.append(i) # adding the number to the list
                
            else:
                continue # moving on to next
            
        print ("The factors of",n,"are:" ,mlist, "\n")
        
        
    else: # if the user wants to quit the program
        print("Thank you for using our program")
        break

