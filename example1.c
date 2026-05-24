#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct Graph {
    int total_vertices;
    int *visited_array;
    struct Node **adjacency_lists;
} GPH;

typedef struct Stack {
    int top_index;
    int max_capacity;
    int *items_array;
} STK;

// Creează un nod nou în lista de adiacență
NODE *create_node(int vertex_value) {
    NODE *new_node = (NODE *)malloc(sizeof(NODE));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = vertex_value;
    new_node->next = NULL;
    
    return new_node;
}

// Creează structura grafului
GPH *create_graph(int total_vertices) {
    GPH *graph = (GPH *)malloc(sizeof(GPH));
    if (graph == NULL) {
        return NULL;
    }
    
    graph->total_vertices = total_vertices;
    graph->adjacency_lists = (NODE **)malloc(total_vertices * sizeof(NODE *));
    graph->visited_array = (int *)malloc(total_vertices * sizeof(int));

    for (int i = 0; i < total_vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited_array[i] = 0;
    }
    
    return graph;
}

// Adaugă o muchie neorientată în graf
void add_edge(GPH *graph, int source_vertex, int destination_vertex) {
    // Adaugă destinația în lista sursei
    NODE *new_node = create_node(destination_vertex);
    new_node->next = graph->adjacency_lists[source_vertex];
    graph->adjacency_lists[source_vertex] = new_node;

    // Adaugă sursa în lista destinației (graf neorientat)
    new_node = create_node(source_vertex);
    new_node->next = graph->adjacency_lists[destination_vertex];
    graph->adjacency_lists[destination_vertex] = new_node;
}

// Inserează muchiile citite de la tastatură
void insert_edges(GPH *graph, int edges_count, int total_vertices) {
    int source_vertex, destination_vertex;
    
    printf("Introduceti %d muchii (valori de la 0 la %d):\n", edges_count, total_vertices - 1);
    for (int i = 0; i < edges_count; i++) {
        if (scanf("%d %d", &source_vertex, &destination_vertex) == 2) {
            add_edge(graph, source_vertex, destination_vertex);
        }
    }
}

// Verifică dacă există conexiune directă (muchie) între două restaurante
void check_direct_path(GPH *graph, int start_restaurant, int end_restaurant) {
    NODE *temp = graph->adjacency_lists[start_restaurant];
    int path_exists = 0;

    while (temp != NULL) {
        if (temp->data == end_restaurant) {
            path_exists = 1;
            break;
        }
        temp = temp->next;
    }

    if (path_exists) {
        printf("Exista drum direct intre restaurantul %d si restaurantul %d.\n", start_restaurant, end_restaurant);
    } else {
        printf("NU exista drum direct intre restaurantul %d si restaurantul %d.\n", start_restaurant, end_restaurant);
    }
}

int main(void) {
    int total_vertices;
    int edges_count;
    int start_restaurant, end_restaurant;

    printf("Cate restaurante are reteaua (noduri)?: ");
    if (scanf("%d", &total_vertices) != 1) return 1;

    printf("Cate conexiuni exista (muchii)?: ");
    if (scanf("%d", &edges_count) != 1) return 1;

    GPH *graph = create_graph(total_vertices);
    if (graph == NULL) return 1;

    insert_edges(graph, edges_count, total_vertices);

    printf("\nIntroduceti cele doua restaurante de verificat: ");
    if (scanf("%d %d", &start_restaurant, &end_restaurant) == 2) {
        check_direct_path(graph, start_restaurant, end_restaurant);
    }

    // Eliberare memorie (Good Practice)
    free(graph->visited_array);
    for (int i = 0; i < total_vertices; i++) {
        NODE *temp = graph->adjacency_lists[i];
        while (temp != NULL) {
            NODE *aux = temp;
            temp = temp->next;
            free(aux);
        }
    }
    free(graph->adjacency_lists);
    free(graph);

    return 0;
}
