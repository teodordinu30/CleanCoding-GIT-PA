// Rezolvare Laborator Clean Code
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct Graph {
    int vertices_count;
    int *visited_array;
    struct Node **adjacency_lists;
} GPH;

// Creează un nod nou pentru listele grafului sau coadă
NODE *create_node(int vertex_value) {
    NODE *new_node = (NODE *)malloc(sizeof(NODE));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = vertex_value;
    new_node->next = NULL;
    
    return new_node;
}

// Creează și inițializează graful
GPH *create_graph(int vertices_count) {
    GPH *graph = (GPH *)malloc(sizeof(GPH));
    if (graph == NULL) {
        return NULL;
    }
    
    graph->vertices_count = vertices_count;
    graph->adjacency_lists = (NODE **)malloc(vertices_count * sizeof(NODE *));
    graph->visited_array = (int *)malloc(vertices_count * sizeof(int));

    for (int i = 0; i < vertices_count; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited_array[i] = 0;
    }
    
    return graph;
}

// Adaugă o muchie neorientată în graf
void add_edge(GPH *graph, int source, int destination) {
    NODE *new_node = create_node(destination);
    new_node->next = graph->adjacency_lists[source];
    graph->adjacency_lists[source] = new_node;

    new_node = create_node(source);
    new_node->next = graph->adjacency_lists[destination];
    graph->adjacency_lists[destination] = new_node;
}

// Citirea și inserarea muchiilor
void insert_edges(int vertices_count, int edges_count, GPH *graph) {
    int source, destination;
    
    printf("Adauga %d muchii (valori de la 0 la %d):\n", edges_count, vertices_count - 1);
    for (int i = 0; i < edges_count; i++) {
        if (scanf("%d %d", &source, &destination) == 2) {
            add_edge(graph, source, destination);
        }
    }
}

// Helperi pentru Coadă (folosită la BFS)
int is_empty(NODE *queue) {
    return queue == NULL;
}

void enqueue(NODE **queue, int value) {
    NODE *new_node = create_node(value);
    if (is_empty(*queue)) {
        *queue = new_node;
    } else {
        NODE *temp = *queue;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(NODE **queue) {
    if (is_empty(*queue)) {
        return -1;
    }
    NODE *temp = *queue;
    int value = temp->data;
    *queue = (*queue)->next;
    free(temp);
    
    return value;
}

// Resetează vectorul de vizitare pentru a putea rula ambele parcurgeri
void wipe_visited_list(GPH *graph, int vertices_count) {
    for (int i = 0; i < vertices_count; i++) {
        graph->visited_array[i] = 0;
    }
}

// Parcurgerea în Adâncime (DFS)
void DFS(GPH *graph, int vertex_nr) {
    NODE *temp = graph->adjacency_lists[vertex_nr];
    
    graph->visited_array[vertex_nr] = 1;
    printf("%d ", vertex_nr);

    while (temp != NULL) {
        int connected_vertex = temp->data;
        if (graph->visited_array[connected_vertex] == 0) {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

// Parcurgerea în Lățime (BFS)
void BFS(GPH *graph, int start_vertex) {
    NODE *queue = NULL;

    graph->visited_array[start_vertex] = 1;
    enqueue(&queue, start_vertex);

    while (!is_empty(queue)) {
        int current_vertex = dequeue(&queue);
        printf("%d ", current_vertex);

        NODE *temp = graph->adjacency_lists[current_vertex];
        while (temp != NULL) {
            int adj_vertex = temp->data;
            if (graph->visited_array[adj_vertex] == 0) {
                graph->visited_array[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

int main(void) {
    int vertices_count;
    int edges_count;
    int starting_vertex;

    printf("Cate noduri are graful?: ");
    if (scanf("%d", &vertices_count) != 1) return 1;

    printf("Cate muchii are graful?: ");
    if (scanf("%d", &edges_count) != 1) return 1;

    GPH *graph = create_graph(vertices_count);
    if (graph == NULL) return 1;

    insert_edges(vertices_count, edges_count, graph);

    printf("\nDe unde plecam in DFS?: ");
    if (scanf("%d", &starting_vertex) == 1) {
        printf("Parcurgere cu DFS: ");
        DFS(graph, starting_vertex);
        printf("\n");
    }

    wipe_visited_list(graph, vertices_count);

    printf("De unde plecam in BFS?: ");
    if (scanf("%d", &starting_vertex) == 1) {
        printf("Parcurgere cu BFS: ");
        BFS(graph, starting_vertex);
        printf("\n");
    }

    return 0;
}
