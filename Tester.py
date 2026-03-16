import os
import subprocess
import random
import math

class Config:
    compiled='compiled'
    uncompiled='uncompiled'
    inputData='inputData'
    outputData='outputData'
    executionTimes='executionTimes'
    averageExecutionTime='averageExecutionTime'
    numOfTestsForEachLength=10 #ile razy dla danego rodzaju ciagu loswego wykonać test
    numOfTestsInParallel=5
    variety =["random","growing","decreasing","Ashaped","Vshaped"]
    sizeGrowth={"Linear":[1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000,11000],
                "Exponential":[100,200,400,800,1600,3200,6400,12800,25600,51200,102400]}

    compiler='gcc'

if not os.path.exists(Config.compiled):
    os.mkdir(Config.compiled)

for uncompiledScript in os.listdir(Config.uncompiled):
    command = ['wsl',f'{Config.compiler}', f'{Config.uncompiled}/{uncompiledScript}', '-o', f'{Config.compiled}/{uncompiledScript[:-2]}','-lm']
    p = subprocess.run(command)
    print(p)
if not os.path.exists(Config.inputData):
    os.mkdir(Config.inputData)
if not os.path.exists(Config.outputData):
    os.mkdir(Config.outputData)
if not os.path.exists(Config.executionTimes):
    os.mkdir(Config.executionTimes)
if not os.path.exists(Config.inputData):
    os.mkdir(Config.inputData)
if not os.path.exists("averageExecutionTime"):
    os.mkdir("averageExecutionTime")


def generateRandomGrowingSeries(size,starting):
    current=starting
    series=[]
    for i in range(size):
        current += random.randint(1, 10)
        series.append(current)
    return series,current


for variety in Config.variety:
    for growthType, sizes in Config.sizeGrowth.items():
        for size in sizes:
            for num in range(Config.numOfTestsForEachLength):
                f = open(f'{Config.inputData}/{growthType}_{variety}_{size}_{num}.in', 'w')
                print(size, file=f)
                match variety:
                    case 'random':
                        print(*[random.randint(0, 10000) for i in range(size)], file=f)
                    case 'growing':
                        print(*generateRandomGrowingSeries(size,0)[0], file=f)
                    case 'decreasing':

                        print(*reversed(generateRandomGrowingSeries(size,0)[0]), file=f)
                    case 'Ashaped':
                        arr,toStartFrom=generateRandomGrowingSeries(size//2,0)
                        print(*arr, file=f)
                        print(*reversed(generateRandomGrowingSeries(size//2,toStartFrom)[0]), file=f)
                    case 'Vshaped':
                        arr, toStartFrom = generateRandomGrowingSeries(size // 2, 0)
                        print(*reversed(arr), file=f)
                        print(*(generateRandomGrowingSeries(size // 2, toStartFrom)[0]), file=f)

                f.close()


for script in os.listdir(Config.compiled):
    for variety in Config.variety:
        for growthType, sizes in Config.sizeGrowth.items():
            for size in sizes:
                for num in range(0, Config.numOfTestsForEachLength, Config.numOfTestsInParallel):
                    f_in, f_out, f_err, ps = [], [], [], []
                    for tmp in range(num, num + Config.numOfTestsInParallel):
                        command = ['wsl', 'time', f'{Config.compiled}/{script}']

                        f_in.append(open(f'{Config.inputData}/{growthType}_{variety}_{size}_{tmp}.in', 'r'))
                        f_out.append(open(f'{Config.outputData}/{script}_{growthType}_{variety}_{size}_{tmp}.out', 'w'))
                        f_err.append(open(f'{Config.executionTimes}/{script}_{growthType}_{variety}_{size}_{tmp}.time', 'w'))

                        p = subprocess.Popen(command, stdout=f_out[-1], stdin=f_in[-1], stderr=f_err[-1])
                        ps.append(p)

                    for i in range(Config.numOfTestsInParallel):
                        ps[i].wait()
                        f_in[i].close()
                        f_out[i].close()
                        f_err[i].close()

for script in os.listdir(Config.compiled):
    for variety in Config.variety:
        for growthType, sizes in Config.sizeGrowth.items():
            for size in sizes:
                times = []
                for num in range(0,Config.numOfTestsForEachLength):
                    f_time=(open(f'{Config.executionTimes}/{script}_{growthType}_{variety}_{size}_{num}.time', 'r'))

                    for line in f_time:
                        if line.startswith('real'):
                            time = line.strip().split()[1].split('m')
                            time = int(time[0]) * 60 + float(time[1][:-1])
                            times.append(time)

                    f_time.close()
                averageTime=sum(times)/Config.numOfTestsForEachLength
                f_averageTime=open(f'{Config.averageExecutionTime}/{script}_{growthType}_{variety}_{size}.time', 'w')
                #f_averageTime.write(str(averageTime))
                standardDevietion = math.sqrt(sum((t - averageTime) ** 2 for t in times) / Config.numOfTestsForEachLength)
                #f_averageTime.write(str(variance))
                f_averageTime.write(f"average={averageTime}\n")
                f_averageTime.write(f"std_dev={standardDevietion}\n")
                f_averageTime.close()





