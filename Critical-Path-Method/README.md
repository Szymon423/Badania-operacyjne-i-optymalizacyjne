# Critical Path Method

## Wynik działania algorytmu

### Macierz sąsiedztwa
|  | 1) | 2) | 3) | 4) | 5) | 6) | 7) | 8) | 9) | 10) |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
|  1)| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
|  2)| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
|  3)| 0 | 0 | 0 | 0 | 1 | 0 | 0 | 1 | 0 | 0 |
|  4)| 0 | 0 | 0 | 0 | 1 | 1 | 1 | 0 | 0 | 1 |
|  5)| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
|  6)| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
|  7)| 1 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 |
|  8)| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
|  9)| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 10)| 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 |


Process time: 214

### Critic times
| earlyStart | earlyFinish | lateStart | lateFinish |
| :---: | :---: | :---: | :---: |
|      121|      214|      121|      214|
|        0|       14|      200|      214|
|        0|       53|        0|       53|
|        0|        1|       52|       53|
|       53|       58|      209|      214|
|       69|      137|      146|      214|
|       47|       69|       99|      121|
|       53|      121|       53|      121|
|        0|       75|      139|      214|
|        1|       47|       53|       99|

### CRP
| action number | start time | finish time |
| :---: | :---: | :---: |
|  3 |   0 |  53 |
|  8 |  53 | 121 |
|  1 | 121 | 214 |
