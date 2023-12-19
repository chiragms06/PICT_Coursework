
class String:

    def __init__(self):                
        self.charList = []            
        self.strLen = 0            
        self.wordList = []            
        self.wordCount = 0              

    def get_string(self):            
        temp = input("Enter string = ")
        for i in range(len(temp)):
            self.charList.append(temp[i])
            self.strLen += 1
        self.word_list()

    def word_list(self):
        word = ""                      
        for i in range(self.strLen):
            if self.charList[i] != " ":
                word += self.charList[i]
            else:
                self.wordList.append(word)
                self.wordCount += 1
                word = ""
        self.wordList.append(word)      
        self.wordCount += 1

    def display_string(self):      
        print("String =", end=" ")
        for i in range(self.strLen):
            print(self.charList[i], end="")

        print("\nLength of string =", self.strLen)

        print("Word List =", self.wordList)

        print("No of words =", self.wordCount, end="\n")

    def longest_word(self):            
        curr_len = 0
        curr_str = ""
        max_len = 0
        max_str = ""

        for i in range(self.wordCount):
            curr_str = self.wordList[i]
            for char in curr_str:
                curr_len += 1

            if curr_len > max_len:    
                max_len = curr_len
                max_str = curr_str
                curr_len = 0

            else:
                curr_len = 0
        return max_str

    def freq_of(self, key):                    
        freq = 0
        for i in range(self.strLen):
            if self.charList[i] == key:
                freq += 1
        return freq

    def check_palindrome(self):              
        for i in range(int(self.strLen/2)):
            if self.charList[i] != self.charList[self.strLen - i - 1]:
                return "String is not a palindrome"
        return "String is a palindrome"

    def substr_occurence(self, substr):      
        k = 0                                  
        for i in range(self.strLen):          
            if self.charList[i] == substr.charList[k]:
                k += 1                          
                k = 0                          
            if k == substr.strLen:            
                return i - substr.strLen + 1
        return -1

    def word_count(self):              
        word_dic = {}
        for word in self.wordList:
            if word not in word_dic:
                word_dic[word] = 1
            else:
                word_dic[word] += 1

        for word in word_dic:
            print(word, " =", word_dic[word])

    def all_occ(self, substr):      
        indices = []                            
        k = 0                                  
        for i in range(self.strLen):            
            if self.charList[i] == substr.charList[k]:
                k += 1                          
            else:
                k = 0                          
            if k == substr.strLen:            
                indices.append(i - substr.strLen + 1)      
                k = 0
        return indices

    def get_substr(self, st, en):          
        ans = String()
        for i in range(st, en+1):
            ans.charList.append(self.charList[i])
            ans.strLen += 1
        ans.word_list()
        return ans


while True:
    print("\n-------- Menu --------")
    print("1. Enter a new String")
    print("2. Display word with the longest length")
    print("3. Frequency of occurrence of a character in the string")
    print("4. Check if string is palindrome")
    print("5. Find index of first occurrence of substring")
    print("6. Occurrence of each word in string")
    print("7. Find all occurrences of a substring in string")
    print("8. Find substring in given range")
    print("9. Exit")
    print("----------------------")

    choice = int(input("\nEnter your choice = "))

    if choice == 1:  
        objStr = String()
        objStr.get_string()
        objStr.display_string()

    elif choice == 2:      
        print("Longest word in string =", objStr.longest_word())

    elif choice == 3:      
        key = input("\nEnter character to find its no of occurrences = ")
        print("Frequency of occurrence of", key, " =", objStr.freq_of(key))

    elif choice == 4:      
        print("\n" + objStr.check_palindrome() + "\n")

    elif choice == 5:      
        objSubStr = String()
        objSubStr.get_string()
        msg = objStr.substr_occurence(objSubStr)
        if msg == -1:
            print("Substring not found\n")
        else:
            print("Substring found first at index =", msg, "\n")

    elif choice == 6:      
        print("\nWord count in given string :")
        objStr.word_count()

    elif choice == 7:      
        objSubStr = String()
        print("\nTo find a substring in given string:")
        objSubStr.get_string()
        Idx = objStr.all_occ(objSubStr)
        if not Idx:
            print("Substring not found")
        else:
            print("Substring occurs at indices =", objStr.all_occ(objSubStr))

    elif choice == 8:      
        St = int(input("Enter start index of substring = "))
        En = int(input("Enter end index of substring (inclusive) = "))
        if St < 0 or En < 0 or St > objStr.strLen or En > objStr.strLen:  
            print("Indices out of range!")
        else:
            print("Substring in given range:")
            Ans = objStr.get_substr(St, En)
            Ans.display_string()

    else:      
        print("\nExit . . .")
        break
