import matplotlib.pyplot as plt
import csv

fig, plots = plt.subplots(2, 3)

fig.suptitle("Disk Scheduling Algorithms: Disk Head Movements")

titles = ["FCFS", "SSTF", "SCAN", "C-SCAN", "LOOK", "C-LOOK"]

for algo in range(1, 7):
    name = "./csv/" + str(algo)+".csv"
    file = open(name)
    csvreader = csv.reader(file)

    header = []
    header = next(csvreader)

    rows = []
    for row in csvreader:
        rows.append(int(row[0]))

    y = []

    for i in range(0, len(rows)):
        y.append(i)

    plots[int((algo-1)/3)][(algo-1)%3].plot(rows, y)
    plots[int((algo-1)/3)][(algo-1)%3].invert_yaxis()
    plots[int((algo-1)/3)][(algo-1)%3].set_title(titles[algo-1])

plt.show()



