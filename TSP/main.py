import time
import numpy as np
import tsp 
from generator import generatePoints


### generowanie naszych własnych danych testowych:
generatePoints(30, (100, 100), "test\\dupa.txt")

# okreslenie ścieżki do pliku testowego
file = "test\\dupa.txt"

# inicjalizacja obiektu 
test = tsp.TSP()

# importowanie danych z pliku
test.importData(file)

# określenie miasta początkowego
test.createFirstTour(3)

# określenie max liczby interacji dla SA
maxIterationNumber = 100_000

# określenie max temperatury dla SA
maxTemperature = 15

# odaplamy timer
start = time.time_ns()

# nasze dwa algorytmy do testów
test.SA(maxIterationNumber, maxTemperature)
# test.opt2()

# znowu odpalamy timer
finish = time.time_ns()

# liczymy czas egzekucji
elapsedTime = finish - start
print("czas trwania: " + str(elapsedTime // 1_000_000) + "ms")

# printowanie rozwiązania
test.showSolution()
