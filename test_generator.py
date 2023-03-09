name = input("Введите имя файла, куда нужно записать команды.")
text = open("tree_test.txt", "w+", encoding='UTF-8')
for i in range(100000):
    if (i % 10 == 0 and i != 0):
        text.write("\n")
    command = "k " + str(i) + " "
    text.write(command)
for i in range(0, 100000, 5):
    if (i % 10 == 0):
        text.write("\n")
    command = "d " + str(i) + " "
    text.write(command)
text.close()
