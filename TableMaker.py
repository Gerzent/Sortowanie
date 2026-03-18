import os
import pandas as pd

baseOfTable="averageExecutionTime"
records=[]
for file in os.listdir(baseOfTable):
    name=file[:-5]
    algorithm,typeOfGrowth,dataVariety,sizeOfTest=name.split("_")
    sizeOfTest=int(sizeOfTest)
    with open(os.path.join(baseOfTable, file)) as f:
        lines = f.readlines()
        average = float(lines[0].split("=")[1])
        standardDeviation = float(lines[1].split("=")[1])
    records.append({
        "algorithm": algorithm,
        "typeOfGrowth": typeOfGrowth,
        "dataVariety": dataVariety,
        "sizeOfTest": sizeOfTest,
        "average": average,
        "standardDeviation": standardDeviation
    })
df = pd.DataFrame(records)#wrzucamy do tabeli


def makeTable(algorithm, typeOfGrowth):
    sub = df[(df["algorithm"] == algorithm) & (df["typeOfGrowth"] == typeOfGrowth)]#filtrowanie kolumn dla danego algorytmu i typu eksperymentu
    table = sub.pivot(index="sizeOfTest", columns="dataVariety", values="average")#tabela
    return table


if not os.path.exists("tablesForAverageTime"):
    os.mkdir("tablesForAverageTime")
outputFolder = "tablesForAverageTime"
algorithms = df["algorithm"].unique()
typeOfGrowths = df["typeOfGrowth"].unique()

for algorithm in algorithms:
    for typeOfGrowth in typeOfGrowths:
        table = makeTable(algorithm, typeOfGrowth)
        title = f"{typeOfGrowth}-{algorithm}"
        table.to_csv(f"{outputFolder}/{algorithm}_{typeOfGrowth}.csv")
