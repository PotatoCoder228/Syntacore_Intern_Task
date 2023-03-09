def main_test():
    print("Тест значений в дереве, записанных после выполнения скрипта.")
    name = input("Введите имя файла, из которого нужно проверять команды:")
    text = open(name, "r", encoding="UTF-8")
    pattern_string = ""
    answer = ""
    deleted = 0
    for i in range(100000):
        if (i % 5 != 0):
            pattern_string += str(i) + " "
    list = []
    for i in range(1, 100000):
        if (i % 5 != 0):
            list.append(i)
    for i in range(79999):
        pattern_string += str(list[i]) + " "
    counter = 0
    pattern_string += str(0) + " "
    for i in range(79999):
        if (i % 5 == 0):
            pattern_string += str(counter) + " "
        else:
            counter += 1
            pattern_string += str(counter) + " "
    answer = text.read()
    if (pattern_string == answer):
        text.close()
        print("Ответ совпадает с ожидаемым.")
        input("Нажмите Enter для выхода")
    else:
        text.close()
        print("Ответ не совпадает с ожидаемым")
        input("Нажмите Enter для выхода")


main_test()
