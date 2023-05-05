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

    /*// 默认使用当前目录下的文件
    strcpy(filename, "./input.txt");

    // 检查命令行参数
    if (argc < 2 || argc > 3) {
        printf("用法: %s [-c | -w] [文件名]\n", argv[0]);
        return 1;
    }

    // 处理参数
    parameter = argv[1];
    if (argc == 3) {
        strcpy(filename, argv[2]);
    }*/

    // 检查命令行参数
    if (argc != 3) {
        printf("用法: %s [-c | -w] [文件名]\n", argv[0]);
        return 1;
    }

    // 处理参数
    parameter = argv[1];
    strcpy(filename, argv[2]);

    // 根据参数调用对应的函数
    if (strcmp(parameter, "-c") == 0) {
        result = count_chars(filename);
        printf("字符数：%d\n", result);
    } else if (strcmp(parameter, "-w") == 0) {
        result = count_words(filename);
        printf("单词数：%d\n", result);
    } else {
        printf("错误：无效的参数 %s\n", parameter);
        return 1;
    }

    return 0;
}

// 统计字符数
int count_chars(char *filename) {
    FILE *fp;
    char line[MAX_LINE_LEN];
    int count = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("错误：无法打开文件 %s\n", filename);
        exit(1);
    }

    while (fgets(line, MAX_LINE_LEN, fp) != NULL) {
        count += strlen(line);
    }

    fclose(fp);

    return count;
}

// 统计单词数
int count_words(char *filename) {
    FILE *fp;
    char line[MAX_LINE_LEN];
    char *word;
    int count = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("错误：无法打开文件 %s\n", filename);
        exit(1);
    }

    while (fgets(line, MAX_LINE_LEN, fp) != NULL) {
        word = strtok(line, " ,\t\n"); // 以空格、逗号、水平制表符和换行符为分隔符
        while (word != NULL) {
            count++;
            word = strtok(NULL, " ,\t\n");
        }
    }

    fclose(fp);

    return count;
}