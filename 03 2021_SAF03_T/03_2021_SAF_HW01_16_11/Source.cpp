#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <Windows.h>


void create_pi(int* pi, const char* p, int  size_p) {

    // ������� ��� ����������� �� ������
    int j = 0;
    int i = 1;

    // ���� �� ���������� �����
    while (i != size_p) {

        // ��������� ��������� i-�� � j-���� ��������

        // i-�� � j-�� �������� �� �����
        if (p[i] != p[j]) {

            // ������ ���� j ��� �� ����������
            if (j == 0) {
                pi[i] = 0;
                i++;
            }
            
            // ������ ���� j ��� ����������
            else {
                j = pi[j - 1];
            }      
        }

        // i-�� � j-�� �������� �����
        else {
            pi[i] = j + 1;
            i++;
            j++;
        }
    }
}

int KMP(int size_p, const char* p, char* f, DWORD dwSize) {
    
    // ������ ��� ����������� �� ������
    int k = 0;

    // ������ ��� ����������� �� �������
    int l = 0;

    // �������� ������� pi � ���-��� ��������� size_p
    int* pi = (int*)calloc(size_p, sizeof(int));

    // ���������� ������� pi
    create_pi(pi, p, size_p);

    // ���� �� ������ �� ����� ������
    for(int i = 0; i < dwSize; i++) {

        // ���������� ����������� ����� � �������
        if (f[k] == p[l]) {
            k++;
            l++;

            // ���� ����������� ������� = ������� ������� - ���������� ����� �������� � �������� �������� ��������
            if (l == size_p ) {
                return (k - size_p - 1);
            }
        }

        // ������� ��������������� ������� ������� pi
        else {

            if (l == 0) {
                k++;
            }

            else {
                l = pi[l-1];
            }

        }

    }

    // ���� �� ���� ������� ����� �� ������� - ���������� 0
    return 0;
}

int main() {

    system("chcp 1251");
    system("cls");

    int size_p = 4;

    const char* p = (const char*)malloc(size_p * sizeof(char));

    p = "ACTG";

    const char path[] = "2022_SAF03_genome.txt";

    // ����������� ����� � ��� ��������
    HANDLE hFile = 0, hFileMapping = 0;

    // ���������� ��� �������� ������� �����
    DWORD dwSize = 0;

    // ��������� ��� ������ � ������ ��� �� �������
    char* f;

    // �������� �������: ����
    hFile = CreateFileA(path, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    dwSize = GetFileSize(hFile, 0);

    // �������� �������: �������� �����
    hFileMapping = CreateFileMapping(hFile, 0, PAGE_READONLY, 0, dwSize, 0);

    // f - ��������� �� ������ �����
    f = (char*)MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, dwSize);

    printf("%d", KMP(size_p, p, f, dwSize));

}