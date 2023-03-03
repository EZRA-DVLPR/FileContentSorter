#sort a files contents alphanumerically

#sorts backwards via the last word of the line
def backwardsSorter(toSort):
    miniList = []

    for i in range(len(toSort)):
        miniList.append(toSort[i].rsplit(' ', 1)[len(toSort[i].rsplit(' ', 1)) - 1])

    progList = list(range(0, len(toSort)))
    sortedList = []

    #insertion sort via miniList
    i = 1
    while i < len(miniList):
        j = i - 1
        while miniList[i] > miniList[j]:
            j -= 1

        if j != i - 1:
            miniList.insert(j + 1, miniList.pop(i))
            progList.insert(j + 1, progList.pop(i))

        i += 1

    #add it to sortedList in reverse order
    for i in range(len(miniList) - 1, -1, -1):
        sortedList.append(toSort[progList[i]])

    return sortedList
    
def write(sorted):
    with open('sample_file_sorted.txt', 'w') as file:
        for line in sorted:
            file.write(line + '\n')

#lines will hold the data from the file
lines = []

#read all data from file
with open('sample_file.txt', 'r', encoding='utf-8') as file:
    for f in file:
        lines.append(f.strip())

#user interaction
while True:
    #ask user for what sort to perform
    inp = input('Which sort should be performed? \n0 - First Word (Standard)\n1 - Last Word\n5 - Exit Program\n\nYour Input: ')

    #handle input given
    if inp == '0':
        print('Sorted!')
        write(sorted(lines))
        break
    elif inp == '1':
        print('Sorted!')
        write(backwardsSorter(lines))
        break
    elif inp == '5':
        print('Goodbye!')
        break
    else:
        print('Improper Input. Please Try again\n\n')