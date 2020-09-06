#include <stdio.h>

#define SIZE 10

int* scan_num(char* name);
void print_num(int* num, char no);
int* Sort(int* sort_num, int size);
void Swap(int* a, int* b);


int main(int argc, char** argv)
{
    int* input;
    char no = argv[1][9];
    input = scan_num(argv[1]);
    int* result = Sort(input, SIZE);
    print_num(result, no);
}

int* scan_num(char* name)
{
    FILE* fp;
    fp = fopen(name, "r");
    static int input[SIZE];

    for (int i = 0; i < 10; i++)
    {
        fscanf(fp, "%d", &input[i]);
    }
    
    return input;
}

void print_num(int* num, char no)
{
    char filename[30] = "OutputData0.txt";
    filename[10] = no;
    FILE* fp = fopen(filename, "w");
    for (int i = 0; i < SIZE; i++)
    {
        fprintf(fp, "%d ", num[i]);
    }
}

int* Sort(int* sort_num, int size) {
    int i, j;
    for (i = 0; i < size - 1; i++)
        for (j = 0; j < size - 1; j++)
            if (sort_num[j] > sort_num[j + 1])
                Swap(&sort_num[j], &sort_num[j + 1]);

    return sort_num;
}

void Swap(int* a, int* b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}