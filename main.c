#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_FILENAME_LEN 1000
#define MAX_LINE_LEN 10000

int count_chars(char *filename);
int count_words(char *filename);

int main(int argc, char *argv[]) {
    char filename[MAX_FILENAME_LEN];
    char *parameter;
    int result;

    // ��������в���
    if (argc != 3) {
        printf("�÷�: %s [-c | -w] [�ļ���]\n", argv[0]);
        return 1;
    }

    // �������
    parameter = argv[1];
    strcpy(filename, argv[2]);

    // ���ݲ������ö�Ӧ�ĺ���
    if (strcmp(parameter, "-c") == 0) {
        result = count_chars(filename);
        printf("�ַ�����%d\n", result);
    } else if (strcmp(parameter, "-w") == 0) {
        result = count_words(filename);
        printf("��������%d\n", result);
    } else {
        printf("������Ч�Ĳ��� %s\n", parameter);
        return 1;
    }

    return 0;
}

// ͳ���ַ���
int count_chars(char *filename) {
    FILE *fp;
    char line[MAX_LINE_LEN];
    int count = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("�����޷����ļ� %s\n", filename);
        exit(1);
    }

    while (fgets(line, MAX_LINE_LEN, fp) != NULL) {
        count += strlen(line);
    }

    fclose(fp);

    return count;
}

// ͳ�Ƶ�����
int count_words(char *filename) {
    FILE *fp;
    char line[MAX_LINE_LEN];
    char *word;
    int count = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("�����޷����ļ� %s\n", filename);
        exit(1);
    }

    while (fgets(line, MAX_LINE_LEN, fp) != NULL) {
        word = strtok(line, " ,\t\n"); // �Կո񡢶��š�ˮƽ�Ʊ���ͻ��з�Ϊ�ָ���
        while (word != NULL) {
            // �޸ģ���鵥���Ƿ��������ĸ�����ַ�
            int i;
            int valid_word = 1;
            for (i = 0; word[i] != '\0'; i++) {
                if (!isalnum(word[i])) {
                    valid_word = 0;
                    break;
                }
            }

            // ��һ���������������������Ҫ�޸�
            // ���磬���Կ��Ǵ������ַ�����д���ʻ���������ַ��ĵ���

            if (valid_word) {
                count++;
            }

            word = strtok(NULL, " ,\t\n");
        }
    }

    fclose(fp);

    return count;
}
