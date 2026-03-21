import os
import subprocess
import random
import math

class Config:
    compiled = 'compiled'
    uncompiled = 'uncompiled'
    inputData = 'inputData'
    outputData = 'outputData'
    averageExecutionTime = 'averageExecutionTime'
    numOfTestsForEachLength = 10
    numOfTestsInParallel = 1
    variety = ["random", "growing", "decreasing", "Ashaped", "Vshaped"]
    sizeGrowth = {
        "Linear": [1000, 4000, 7000, 10000, 13000, 16000, 19000, 22000, 25000, 28000, 31000, 34000],
        "Exponential": [100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600, 51200, 102400]
    }
    # Zmieniamy na cl (kompilator MSVC)
    compiler = 'cl'

# Tworzenie folderów
for folder in [Config.compiled, Config.inputData, Config.outputData, Config.averageExecutionTime]:
    if not os.path.exists(folder):
        os.mkdir(folder)

# --- KOMPILACJA ---
for uncompiledScript in os.listdir(Config.uncompiled):
    # Ignoruj pliki/foldery, które nie są kodem źródłowym C
    if not uncompiledScript.endswith('.c'):
        continue
        
    source_path = os.path.join(Config.uncompiled, uncompiledScript)
    
    # Bezpieczne wyciąganie nazwy bez rozszerzenia (niezależnie od długości .c / .cpp)
    base_name = os.path.splitext(uncompiledScript)[0]
    output_name = f"{base_name}.exe"
    output_path = os.path.join(Config.compiled, output_name)
    
    # /nologo ukrywa baner startowy Microsoftu, żeby logi były czytelniejsze
    command = [Config.compiler, '/F104857600', '/nologo', '/O2', source_path, f'/Fe:{output_path}']
    
    print(f"Kompilowanie: {uncompiledScript}...")
    p = subprocess.run(command, capture_output=True, text=True)
    if p.returncode != 0:
        print(f"Błąd kompilacji pliku {uncompiledScript}!\n{p.stderr}")

# --- GENEROWANIE DANYCH (bez zmian w logice) ---
def generateRandomGrowingSeries(size, starting):
    current = starting
    series = []
    for i in range(size):
        current += random.randint(1, 10)
        series.append(current)
    return series, current

for variety in Config.variety:
    for growthType, sizes in Config.sizeGrowth.items():
        for size in sizes:
            for num in range(Config.numOfTestsForEachLength):
                file_path = f'{Config.inputData}/{growthType}_{variety}_{size}_{num}.in'
                with open(file_path, 'w') as f:
                    print(size, file=f)
                    match variety:
                        case 'random': print(*[random.randint(0, 10000) for i in range(size)], file=f)
                        case 'growing': print(*generateRandomGrowingSeries(size, 0)[0], file=f)
                        case 'decreasing': print(*reversed(generateRandomGrowingSeries(size, 0)[0]), file=f)
                        case 'Ashaped':
                            arr, start = generateRandomGrowingSeries(size // 2, 0)
                            print(*arr, *reversed(generateRandomGrowingSeries(size // 2, start)[0]), file=f)
                        case 'Vshaped':
                            arr, start = generateRandomGrowingSeries(size // 2, 0)
                            print(*reversed(arr), *generateRandomGrowingSeries(size // 2, start)[0], file=f)

# --- URUCHAMIANIE TESTÓW (Natywne Windows) ---
print("\n--- ROZPOCZYNAM URUCHAMIANIE TESTÓW ---")
scripts = [s.removesuffix('.exe') for s in os.listdir(Config.compiled) if s.endswith('.exe')]
total_scripts = len(scripts)

for s_idx, script in enumerate(scripts, 1):
    print(f"\n[{s_idx}/{total_scripts}] Testowanie algorytmu: {script}")
    
    for variety in Config.variety:
        print(f"  > Wariant: {variety}", end=" ", flush=True)
        
        for growthType, sizes in Config.sizeGrowth.items():
            for size in sizes:
                # Mały "punkt" w konsoli po każdym rozmiarze, żebyś widział postęp
                print(".", end="", flush=True)
                
                for num in range(0, Config.numOfTestsForEachLength, Config.numOfTestsInParallel):
                    ps, f_in, f_out = [], [], []

                    for tmp in range(num, min(num + Config.numOfTestsInParallel, Config.numOfTestsForEachLength)):
                        exec_path = os.path.join(Config.compiled, script)
                        fin = open(f'{Config.inputData}/{growthType}_{variety}_{size}_{num}.in', 'r')
                        fout = open(f'{Config.outputData}/{script}_{growthType}_{variety}_{size}_{num}.out', 'w')
                        
                        f_in.append(fin)
                        f_out.append(fout)
                        p = subprocess.Popen([exec_path], stdout=fout, stdin=fin)
                        ps.append(p)

                    for i, p in enumerate(ps):
                        p.wait()
                        f_in[i].close()
                        f_out[i].close()
        print(" [OK]") # Koniec wariantu

# --- ANALIZA (Z LOGOWANIEM) ---
print("\n--- OBLICZANIE ŚREDNICH ---")
for script in scripts:
    print(f"Przetwarzanie wyników dla: {script}...")
    for variety in Config.variety:
        for growthType, sizes in Config.sizeGrowth.items():
            for size in sizes:
                times = []

                for num in range(0, Config.numOfTestsForEachLength):
                    file_path = f'{Config.outputData}/{script}_{growthType}_{variety}_{size}_{num}.out'
                    
                    with open(file_path, 'r') as f_out:
                        # Read lines and ignore any trailing empty or whitespace-only lines
                        lines = [line.strip() for line in f_out if line.strip()]
                        
                        if lines:
                            final_line = lines[-1]  # Grab the actual last line of text
                            
                            if 'Czas:' in final_line:
                                # Split the line at "Czas:" and grab the part that comes after it
                                value = final_line.split('Czas:')[1].strip()
                                time = float(value)
                                times.append(time)

                averageTime=sum(times)/Config.numOfTestsForEachLength
                f_averageTime=open(f'{Config.averageExecutionTime}/{script}_{growthType}_{variety}_{size}.time', 'w')
                standardDevietion = math.sqrt(sum((t - averageTime) ** 2 for t in times) / Config.numOfTestsForEachLength)
                f_averageTime.write(f"average={averageTime}\n")
                f_averageTime.write(f"std_dev={standardDevietion}\n")
                f_averageTime.close()

    
print("\nWSZYSTKO GOTOWE!")
