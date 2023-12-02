#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

typedef enum {
    NOT_VALID,
    LABEL,
    INST
} line_type;

uint8_t label_table[32];

int file_line_count = 0;
char *file_asm;

uint16_t adler16(char *s, size_t size) {
    uint16_t hsh = 0;
    for (int i = 0; i < size; ++i) {
        if (i == 0) {
            hsh += s[i] * i + 1;
        }
        else {
            hsh += s[i] * i + s[i-1];
        }
    }
    return hsh;
}

bool check_stray_chars(char *line) {
    while (*line != '\0') {
        if (isalpha(*line)) {
            printf("%s\n", line);
            return true;
        }
        line++;
    }
    return false;
}


char *trim_leading_spaces(char *line, const size_t size) {
    while (isspace(*line)) {
        line++;
    }
    return line;
}

#define log_log() fprintf(stderr, "log_log: %d:", __line__)

line_type parse_line(char *line, const size_t size, const int current_addr) {
    char label_temp[256];

    char inst_temp[3];
    if (!isalpha(line[0]) && line[0] != '_') {
        return NOT_VALID;
    }
    for (int i = 0; i < size; ++i) {
        if (line[i] == ':') {
            if (check_stray_chars(line+i+1)) {
                return NOT_VALID;
            }
            memcpy(label_temp, line, i);
            printf("line: %s", line);
            printf("label is: %s\n", label_temp);
            label_table[adler16(label_temp,i)] = current_addr;
            return LABEL;
        }
        else if (isspace(line[i])) {
            memcpy(inst_temp, line, i-1);
            printf("inst is: %s\n", label_temp);
            return INST;
        }
    }
}

void log_err(const char *fmt, ...) {
    fprintf(stderr, "%s:%d: ", file_asm, file_line_count);
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fprintf(stderr, "\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        perror("Too few arguments!");
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }
    file_asm = argv[1];

    char *line = NULL;
    size_t linecap;

    int ret = 0;
    int address_counter = 0;
    while ((ret = getline(&line, &linecap, fp)) != -1) {
        file_line_count++;
        char *line_cp = trim_leading_spaces(line, ret);
        if (line_cp[0] == '\0') {
            continue;
        }
        int type = parse_line(line_cp, ret - (line - line_cp), address_counter);
        if (type == NOT_VALID) {
            log_err("Syntax error");
        }
        else if (type == INST) {
            address_counter++;
        }
        printf("%s", line);
    }
}
