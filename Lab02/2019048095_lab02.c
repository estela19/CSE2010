#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int ID;
    char* Name;
} Student;

typedef struct {
    int cnt;
    Student student[10];
} Students;

Students students = { 5,
{{2020200001, "test person 1"},
{2020200765, "test person 2"},
{2020300004, "test person 3"},
{2020200628, "test person 4"},
{2020200218, "test person 5"},
}};

typedef struct {
    Student data;
    struct Node* next;
}Node;

typedef struct {
    Node* Head;
    Node* Cur;
    Node* Tail;
    int cnt;
}List;

void Insert(List* list, Student student);
void Delete(List* list, int key);
void Print(List* list);

int main() {
    List linkedlist = { NULL, NULL, NULL, 0 };
    List* plist = &linkedlist;
    Insert(plist, students.student[0]);
    Insert(plist, students.student[1]);
    Insert(plist, students.student[2]);
    Insert(plist, students.student[3]);
    Insert(plist, students.student[4]);

    Print(plist);
    Delete(plist, 2020200628);
    Print(plist);
}

void Insert(List* list, Student student) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = student;
    temp->next = NULL;

    list->Cur = list->Head;
    if (list->cnt == 0) {
        list->Head = temp;
        list->cnt++;
        return;
    }

    Node* prev = list->Cur;
    while (list->Cur->data.ID < temp->data.ID) {
        prev = list->Cur;
        list->Cur = list->Cur->next;
        if (list->Cur == NULL) {
            prev->next = temp;
            temp->next = NULL;
            list->cnt++;
            return;
        }
    }
    prev->next = temp;
    temp->next = list->Cur;
    list->cnt++;
}

void Delete(List* list, int key) {
    printf("Delete student node ID = %d\n\n", key);
    list->Cur = list->Head;
    Node* prev = list->Cur;
    while (list->Cur->data.ID != key) {
        prev = list->Cur;
        list->Cur = list->Cur->next;
    }
    prev->next = list->Cur->next;
    list->cnt--;
}

void Print(List* list) {
    list->Cur = list->Head;
    printf("Num of datas %d\n", list->cnt);
    while (list->Cur != NULL) {
        printf("ID : %d, Name : %s\n", list->Cur->data.ID, list->Cur->data.Name);
        list->Cur = list->Cur->next;
    }
    printf("\n");
}