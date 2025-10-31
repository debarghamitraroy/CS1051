#include <arpa/inet.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080

typedef struct {
    char name;
    double value;
} Variable;

double get_value(char var, Variable *vars, int count) {
    for (int i = 0; i < count; i++) {
        if (vars[i].name == var)
            return vars[i].value;
    }
    printf("Unknown variable: %c\n", var);
    return 0;
}

double evaluate_expression(char *expr, Variable *vars, int count) {
    double stack[100];
    char ops[100];
    int sp = 0, op_sp = 0;
    for (int i = 0; i < strlen(expr); i++) {
        char c = expr[i];
        if (isspace(c))
            continue;
        if (isalpha(c))
            stack[sp++] = get_value(c, vars, count);
        else if (c == '+' || c == '-' || c == '*' || c == '/')
            ops[op_sp++] = c;
    }
    for (int i = 0; i < op_sp; i++) {
        if (ops[i] == '*' || ops[i] == '/') {
            double a = stack[i];
            double b = stack[i + 1];
            stack[i] = (ops[i] == '*') ? a * b : a / b;
            for (int j = i + 1; j < sp - 1; j++)
                stack[j] = stack[j + 1];
            sp--;
            for (int j = i; j < op_sp - 1; j++)
                ops[j] = ops[j + 1];
            op_sp--;
            i--;
        }
    }
    double result = stack[0];
    for (int i = 0; i < op_sp; i++) {
        if (ops[i] == '+')
            result += stack[i + 1];
        else if (ops[i] == '-')
            result -= stack[i + 1];
    }
    return result;
}

int parse_variables(char *str, Variable *vars) {
    int count = 0;
    char *token = strtok(str, ",");
    while (token) {
        char var;
        double val;
        if (sscanf(token, " %c=%lf", &var, &val) == 2) {
            vars[count].name = var;
            vars[count].value = val;
            count++;
        }
        token = strtok(NULL, ",");
    }
    return count;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[1024];
    int addrlen = sizeof(address);
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    listen(server_fd, 3);
    printf("Server listening on port %d\n", PORT);
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("accept error");
        exit(EXIT_FAILURE);
    }
    read(new_socket, buffer, sizeof(buffer));
    char expr[100], vars_str[200];
    sscanf(buffer, "%[^;];%s", expr, vars_str);
    printf("Expression: %s\n", expr);
    printf("Variables: %s\n", vars_str);
    Variable vars[20];
    int count = parse_variables(vars_str, vars);
    double result = evaluate_expression(expr, vars, count);
    printf("Result: %.2f\n", result);
    char result_str[50];
    sprintf(result_str, "%.2f", result);
    send(new_socket, result_str, strlen(result_str), 0);
    close(new_socket);
    close(server_fd);
    return 0;
}
