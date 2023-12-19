class SortTech:
    def __init__(self):
        self.list = []
        self.size = 0

    def accept_list(self):
        self.size = int(input("Enter the number of students :"))
        for i in range(0,self.size):
            ele = int(input("Enter the second year percentage of students :"))
            self.list.append(ele)

        return self.list

    def display(self):
        print("\nThe list of percentage of students is :",self.list)

    def bubble(self):
        for i in range(self.size-1):
            for j in range(self.size-i-1):
                if(self.list[j] > self.list[j+1]):
                    temp = self.list[j+1]
                    self.list[j+1] = self.list[j]
                    self.list[j] = temp

        print("\nThe list after bubble sorting is :",self.list)

    def selection(self):
        for i in range(self.size-1):
            min = i
            for j in range(self.size-i-1):
                if(self.list[min] > self.list[j]):
                    min = j
                    temp = self.list[j]
                    self.list[j] = self.list[min]
                    self.list[min] = temp
        print("\nThe list after selection sorting is :",self.list)

    def insertion(self):
        for i in range(0,self.size-2):
            temp = self.list[i]
            j = i - 1
            while((self.list[j] > temp) and (j >= 0)):
                self.list[j+1] = self.list[j]
                j -= 1
            self.list[j+1] = temp
        print("\nThe list after insertion sorting is :",self.list)

    def shell(self):
        interval = 0
        while(interval < (int(self.size)/3)):
            interval = interval*3 + 1

        while(interval > 0):
            for i in range(int(interval),self.size):
                insert = self.list[i]
                j = i

                while(j > int(interval) - 1 and self.list[j - int(interval)] >= insert):
                    self.list[j] = self.list[j - int(interval)]
                    j = j - int(interval)

                    self.list[j] = insert

            interval = int((interval - 1)/3)

        print("\nThe list after shell sorting is :",self.list)

    def top5(self):
        if (len(self.list) >= 5):
            top5 = []
            list1 = self.list[::-1]
            for i in range(0,5):
                top5.append(list1[i])

            print("\nThe top five percentages are :",top5)
        else:
            print("\nTop five scores cannot be displayed.")

a = SortTech()
a.accept_list()
a.display()

flag = 1
while(flag == 1):
    print("\n-----OPTIONS MENU-----\n")
    print("Your options are :")
    print("\n1.BUBBLE SORT\n2.SELECTION SORT\n3.INSERTION SORT\n4.SHELL SORT\n5.EXIT")
    ch = int(input("\nEnter your choice of sorting technique :"))

    if ch == 1:
        a.bubble()
        a.top5()
        char = input("\nDo you want to continue?(yes/no) :")
        if char == 'yes':
            flag = 1
        else:
            flag = 0
            print("\nThanks for using this program! Have a great day!!")

    elif ch == 2:
        a.selection()
        a.top5()
        char = input("\nDo you want to continue?(yes/no) :")
        if char == 'yes':
            flag = 1
        else:
            flag = 0
            print("\nThanks for using this program! Have a great day!!")

    elif ch == 3:
        a.insertion()
        a.top5()
        char = input("\nDo you want to continue?(yes/no) :")
        if char == 'yes':
            flag = 1
        else:
            flag = 0
            print("\nThanks for using this program! Have a great day!!")

    elif ch == 4:
        a.shell()
        a.top5()
        char = input("\nDo you want to continue?(yes/no) :")
        if char == 'yes':
            flag = 1
        else:
            flag = 0
            print("\nThanks for using this program! Have a great day!!")

    elif ch == 5:
        flag = 0
        print("\nThanks for using this program! Have a great day!!")

    else:
        print("\nOOPS!!Invalid choice.")
        char = input("\nDo you want to continue?(yes/no) :")
        if char == 'yes':
            flag = 1
        else:
            flag = 0
            print("\nThanks for using this program! Have a great day!!")
