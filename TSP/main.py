import time
import numpy as np
import tsp 


file = "test\\data_51.txt"

test = tsp.TSP()

test.importData(file)
test.createFirstTour(3)
test.opt2()
test.showSolution()
