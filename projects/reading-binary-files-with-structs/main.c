#include <stdio.h>
#include <stdlib.h>
#include "plane.h"

typedef struct node {
    Plane data;
    struct node* next;
} Node;

void printStructs(Node* head, FILE* textfile) {
    while (head != NULL) {
        fprintf(textfile, "Model: %s\n", head->data.model);
        fprintf(textfile, "Maximum Speed: %f\n", head->data.max_speed);
        fprintf(textfile, "Maximum Altitude: %f\n", head->data.max_alt);
        fprintf(textfile, "Passanger Capacity: %d\n", head->data.passanger_cap);
        fprintf(textfile, "Military: %s\n\n", head->data.is_military ? "Yes" : "No");
        head = head->next;
    }
}

int main(void) {
    FILE* file = fopen("planes.dat", "rb");
    if (file == NULL) {
        printf("Could not open file.\n");
        return 1;
    }

    Node* head = NULL;
    Node* tail = NULL;
    Plane temp;

    while (fread(&temp, sizeof(Plane), 1, file) == 1) {
        Node* new_node = malloc(sizeof(Node));
        new_node->data = temp;
        new_node->next = NULL;

        if (head == NULL)
            head = new_node;
        else
            tail->next = new_node;
        tail = new_node;
    }

    fclose(file);

    FILE* textfile = fopen("planes.txt", "w");
    printStructs(head, textfile);
    fclose(textfile);

    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
