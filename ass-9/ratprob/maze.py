from fibheap import *
import pickle
import math
def isValid(row,col,ROW,COL):
    return (row >= 0) and (row < ROW) and (col >= 0) and (col < COL)

def isUnBlocked(ar,row,col):
    #print("In unbolc")
    if ar[row][col]==1:
        #print("yeah")
        return True
    else:
        return False

def isDestination(row,col,row1,col1):
    if row == row1 and col == col1:
         return True
    else:
         return False

def calh(row,col,row1,col1,t):
    if t==1:
        return abs(row-row1)+abs(col - col1)
    elif t==2:
        return max(abs(row-row1),abs(col - col1))
    elif t==3:
        return math.sqrt(((row - row1) * (row - row1)) + ((col - col1) * (col - col1)))


def  tracePath(arr,row1,col1,row,col):
    print("The Path is:")
    row2=row1
    #print(row2,row)
    col2=col1
    #print(col2,col)
    while True:
         if row2==row and col2==col:
             print("(", col2, ",", row2, ")")
             break
         else:
            print("(", col2, ",", row2, ")", end="<-")
            x=row2
            y=col2
            row2=arr[x][y][0][3]
            col2=arr[x][y][0][4]
            #print("\n",row2,col2)

    #print("(",row,",",col,")")
    return

def astar():
    #ROW, COL = input("Enter row and column values:").split()
    #ROW=8
    #COL=8
    #ar = [[0 for i in range(COL)] for j in range(ROW)]
    infile = open("L9_P1_input.pkl", "rb")
    ar = pickle.load(infile)
    infile.close()
    '''for i in range(ROW):
        for j in range(COL):
            #print(i,j)
            ar[i][j]=1
            #ar[i][j] =input("Enter")

    ar[1][1]=0
    ar[0][1]=0
    ar[1][2]=0
    ar[0][2]=0'''
    ROW=len(ar)
    COL=len(ar[0])
    #row,col=[int(x) for x in input("Enter row and column values of source: ").split()]
    #row1,col1=[int(x) for x in input("Enter row and column values of destination: ").split()]
    col=int(input("Enter source row:"))
    row=int(input("Enter source column:"))
    col1=int(input("Enter destination row:"))
    row1=int(input("Enter destination  column:"))
    #print(row,col,row1,col1)
    if isValid(row, col,ROW,COL) == False:
            print("Source is invalid\n")
            return

    if isValid(row1, col1,ROW,COL) == False:
       print("Destination is invalid\n")
       return

    if ar[row][col]==0 or ar[row1][col1]==0:
       print("Source or the destination is blocked\n")
       return

    if isDestination(row,col,row1,col1) == True:
         #print("We are already at the destination\n")
         return

    cl = [[False for i in range(COL)] for j in range(ROW)]
    arr = [[[] for i in range(COL)] for j in range(ROW)]
    for i in range(ROW):
        for j in range(COL):
            arr[i][j]=[(100000,100000,100000,-1,-1)]
            #arr[i][j][0][1]=100000
            #arr[i][j][0][2]=100000
            #arr[i][j][0][3]=-1
            #arr[i][j][0][4]=-1

    arr[row][col]=[(0,0,0,row,col)]
    #arr[row][col][0][1]=0
    #arr[row][col][0][2]=0
    #arr[row][col][0][3]=row
    #arr[row][col][0][4]=col
    #print("tutu")
    #print(arr[row][col][0][0])
    ol=[]
    heap=makefheap()
    ol.append([(arr[row][col][0][0],arr[row][col][0][1],arr[row][col][0][2],arr[row][col][0][3],arr[row][col][0][4],row,col)])
    fheappush(heap,[(arr[row][col][0][0],arr[row][col][0][1],arr[row][col][0][2],arr[row][col][0][3],arr[row][col][0][4],row,col)])
    fde = False
    t=int(input("Enter choice for approximation heuristic that shall be used for distance calculation:\n"
            "1 for Manhattan Distance\n"
            "2 for Diagonal Distance\n"
            "3 for Euclidean Distance\n"
            "Enter the choice to calculate h:"))
    #t=3
    while len(ol)!=0:
     node=fheappop(heap)
     #print("start",node)
     ol.remove(node)
     r=node[0][5]
     #print("parent x of removed node is :",node[0][3])
     c=node[0][6]
     #print("parent y of removed node is :",node[0][4])
     cl[r][c]=True
     set1={r-1,r,r+1}
     set2={c-1,c,c+1}
     for i in set1:
         for j in set2:
             if not (i==r and j==c):
                 if isValid(i,j,ROW,COL)==True:
                     #print("here in isValid")
                     #print("i is:",i," j is:",j)
                     if isDestination(i,j,row1,col1)==True:
                         #print("here in isdestination")
                         node = arr[i][j].pop()
                         li1 = list(node)
                         li1[3]=r
                         #print("main x parent is:",r)
                         li1[4]=c
                         #print("main y parent is:",c)
                         node3=tuple(li1)
                         arr[i][j].append(node3)
                         #print(arr[i][j])
                         #print("The destination cell is found\n")
                         tracePath(arr,row1,col1,row,col)
                         fde=True
                         return

                     elif cl[i][j] == False and ar[i][j]==1:
                         #print("here in calculating f g h")
                         g1 = float(arr[r][c][0][1]) + 1.0
                         h1 = calh(i,j,row1,col1,t)
                         f1 = g1 + h1
                         if arr[i][j][0][0]==100000 or arr[i][j][0][0]>f1:
                             #print("here in adding the node to openlist and fibo and set fgh")
                             arr[i][j]=[(f1,g1,h1,r,c)]
                             #arr[i][j][0][1]=g1
                             #arr[i][j][0][2]=h1
                             #arr[i][j][0][3]=r
                             #arr[i][j][0][4]=c
                             ol.append([(arr[i][j][0][0],arr[i][j][0][1],arr[i][j][0][2],arr[i][j][0][3],arr[i][j][0][4],i,j)])
                             fheappush(heap,[(arr[i][j][0][0],arr[i][j][0][1],arr[i][j][0][2],arr[i][j][0][3],arr[i][j][0][4],i,j)])

    if fde==False:
        print("Failed to find the Destination Cell\n")

    return

astar()
