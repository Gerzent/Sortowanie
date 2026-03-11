import os
import subprocess
import random

class Config:
    compiled='compiled'
    uncompiled='uncompiled'
    inputData='inputData'
    outputData='outputData'
    executionTimes='executionTimes'
    numOfTestsForEachLength=10 #ile razy dla danego rodzaju ciagu loswego wykonać test
    numOfTestsInParallel=5
    sizes = [100, 200, 1000, 5000, 10000] #tu będą rodzaje loswych danych
    compiler='gcc'

if not os.path.exists(Config.compiled):
    os.mkdir(Config.compiled)

for uncompiledScript in os.listdir(Config.uncompiled):
    command = ['wsl',f'{Config.compiler}', f'{Config.uncompiled}/{uncompiledScript}', '-o', f'{Config.compiled}/{uncompiledScript[:-2]}']
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

for size in Config.sizes:
    for num in range(Config.numOfTestsForEachLength):
        f = open(f'{Config.inputData}/{size}_{num}.in', 'w')
        print(size, file=f)
        print(*[random.randint(0, 10000) for i in range(size)], file=f)
        f.close()

for script in os.listdir(Config.compiled):
    for num in range(0, Config.numOfTestsForEachLength, Config.numOfTestsInParallel):
        for size in Config.sizes:
            f_in, f_out, f_err, ps = [], [], [], []
            for tmp in range(num, num + Config.numOfTestsInParallel):
                command = ['wsl', 'time', f'{Config.compiled}/{script}']

                f_in.append(open(f'{Config.inputData}/{size}_{tmp}.in', 'r'))
                f_out.append(open(f'{Config.outputData}/{script}_{size}_{tmp}.out', 'w'))
                f_err.append(open(f'{Config.executionTimes}/{script}_{size}_{tmp}.time', 'w'))

                p = subprocess.Popen(command, stdout=f_out[-1], stdin=f_in[-1], stderr=f_err[-1])
                ps.append(p)

            for i in range(Config.numOfTestsInParallel):
                ps[i].wait()
                f_in[i].close()
                f_out[i].close()
                f_err[i].close()



