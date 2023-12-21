class Matrix:
    def __init__(self):
        self.rows = 0
        self.cols = 0
        self.mat = []
    
    def accept(self):
        self.rows = int(input("Enter no of rows :"))
        self.cols = int(input("Enter no of cols :"))
        for i in range(self.rows):
            r = []
            for j in range (self.cols):
                ele = int(input("Enter the element :"))
                r.append(ele)
            self.mat.append(r)
            
    def display(self):
        print("\nThe matrix is :")
        for i in range(self.rows):
            for j in range (self.cols):
                print(self.mat[i][j],end=" ")
            print()
            
    def transpose(self):
        print("\nThe transpose is :")
        for j in range(self.cols):
            for i in range (self.rows):
                print(self.mat[i][j],end=" ")
            print()
        
    def addition(self,b):
        if(self.rows == b.rows and self.cols == b.cols):
            c = []
            for i in range(self.rows):
                r = []
                for j in range(self.cols):
                    r.append(self.mat[i][j] + b.mat[i][j])
                c.append(r)
            print("\nThe matrix after addition is :")
            for i in range(self.rows):
                for j in range (self.cols):
                    print(c[i][j],end=" ")
                print()
        else:
            print("\nMatrix addition is not possible")
            
    def subtraction(self,b):
        if(self.rows == b.rows and self.cols == b.cols):
            c = []
            for i in range(self.rows):
                r = []
                for j in range(self.cols):
                    r.append(self.mat[i][j] - b.mat[i][j])
                c.append(r)
            print("\nThe matrix after subtraction is :")
            for i in range(self.rows):
                for j in range (self.cols):
                    print(c[i][j],end=" ")
                print()
        else:
            print("\nMatrix subtraction is not possible")
        
    def mul(self,b):
        if(self.rows == b.cols):
            c = []
            for i in range(self.rows):
                r = []
                for j in range(b.cols):
                    sum = 0
                    for k in range(self.cols):
                        sum += self.mat[i][k]*b.mat[k][j]
                    r.append(sum)
                c.append(r)
            print("\nThe matrix after muliplication is :")
            for i in range(self.rows):
                for j in range (self.cols):
                    print(c[i][j],end=" ")
                print()
        else:
            print("\nMatrix multiplication is not possible")        
                
a = Matrix()
a.accept()
a.display()

b = Matrix()
b.accept()
b.display()

while(True):
    print("\n-----MENU-----\n")
    print("Your options are :")
    print("\n1.Addition\n2.Subtraction\n3.Multiplication\n4.Transpose\n5.Exit\n")
    op = int(input("Enter your choice :"))
    
    if op == 1:
        a.addition(b)
    elif op == 2:
        a.subtraction(b)
    elif op == 3:
        a.mul(b)
    elif op == 4:
        a.transpose()
    elif op == 5:
        print("Thank you")
        break
    else:
        print("wrong choice")
    ip = input("Do you want to continue?(y/n):")
    if (ip =='y' or ip == 'Y'):
        pass
    else:
        print("Thank you")
        break

