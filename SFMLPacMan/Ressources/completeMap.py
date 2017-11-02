
lines = []
with open("mapHalf.txt", 'r') as f:
    for line in f:
        lines.append(line)


toWrite = []
with open("mapComplete.txt", 'w') as f:
    for line in lines:
        line = line.rstrip()
        completeLine = line + line[::-1] + '\n'
        toWrite.append(completeLine)
        print completeLine
    f.writelines(toWrite)


