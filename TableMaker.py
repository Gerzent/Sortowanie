import os
import pandas as pd
import matplotlib.pyplot as plt

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
if not os.path.exists("plotsAlgo"):
    os.mkdir("plotsAlgo")

if not os.path.exists("plotsData"):
    os.mkdir("plotsData")


outputFolder = "tablesForAverageTime"
algorithms = df["algorithm"].unique()
typeOfGrowths = df["typeOfGrowth"].unique()
dataVarieties = df["dataVariety"].unique()


for algorithm in algorithms:
    for typeOfGrowth in typeOfGrowths:
        table = makeTable(algorithm, typeOfGrowth)
        title = f"{typeOfGrowth}-{algorithm}"
        table.to_csv(f"{outputFolder}/{algorithm}_{typeOfGrowth}.csv")

for algorithm in algorithms:
    for typeOfGrowth in typeOfGrowths:
        plt.figure(figsize=(10, 6))
        plt.title(f"{algorithm} - {typeOfGrowth}")
        plt.xlabel("sizeOfTest")
        plt.ylabel("average execution time")
        plt.grid(True)
        if typeOfGrowth.lower() == "exponential":
            plt.xscale("log", base=2)
            plt.xlim(2 ** 6, df["sizeOfTest"].max()+100000)

        for dataVariety in dataVarieties:

            sub = df[
                (df["algorithm"] == algorithm) &
                (df["typeOfGrowth"] == typeOfGrowth) &
                (df["dataVariety"] == dataVariety)
            ].sort_values("sizeOfTest")

            if sub.empty:
                continue



            # wykres z odchyleniem standardowym
            plt.errorbar(
                sub["sizeOfTest"],
                sub["average"],
                yerr=sub["standardDeviation"],
                fmt="o-",
                capsize=5,
                label=dataVariety
            )

        plt.legend(title="dataVariety")

        filename = f"{algorithm}_{typeOfGrowth}.png"
        plt.savefig(os.path.join("plotsAlgo", filename))
        plt.close()

for dataVariety in dataVarieties:
    for typeOfGrowth in typeOfGrowths:
        plt.figure(figsize=(10, 6))
        plt.title(f"{dataVariety} - {typeOfGrowth}")
        plt.xlabel("sizeOfTest")
        plt.ylabel("average execution time")
        plt.grid(True)
        if typeOfGrowth.lower() == "exponential":
            plt.xscale("log", base=2)
            plt.xlim(2 ** 6, df["sizeOfTest"].max()+100000)

        for algorithm in algorithms:

            sub = df[
                (df["dataVariety"] == dataVariety) &
                (df["typeOfGrowth"] == typeOfGrowth) &
                (df["algorithm"] == algorithm)
            ].sort_values("sizeOfTest")

            if sub.empty:
                continue


            # wykres z odchyleniem standardowym
            plt.errorbar(
                sub["sizeOfTest"],
                sub["average"],
                yerr=sub["standardDeviation"],
                fmt="o-",
                capsize=5,
                label=algorithm
            )

        plt.legend(title="algorithm")

        filename = f"{dataVariety}_{typeOfGrowth}.png"
        plt.savefig(os.path.join("plotsData", filename))
        plt.close()
