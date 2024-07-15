# Задание 12 - Каналы 
## Сборщик проекта
В качестве сборщика проекта используется Makefile. Для компиляции проекта необходимо ввести следующую команду в корне проекта:
``` bash
make
```

Для очистки бинарных файлов можно воспользоваться командой:
``` bash
make clean
```

## Задание
1) Реализовать программу, которая создает неименованный канал и порождает процесс. Родительский процесс закрывает дескриптор для чтения из канала и записывает в канал строку “Hi!”, затем ожидает завершения дочернего процесса. Дочерний процесс закрывает дескриптор для записи в канал, считывает строку из канала и выводит на экран.
2) Реализовать 2 программы, первая сервер, вторая клиент. Сервер создает именованный канал и открывает его только на запись, записывает строку “Hi!” и завершается. Клиент открывает созданный канал сервером только на чтение, считывает строку из канала и выводит на экран. Удает канал.
3) Переписать командный интерпретатор из задания по процессам так, чтобы он поддерживал конструкции вида `ls /bin | grep ssh`
## Результаты тестирования программ
### Задание №1
```
Child read string: Hi!
```
### Задание №2
Server:
```
thenorth@pop-os:~/eltex/Pipes$ ./task2/bin/server
thenorth@pop-os:~/eltex/Pipes$ 
```
Client
```
thenorth@pop-os:~/eltex/Pipes$ ./task2/bin/client
Client read: Hi!
thenorth@pop-os:~/eltex/Pipes$
```

### Задание №3
```
thenorth:/home/thenorth/eltex/Pipes$ ls /bin | grep ssh
ssh
ssh-add
ssh-agent
ssh-argv0
ssh-copy-id
ssh-keygen
ssh-keyscan
thenorth:/home/thenorth/eltex/Pipes$ 
```

## Демонстрация работы программ
### Задание №1
![task1](https://github.com/user-attachments/assets/ad6cad78-ed02-4965-855f-8a2aac8e5920)

### Задание №2
![task2](https://github.com/user-attachments/assets/102b9492-b5ca-45ea-bd80-5e60f2d5a5bf)

### Задание №3
![task3](https://github.com/user-attachments/assets/05e80deb-5089-4468-ab4e-834466d5b79f)

## Тест на утечку памяти
### Задание №3
![image](https://github.com/user-attachments/assets/93a30d2a-debd-4ade-a208-c62dcb111938)

