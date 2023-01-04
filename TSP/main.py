import time
import numpy as np
import tsp 

# okreslenie ścieżki do pliku testowego
file = "test\\data_51.txt"

# inicjalizacja obiektu 
test = tsp.TSP()

# importowanie danych z pliku
test.importData(file)

# określenie miasta początkowego
test.createFirstTour(3)

# określenie max liczby interacji dla SA
maxIterationNumber = 50_000

# określenie max temperatury dla SA
maxTemperature = 10

# odaplamy timer
start = time.time_ns()

# nasze dwa algorytmy do testów
# test.SA(maxIterationNumber, maxTemperature)
test.opt2()

# znowu odpalamy timer
finish = time.time_ns()

# liczymy czas egzekucji
elapsedTime = finish - start
print("czas trwania: " + str(elapsedTime // 1_000_000) + "ms")

# printowanie rozwiązania
test.showSolution()
