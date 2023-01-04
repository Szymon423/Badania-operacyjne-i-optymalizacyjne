import numpy as np

def generatePoints(n, canvasSize, name="test//moje_dane_1"):
    x = 0
    y = 1
    points = np.zeros((n, 2))
    

    points[0][x] = np.random.randint(1, canvasSize[x])
    points[0][y] = np.random.randint(1, canvasSize[y])

    for i in range(1, n):
        isOk = False
        while not isOk:
            isOk = True
            newX = np.random.randint(1, canvasSize[x])
            newY = np.random.randint(1, canvasSize[y])
            
            for j in range(i):
                if points[j][x] == newX:
                    if points[j][y] == newY:
                        isOk = False
                    
        points[i][x] = newX
        points[i][y] = newY
    
    np.savetxt(name, points, header=str(n), comments = "", fmt = '%i')

    
    


