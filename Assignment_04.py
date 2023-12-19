class SearchTech:
    def __init__(self):
        self.rollno = []
        self.size = 0
        self.sorted = []

    def accept_roll(self):
        self.size = int(input("Enter the number of students who attended the training program :"))

        for i in range(0,self.size):
            ele = int(input("Enter the roll no :"))
            self.rollno.append(ele)

        return self.rollno

    def display_roll(self):
        print("The roll no of students who attended the training program are :", self.rollno)

    def linear_itr(self):
        n = int(input("\nEnter the value to be found using linear search :"))
        count = 1
        for i in range(0, self.size):
            if self.rollno[i] == n:
                print("The entered value is at position :",i)
                break

            else:
                count += 1
        print("Total no of comparisons is/are :",count)

    def binary_itr(self):
        self.sorted = self.rollno.copy()
        self.sorted.sort()

        n = int(input("\nEnter the value to be found using binary search :"))

        low = 0
        high = self.size-1
        while (low <= high):
            mid = int((low+high)/2)

            if (self.sorted[mid] == n):
                print("\nEntered value is found at position :",mid)
                return mid
            if (n < self.sorted[mid]):
                high = mid - 1

            if (n > self.sorted[mid]):
                low = mid + 1
        print("Entered value not found.")
        return -1

    # def linear_rec(self,a,i):
    #     if (self.rollno[i] == a):
    #         return i
    #     else:
    #         return self.linear_rec(a,i+1)

    def binary_rec(self,low,high):
        self.sorted = self.rollno.copy()
        self.sorted.sort()

        n = int(input("\nEnter the value to be found using binary search :"))
        if (low == high):
            if (n == self.rollno[low]):
                print("Entered value is found at position :",low)
                return low
            else:
                return -1
        else:
            mid = int((low + high)/2)
            if (self.rollno[mid] == n):
                print("\nEntered value is found at position :",mid)
                return mid
            elif (n < self.rollno[mid]):
                return self.binary_rec(low,mid-1)
            else:
                return self.binary_rec(low,mid+1)
        print("Entered value not found.")
        return -1

    def sentinel(self):
        n = int(input("\nEnter the value to be found using sentinel search :"))
        last = self.rollno[self.size-1]

        last = n

        i=0
        while(self.rollno[i] != n):
            i +=1

        self.rollno[self.size-1] = last

        if (i < self.size-1) or (n == self.rollno[self.size-1]):
            print("\nEntered value is found at position :",i)
            return i
        else:
            print("Entered value not found")
            return -1

    def fibo(self,n):
        a=b=c=1

        if n==0 or n==1:
            return 0
        else:
            while c<n:
                c=a+b
                a=b
                b=c
        return a

    def fiboS(self):
        self.sorted = self.rollno.copy()
        self.sorted.sort()
        print(self.sorted)

        start = 0
        end = self.size-1
        flag = 0
        n = self.size

        x = int(input("\nEnter the value to be found using fibonacci search :"))

        while((flag != 1) and (start <= end)):
            index = self.fibo(n)
            if(self.sorted[start+index] == x):
                loc = start+index
                flag = 1
                break
            elif(self.sorted[start+index] < x):
                start = start+index+1
            else:
                end = start+index-1

            n = end-start+1

        if flag == 1:
            print("Entered value is found at position: ",loc)
        else:
            print("Entered value not found")


a = SearchTech()
a.accept_roll()

while(True):
    print("\n\n-----MENU----\n\n")
    print("Your options are :")
    print("\n1.LINEAR\n2.BINARY\n3.SENTINEL\n4.FIBONACCI\n5.EXIT")
    ch = int(input("Enter your choice of operation :"))

    if ch == 1:
        a.linear_itr()
    elif ch == 2:
        a.binary_itr()
    elif ch == 3:
        a.sentinel()
    elif ch == 4:
        a.fiboS()
    elif ch == 5:
        print("THANK YOU")
        break
    else:
        print("OOPS!!Invalid choice.")
