import subprocess
import matplotlib.pyplot as plt
import re
import os

#########################################################################################################################################################################################

commands = [
    "./graph_search -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 10 -E 10 -R 5 -N 4 -m 1 -o o.txt",
    "./graph_search -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 20 -E 10 -R 5 -N 4 -m 1 -o o.txt",
    "./graph_search -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 30 -E 10 -R 5 -N 4 -m 1 -o o.txt",
    "./graph_search -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 40 -E 10 -R 5 -N 4 -m 1 -o o.txt",
    "./graph_search -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 40 -E 20 -R 5 -N 4 -m 1 -o o.txt",
    "./graph_search -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 40 -E 30 -R 5 -N 4 -m 1 -o o.txt",
    "./graph_search -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 40 -E 35 -R 5 -N 4 -m 1 -o o.txt",
    "./graph_search -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 40 -E 10 -R 1 -N 4 -m 1 -o o.txt",
    "./graph_search -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 40 -E 10 -R 4 -N 4 -m 1 -o o.txt",
    "./graph_search -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 40 -E 10 -R 7 -N 4 -m 1 -o o.txt",
    "./graph_search -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 40 -E 10 -R 8 -N 4 -m 1 -o o.txt",
    "./graph_search -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 40 -E 10 -R 10 -N 4 -m 1 -o o.txt"
] 

commandsMRNG = [
"./graph_search -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 30 -E 15 -R 5 -N 5 -l 5 -m 2 -o o2.txt",
"./graph_search -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 30 -E 15 -R 5 -N 5 -l 6 -m 2 -o o2.txt",
"./graph_search -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 30 -E 15 -R 5 -N 5 -l 10 -m 2 -o o2.txt",
"./graph_search -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 30 -E 15 -R 5 -N 5 -l 12 -m 2 -o o2.txt",
"./graph_search -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 30 -E 15 -R 5 -N 5 -l 15 -m 2 -o o2.txt",
"./graph_search -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 30 -E 15 -R 5 -N 5 -l 17 -m 2 -o o2.txt",
"./graph_search -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 30 -E 15 -R 5 -N 5 -l 20 -m 2 -o o2.txt",
"./graph_search -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 30 -E 15 -R 5 -N 5 -l 22 -m 2 -o o2.txt",
"./graph_search -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 30 -E 15 -R 5 -N 5 -l 25 -m 2 -o o2.txt",
"./graph_search -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 30 -E 15 -R 5 -N 5 -l 30 -m 2 -o o2.txt",
"./graph_search -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 30 -E 15 -R 5 -N 5 -l 32 -m 2 -o o2.txt"
]

executable_dirLSH = "../ergasia1/LSH"
commandsLSH = [
os.path.join(executable_dirLSH, "lsh -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 2 -L 5 -o o.txt -N 2 -R 1"),
os.path.join(executable_dirLSH, "lsh -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 4 -L 5 -o o.txt -N 2 -R 1"),
os.path.join(executable_dirLSH, "lsh -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 5 -L 5 -o o.txt -N 2 -R 1"),
os.path.join(executable_dirLSH, "lsh -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 6 -L 5 -o o.txt -N 2 -R 1"),
os.path.join(executable_dirLSH, "lsh -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 8 -L 5 -o o.txt -N 2 -R 1"),
os.path.join(executable_dirLSH, "lsh -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 10 -L 5 -o o.txt -N 2 -R 1"),
os.path.join(executable_dirLSH, "lsh -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 12 -L 5 -o o.txt -N 2 -R 1"),
os.path.join(executable_dirLSH, "lsh -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 15 -L 5 -o o.txt -N 2 -R 1"),
os.path.join(executable_dirLSH, "lsh -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 4 -L 3 -o o.txt -N 2 -R 1"),
os.path.join(executable_dirLSH, "lsh -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 4 -L 4 -o o.txt -N 2 -R 1"),
os.path.join(executable_dirLSH, "lsh -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 4 -L 10 -o o.txt -N 2 -R 1"),
os.path.join(executable_dirLSH, "lsh -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 4 -L 12 -o o.txt -N 2 -R 1")
]

executable_dirCube = "../ergasia1/Cube"
commandsCube = [
os.path.join(executable_dirCube, "cube -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 2 -M 1000 -probes 2 -o o.txt -N 2 -R 1"),
os.path.join(executable_dirCube, "cube -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 4 -M 1000 -probes 2 -o o.txt -N 2 -R 1"),
os.path.join(executable_dirCube, "cube -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 10 -M 1000 -probes 2 -o o.txt -N 2 -R 1"),
os.path.join(executable_dirCube, "cube -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 12 -M 1000 -probes 2 -o o.txt -N 2 -R 1"),
os.path.join(executable_dirCube, "cube -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 15 -M 1000 -probes 2 -o o.txt -N 2 -R 1"),
os.path.join(executable_dirCube, "cube -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 10 -M 10 -probes 2 -o o.txt -N 2 -R 1"),
os.path.join(executable_dirCube, "cube -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 4 -M 100 -probes 2 -o o.txt -N 2 -R 1"),
os.path.join(executable_dirCube, "cube -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 4 -M 5000 -probes 2 -o o.txt -N 2 -R 1"),
os.path.join(executable_dirCube, "cube -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 4 -M 1000 -probes 5 -o o.txt -N 2 -R 1"),
os.path.join(executable_dirCube, "cube -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 4 -M 1000 -probes 10 -o o.txt -N 2 -R 1"),
os.path.join(executable_dirCube, "cube -d t10k-images-idx3-ubyte -q t10k-images-idx3-ubyte -k 4 -M 1000 -probes 12 -o o.txt -N 2 -R 1")
]

#########################################################################  GNNS  #######################################################################################################

