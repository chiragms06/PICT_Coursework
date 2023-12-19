class SortTech:
    def __init__(self):
        self.list = []
        self.size = 0

    def accept_list(self):
        self.size = int(input("Enter the number of students :"))
        for i in range(self.size):
            ele = int(input("Enter the second year percentage of students :"))
            self.list.append(ele)


    def quick_sort(self,low,high):

        if (low >= high):
            return
        else:
            pivot = self.list[low]
            i = low + 1
            j = high

            while(i <= j):

                while(i <= high and self.list[i] < pivot ):
                    i += 1
                while(j >= low and self.list[j] > pivot):
                    j -= 1
                if(i < j):
                    temp = self.list[j]
                    self.list[j] = self.list[i]
                    self.list[i] = temp
                    i += 1
                    j -= 1


            temp = self.list[j]
            self.list[j] = self.list[low]
            self.list[low] = temp

            self.quick_sort(0,j-1)
            self.quick_sort(j+1,high)

    def display(self):
        print("\nThe array is:",self.list)


a = SortTech()
a.accept_list()
a.display()
a.quick_sort(0,a.size-1)
a.display()
