import numpy as np
import matplotlib.pyplot as plt


class TSP: 
    
    tour = np.zeros(3, dtype=int)
    graf = np.zeros(3, dtype=int)
    distances = np.zeros(3)
    n = 0
    length = 0
    startCity = 0
    changesOccured = True

    def __init__(self):
        pass

    
    def importData(self, path):
        f = open(path)
        zawartosc = f.read()
        wiersze = zawartosc.split("\n")
        n = int(wiersze[0])
        C = np.zeros((n, 2), dtype=int)
        for i in range(1, n + 1):
            zmienna = wiersze[i].split()
            C[i - 1][0] = int(zmienna[0])
            C[i - 1][1] = int(zmienna[1])
        f.close()
        self.graf = C
        self.n = n
        self.calculateDistances()

    def createFirstTour(self, start_city):
        self.startCity = start_city
        self.tour = np.zeros(self.n + 1)
        self.tour[0] = start_city
        
        for i in range(0, self.n):
            if i < self.startCity:
                self.tour[i + 1] = i
            else:
                self.tour[i + 1] = i + 1
        self.tour[self.n] = start_city
        # print(self.tour)

    def calculateDistances(self):
        self.distances = np.zeros((self.n, self.n))
        for i in range(self.n):
            for j in range(self.n):
                self.distances[i][j] = np.sqrt((self.graf[i][0] - self.graf[j][0]) ** 2 + (self.graf[i][1] - self.graf[j][1]) ** 2)
        # print(self.distances)

    def calculateLength(self, currentTour):
        _len = 0
        for i in range(len(currentTour) - 1):
            _len += self.distances[int(currentTour[i])][int(currentTour[i + 1])]
        return _len

    def swap(self, currentTour, i, j):

        newTour = np.copy(currentTour)

        partToFlip = np.copy(newTour[i:j+1])
        newTour[i:j+1] = np.flip(partToFlip)
        # help = newTour[i]
        # newTour[i] = newTour[j]
        # newTour[j] = help
        return newTour


    def showSolution(self):

        x = np.zeros(self.n)
        y = np.zeros(self.n)
        for i in range(self.n):
            x[i] = self.graf[int(self.tour[i])][0]
            y[i] = self.graf[int(self.tour[i])][1]


        fig, ax = plt.subplots()
        ax.plot(x, y)
        ax.scatter(x, y)
        for i, txt in enumerate(self.tour[:-1]):
            ax.annotate(int(txt), (x[i], y[i]))

        plt.show()
        

    def opt2(self):

        # tablica zawierająca aktualnie wygenerowaną permutację
        currentTour = np.copy(self.tour)

        # tablica z minimalną permutacją w każdej iteracji while-a
        currentMinTour = np.copy(self.tour)

        # szukamy kolejnych permutacji jeżeli poprzednia znaleziona była lepszą lub
        # jeżeli nie znaleźliśmy nic lepszego to lecimy dodatkowo jesszcze jedną iterację while-a 
        while self.changesOccured:
            # uznajemy, że nie pojawiły się żadne zmiany
            self.changesOccured = False

            # pętla iterująca przez miasta podlegające permutacjom
            for i in range(1, self.n):
                # pętla iterująca przez miasta podlegające permutacjom
                for j in range(1, self.n):
                    # dodać omijanie sąsiednich elementów

                    # do tablicy z aktualną permutacją zapisujemy pewną permutację stworzoną z permutacji
                    # stanowiącej najlepszą w poprzedniej iteracji while-a
                    currentTour = self.swap(self.tour, i, j)

                    # sprawdzamy, czy stworzona właśnie permutacja jest lepsza od najlepszej jaką stworzyliśmy
                    # w tej iteracji while-a
                    if self.calculateLength(currentTour) < self.calculateLength(currentMinTour):
                        #jeśli tak, to zapisujemy ją do najlepszej w bieżącej iteracji while-a
                        currentMinTour = currentTour
            
            # sprawdzenie, czy znalezione minium jest mniejsze od globalnego minimum
            if self.calculateLength(currentMinTour) < self.calculateLength(self.tour):
                # jeśli tak, to zapisujemy je do minimalnej, globalnej permutacji
                self.tour = currentMinTour

                # dodatkowo określamy, że pojawiła się zmiana
                self.changesOccured = True
           
        print(self.tour.astype(int))
        print(self.calculateLength(self.tour))

    def simulatedAnnealing(self):
        # tablica zawierająca aktualnie wygenerowaną permutację
        currentTour = np.copy(self.tour)

        # tablica z minimalną permutacją w każdej iteracji while-a
        currentMinTour = np.copy(self.tour)

        # szukamy kolejnych permutacji jeżeli poprzednia znaleziona była lepszą lub
        # jeżeli nie znaleźliśmy nic lepszego to lecimy dodatkowo jesszcze jedną iterację while-a 
        while self.changesOccured:
            # uznajemy, że nie pojawiły się żadne zmiany
            self.changesOccured = False

            # tutaj należy wprowadzić wybór krawędzi do swap-a w sposób randomowy
            

            # sprawdzenie, czy znalezione minium jest mniejsze od globalnego minimum
            if self.calculateLength(currentMinTour) < self.calculateLength(self.tour):
                # jeśli tak, to zapisujemy je do minimalnej, globalnej permutacji
                self.tour = currentMinTour

                # dodatkowo określamy, że pojawiła się zmiana
                self.changesOccured = True
           
        print(self.tour.astype(int))
        print(self.calculateLength(self.tour))


    def dp(self, distances):

        n = len(distances)
        empty = np.zeros((n + 1, n + 1))
        empty[1:, 1:] = distances
        distances = empty.copy()

        memo = [[-1]*(1 << (n+1)) for _ in range(n+1)]
        
        ans = 10**9
        for i in range(1, n+1):
            ans = min(ans, fun(i, (1 << (n+1))-1, memo, distances) + distances[i][1])
        return ans

def fun(i, mask, memo, distance):
    n = len(distance)

    if mask == ((1 << i) | 3):
        return distance[1][i]

    # memoization
    if memo[i][mask] != -1:
        return memo[i][mask]

    res = 10**9

    for j in range(1, n + 1):
        if (mask & (1 << j)) != 0 and j != i and j != 1:
            res = min(res, fun(j, mask & (~(1 << i)), memo, distance) + distance[j][i])
    memo[i][mask] = res
    return res

def generatePoints(n, canvasSize, name="test//data_new.txt"):
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
