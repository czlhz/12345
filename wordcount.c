#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 函数声明
void count_characters(const char *filename);
void count_words(const char *filename);
void print_usage(const char *program_name);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        print_usage(argv[0]);
        return 1;
    }

    const char *parameter = argv[1];
    const char *filename = argv[2];

    if (strcmp(parameter, "-c") == 0) {
        count_characters(filename);
    } else if (strcmp(parameter, "-w") == 0) {
        count_words(filename);
    } else {
        print_usage(argv[0]);
        return 1;
    }

    return 0;
}

// 统计字符数
void count_characters(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    int char_count = 0;
    int c;

    while ((c = fgetc(file)) != EOF) {
        char_count++;
    }

    fclose(file);
    printf("the number of char:%d\n", char_count);
}

// 统计单词数
void count_words(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    int word_count = 0;
    int c;
    int in_word = 0;

    while ((c = fgetc(file)) != EOF) {
        if (isspace(c) || c == ',') {
            if (in_word) {
                word_count++;
                in_word = 0;
            }
        } else {
            in_word = 1;
        }
    }

    // 如果文件以单词结尾
    if (in_word) {
        word_count++;
    }

    fclose(file);
    printf("the number of word:%d\n", word_count);
}

// 打印使用方法
void print_usage(const char *program_name) {
    printf("Usage: %s [parameter] [input_file_name]\n", program_name);
    printf("Parameters:\n");
    printf("  -c    Count characters\n");
    printf("  -w    Count words\n");
}

