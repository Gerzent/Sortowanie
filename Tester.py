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
    sizeGrowth={"Linear":[1000, 4000, 7000, 10000, 13000, 16000, 19000, 22000, 25000, 28000,31000,34000],
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


def to_wsl_path(path):
    path = path.replace("\\", "/")
    drive = path[0].lower()
    return f"/mnt/{drive}{path[2:]}"

wsl_cwd = to_wsl_path(os.getcwd())

import time

for script in os.listdir(Config.compiled):
    for variety in Config.variety:
        for growthType, sizes in Config.sizeGrowth.items():
            for size in sizes:
                for num in range(0, Config.numOfTestsForEachLength, Config.numOfTestsInParallel):

                    ps = []
                    f_in, f_out, f_err = [], [], []
                    start_times = []
                    end_times = []

                    for tmp in range(num, num + Config.numOfTestsInParallel):

                        command = [
                            'wsl',
                            'bash', '-c',
                            f'cd "{wsl_cwd}" && ./{Config.compiled}/{script}'
                        ]

                        f_in.append(open(f'{Config.inputData}/{growthType}_{variety}_{size}_{tmp}.in', 'r'))
                        f_out.append(open(f'{Config.outputData}/{script}_{growthType}_{variety}_{size}_{tmp}.out', 'w'))
                        f_err.append(open(f'{Config.executionTimes}/{script}_{growthType}_{variety}_{size}_{tmp}.time', 'w'))

                        start_times.append(time.perf_counter())
                        p = subprocess.Popen(command, stdout=f_out[-1], stdin=f_in[-1])
                        ps.append(p)

                    for i, p in enumerate(ps):
                        p.wait()
                        end_times.append(time.perf_counter())

                        elapsed = end_times[i] - start_times[i]
                        f_err[i].write(f"real {elapsed}\n")

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
                            value = line.strip().split()[1]
                            time = float(value)
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





