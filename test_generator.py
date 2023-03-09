text = open("../../OneDrive/Рабочий стол/file.txt", "w+", encoding='UTF-8')
for i in range(100000):
    if (i % 10 == 0 and i != 0):
        text.write("\n")
    command = "k " + str(i) + " "
    text.write(command)
for i in range(100000):
    if (i % 10 == 0):
        text.write("\n")
    command = "m " + str(i) + " "
    text.write(command)
for i in range(0, 100000, 5):
    if (i % 10 == 0):
        text.write("\n")
    command = "n " + str(i) + " " + "d " + str(i) + " " + "n " + str(i) + " "
    text.write(command)
text.close()
