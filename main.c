#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void atr(char line[])
{
	char *p = strtok(line, " ");
	char reg = p[0];

	p = strtok(NULL, " ");
	p = strtok(NULL, " ");

	if (p[0] >= 'a' && p[0] <= 'd')
		printf("MOV e%cx, e%cx\n", reg, p[0]);
	else
		printf("MOV e%cx, %d\n", reg, atoi(p));
}

void op(char line[])
{
	char *p = strtok(line, " ");
	char reg = p[0], semn;

	p = strtok(NULL, " ");
	p = strtok(NULL, " ");
	p = strtok(NULL, " ");
	semn = p[0];
	p = strtok(NULL, " ");

	if (semn == '&') {
		printf("AND e%cx, ", reg);
		if (p[0] >= '0' && p[0] <= '9')
			printf("%d\n", atoi(p));
		else
			printf("e%cx\n", p[0]);
	} else if (semn == '^') {
		printf("XOR e%cx, ", reg);
		if (p[0] >= '0' && p[0] <= '9')
			printf("%d\n", atoi(p));
		else
			printf("e%cx\n", p[0]);
	} else if (semn == '|') {
		printf("OR e%cx, ", reg);
		if (p[0] >= '0' && p[0] <= '9')
			printf("%d\n", atoi(p));
		else
			printf("e%cx\n", p[0]);
	} else if (semn == '+') {
		printf("ADD e%cx, ", reg);
		if (p[0] >= '0' && p[0] <= '9')
			printf("%d\n", atoi(p));
		else
			printf("e%cx\n", p[0]);
	} else if (semn == '-') {
		printf("SUB e%cx, ", reg);
		if (p[0] >= '0' && p[0] <= '9')
			printf("%d\n", atoi(p));
		else
			printf("e%cx\n", p[0]);
	} else if (semn == '>') {
		printf("SHR e%cx, %d\n", reg, atoi(p));
	} else if (semn == '<') {
		printf("SHL e%cx, %d\n", reg, atoi(p));
	} else if (semn == '*') {
		if (reg == 'a')
			printf("MUL %d\n", atoi(p));
		if (reg == 'b' || reg == 'c' || reg == 'd') {
			printf("MOV eax, e%cx\n", reg);
			if (p[0] >= '0' && p[0] <= '9')
				printf("MUL %d\n", atoi(p));
			else
				printf("MUL e%cx\n", p[0]);
			printf("MOV e%cx, eax\n", reg);
		}
	} else if (semn == '/') {
		if (p[0] == '0') {
			printf("Error\n");
			//error
		} else {
			if (reg == 'a')
				printf("DIV %d\n", atoi(p));
			if (reg == 'b' || reg == 'c' || reg == 'd') {
				printf("MOV eax, e%cx\n", reg);
				if (p[0] >= '0' && p[0] <= '9')
					printf("DIV %d\n", atoi(p));
				else
					printf("DIV e%cx\n", p[0]);
				printf("MOV e%cx, eax\n", reg);
			}
		}
	}
}

void daca(char line[])
{
	char *p = strtok(line, " ");
	p = strtok(NULL, " ");
	char reg = p[1];
	p = strtok(NULL, " ");
	char *semn = p;
	p = strtok(NULL, " ");
	int val = atoi(p);

	printf("CMP e%cx, %d\n", reg, val);
	if (strlen(semn) == 1) {
		if (semn[0] == '<')
			printf("JGE end_label\n");
		else if (semn[0] == '>')
			printf("JLE end_label\n");
	} else if (strlen(semn) == 2) {
		if (semn[0] == '>' && semn[1] == '=')
			printf("JL end_label\n");
		else if (semn[0] == '<' && semn[1] == '=')
			printf("JG end_label\n");
		else if (semn[0] == '=' && semn[1] == '=')
			printf("JNE end_label\n");
	}

	char new_line[256];
	while (fgets(new_line, sizeof(new_line), stdin)) {
		if (new_line[0] == '}')
			break;
		int cnt = 0, x = strlen(new_line);
		for (int i = 0; i < x; ++i)
			if (new_line[i] == ' ')
				++cnt;
		if (cnt == 2)
			atr(new_line + 1);
		else
			op(new_line + 1);
	}
	printf("end_label:\n");
}

void pentru(char line[])
{
	char *p = strtok(line, " ");
	p = strtok(NULL, " ");
	char reg = p[1];
	p = strtok(NULL, " ");
	p = strtok(NULL, " ");
	p = strtok(NULL, " ");
	p = strtok(NULL, " ");
	char *semn = p;
	p = strtok(NULL, " ");
	int val = atoi(p);

	printf("MOV e%cx, 0\n", reg);
	printf("start_loop:\n");
	printf("CMP e%cx, %d\n", reg, val);

	if (strlen(semn) == 1)
		printf("JGE end_label\n");
	else if (strlen(semn) == 2)
		printf("JG end_label\n");

	char new_line[256];
	while (fgets(new_line, sizeof(new_line), stdin)) {
		if (new_line[0] == '}')
			break;
		int cnt = 0, x = strlen(new_line);
		for (int i = 0; i < x; ++i)
			if (new_line[i] == ' ')
				++cnt;
		if (cnt == 2)
			atr(new_line + 1);
		else
			op(new_line + 1);
	}

	printf("ADD e%cx, 1\n", reg);
	printf("JMP start_loop\n");
	printf("end_loop:\n");
}

void cattimp(char line[])
{
	char *p = strtok(line, " ");
	p = strtok(NULL, " ");
	char reg = p[1];
	p = strtok(NULL, " ");
	char *semn = p;
	p = strtok(NULL, " ");
	int val = atoi(p);

	printf("start_loop:\n");
	printf("CMP e%cx, %d\n", reg, val);
	if (strlen(semn) == 1) {
		if (semn[0] == '>')
			printf("JLE end_label\n");
		else if (semn[0] == '<')
			printf("JGE end_label\n");
	} else if (strlen(semn) == 2) {
		if (semn[0] == '>' && semn[1] == '=')
			printf("JL end_label\n");
		else if (semn[0] == '<' && semn[1] == '=')
			printf("JG end_label\n");
		else if (semn[0] == '=' && semn[1] == '=')
			printf("JNE end_label\n");
	}

	char new_line[256];
	while (fgets(new_line, sizeof(new_line), stdin)) {
		if (new_line[0] == '}')
			break;
		int cnt = 0, x = strlen(new_line);
		for (int i = 0; i < x; ++i)
			if (new_line[i] == ' ')
				++cnt;
		if (cnt == 2)
			atr(new_line + 1);
		else
			op(new_line + 1);
	}

	printf("JMP start_loop\n");
	printf("end_label:\n");
}

int main(void)
{
	char line[256];
	while (fgets(line, sizeof(line), stdin)) {
		if (line[0] >= 'a' && line[0] <= 'd') {
			int cnt = 0, x = strlen(line);
			for (int i = 0; i < x; ++i)
				if (line[i] == ' ')
					++cnt;
			if (cnt == 2)
				atr(line);
			else
				op(line);
		} else if (line[0] == 'i') {
			daca(line);
		} else if (line[0] == 'f') {
			pentru(line);
		} else if (line[0] == 'w') {
			cattimp(line);
		}
	}

	return 0;
}