file_path = "o.txt"  
maf = []
time = []

for command in commands:
    process = subprocess.Popen(command, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
    process.stdin.write(b"END\n")
    process.stdin.flush()
    stdout, stderr = process.communicate()
    print("Process output:", stdout.decode())
    
    with open(file_path, 'r') as file:
        lines = file.readlines()
        match = re.search(r'MAF:\s+([\d.]+)', lines[-1])
        maf.append(float(match.group(1)))
        match = re.search(r'tAverageApproximate:\s+([\d.]+)', lines[11])
        time.append(float(match.group(1)))

combined_lists = list(zip(time, maf))
sorted_pairs = sorted(combined_lists, key=lambda x: x[1])
sorted_time, sorted_maf = zip(*sorted_pairs)

#########################################################################  MRNG  #######################################################################################################

file_path = "o2.txt"  
mafMRNG = []
timeMRNG = []
for commandMRNG in commandsMRNG:
    process = subprocess.Popen(commandMRNG, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
    process.stdin.write(b"yes\n")
    process.stdin.flush()
    process.stdin.write(b"END\n")
    process.stdin.flush()
    stdout, stderr = process.communicate()
    print("Process output MRNG:", stdout.decode())

    with open(file_path, 'r') as file:
        lines = file.readlines()
        match = re.search(r'MAF:\s+([\d.]+)', lines[-1])
        mafMRNG.append(float(match.group(1)))
        match = re.search(r'tAverageApproximate:\s+([\d.]+)', lines[11])
        timeMRNG.append(float(match.group(1)))

combined_lists = list(zip(timeMRNG, mafMRNG))
sorted_pairs = sorted(combined_lists, key=lambda x: x[1])
sorted_timeMRNG, sorted_mafMRNG = zip(*sorted_pairs)

#########################################################################  LSH  #######################################################################################################

file_pathlsh = "o.txt"  
maflsh = []
timelsh = []

for commandLSH in commandsLSH:
    process = subprocess.Popen(commandLSH, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
    process.stdin.write(b"END\n")
    process.stdin.flush()
    stdout, stderr = process.communicate()
    print("Process output LSH:", stdout.decode())

    with open(file_pathlsh, 'r') as file:
        lines = file.readlines()
        match = re.search(r'MAF:\s+([\d.]+)', lines[-1])
        maflsh.append(float(match.group(1)))
        match = re.search(r'tLsh:\s+([\d.]+)', lines[11])
        timelsh.append(float(match.group(1)))

combined_lists = list(zip(timelsh, maflsh))
sorted_pairs = sorted(combined_lists, key=lambda x: x[1])
sorted_timelsh, sorted_maflsh = zip(*sorted_pairs)

#########################################################################  CUBE  #######################################################################################################

file_pathcube = "o.txt"  
mafcube = []
timecube = []

for commandCube in commandsCube:
    process = subprocess.Popen(commandCube, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
    process.stdin.write(b"END\n")
    process.stdin.flush()
    stdout, stderr = process.communicate()
    print("Process output Cube:", stdout.decode())

    with open(file_pathcube, 'r') as file:
        lines = file.readlines()
        match = re.search(r'MAF:\s+([\d.]+)', lines[-1])
        mafcube.append(float(match.group(1)))
        if(len(lines) == 16):
            match = re.search(r'tCube:\s+([\d.]+)', lines[12])
        if(len(lines) == 15):
            match = re.search(r'tCube:\s+([\d.]+)', lines[11])
        timecube.append(float(match.group(1)))

combined_lists = list(zip(timecube, mafcube))
sorted_pairs = sorted(combined_lists, key=lambda x: x[1])
sorted_timeCube, sorted_mafCube = zip(*sorted_pairs)

#########################################################################  PLOTS  #######################################################################################################

####################################################  GNNS-MRNG  ###################################################

plt.plot(sorted_maf, sorted_time, color='blue', label='GNNS')                                        
plt.plot(sorted_mafMRNG, sorted_timeMRNG, color='black', label='Search on graph')
plt.xlabel('MAF')
plt.ylabel('Time(seconds)')
plt.legend()
plt.savefig('./images/GNNS-MRNG.png')
plt.close()

####################################################  GNNS-LSH  ###################################################

plt.plot(sorted_maf, sorted_time, color='blue', label='GNNS')
plt.plot(sorted_maflsh, sorted_timelsh, color='black', label='LSH')
plt.xlabel('MAF')
plt.ylabel('Time(seconds)')
plt.legend()
plt.savefig('./images/GNNS-LSH.png')
plt.close()

####################################################  MRNG-LSH  ###################################################

plt.plot(sorted_mafMRNG, sorted_timeMRNG, color='blue', label='Search on graph')
plt.plot(sorted_maflsh, sorted_timelsh, color='black', label='LSH')
plt.xlabel('MAF')
plt.ylabel('Time(seconds)')
plt.legend()
plt.savefig('./images/MRNG-LSH.png')
plt.close()

####################################################  GNNS-CUBE  ###################################################

plt.plot(sorted_maf, sorted_time, color='blue', label='GNNS')
plt.plot(sorted_mafCube, sorted_timeCube, color='black', label='Cube')
plt.xlabel('MAF')
plt.ylabel('Time(seconds)')
plt.legend()
plt.savefig('./images/GNNS-Cube.png')
plt.close()

####################################################  MRNG-CUBE  ###################################################

plt.plot(sorted_mafMRNG, sorted_timeMRNG, color='blue', label='Search on graph')
plt.plot(sorted_mafCube, sorted_timeCube, color='black', label='Cube')
plt.xlabel('MAF')
plt.ylabel('Time(seconds)')
plt.legend()
plt.savefig('./images/MRNG-Cube.png')
plt.close()