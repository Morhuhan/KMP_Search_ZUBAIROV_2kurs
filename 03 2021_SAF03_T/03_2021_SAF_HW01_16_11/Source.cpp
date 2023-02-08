#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <Windows.h>


void create_pi(int* pi, const char* p, int  size_p) {

    // Индексы для перемещения по образу
    int j = 0;
    int i = 1;

    // Пока не закончится образ
    while (i != size_p) {

        // Проверяем равенство i-го и j-того элемента

        // i-Ый и j-ый элементы НЕ РАВНЫ
        if (p[i] != p[j]) {

            // Слечай если j еще не сдвинулось
            if (j == 0) {
                pi[i] = 0;
                i++;
            }
            
            // Случай если j уже сдвинулось
            else {
                j = pi[j - 1];
            }      
        }

        // i-ый и j-ый элементы РАВНЫ
        else {
            pi[i] = j + 1;
            i++;
            j++;
        }
    }
}

int KMP(int size_p, const char* p, char* f, DWORD dwSize) {
    
    // Индекс для перемещения по тексту
    int k = 0;

    // Индекс для перемещения по образцу
    int l = 0;

    // Создание массива pi с кол-вом элементов size_p
    int* pi = (int*)calloc(size_p, sizeof(int));

    // Заполнение массива pi
    create_pi(pi, p, size_p);

    // Пока не дойдем до конца текста
    for(int i = 0; i < dwSize; i++) {

        // Сравниваем посимвольно текст и образец
        if (f[k] == p[l]) {
            k++;
            l++;

            // Если колличество сходств = размеру образца - возвращаем номер элемента с которого началось сходство
            if (l == size_p ) {
                return (k - size_p - 1);
            }
        }

        // Пробуем воспользоваться помощью массива pi
        else {

            if (l == 0) {
                k++;
            }

            else {
                l = pi[l-1];
            }

        }

    }

    // если за цикл сходств найти не удлаось - возвращаем 0
    return 0;
}

int main() {

    system("chcp 1251");
    system("cls");

    int size_p = 4;

    const char* p = (const char*)malloc(size_p * sizeof(char));

    p = "ACTG";

    const char path[] = "2022_SAF03_genome.txt";

    // Дескрипторы файла и его проекции
    HANDLE hFile = 0, hFileMapping = 0;

    // Переменная для хранения размера файла
    DWORD dwSize = 0;

    // Указатель для работы с файлом как со строкой
    char* f;

    // Создание объекта: файл
    hFile = CreateFileA(path, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    dwSize = GetFileSize(hFile, 0);

    // Создание объекта: проекция файла
    hFileMapping = CreateFileMapping(hFile, 0, PAGE_READONLY, 0, dwSize, 0);

    // f - указывает на начало файла
    f = (char*)MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, dwSize);

    printf("%d", KMP(size_p, p, f, dwSize));

}