#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct {
    float X;
    float Y;
} Ponto;


float AreaTriangulo(Ponto A, Ponto B, Ponto C) {
    float det = fabs(A.X * (B.Y - C.Y) + B.X * (C.Y - A.Y) + C.X * (A.Y - B.Y));
    return det / 2.0;
}


float AreaPoligono(Ponto *vertices, int numVertices) {
    float areaTotal = 0.0;
    int i;

    for (i = 1; i < numVertices - 1; i++) {
        areaTotal += AreaTriangulo(vertices[0], vertices[i], vertices[i + 1]);
    }

    return areaTotal;
}

int main() {
    FILE *file;
    int numVertices, i;
    float areaTotal;
    Ponto *vertices;

   
    file = fopen("vertices.txt", "r");
    if (file == NULL) {
        printf("Erro ao achar o arquivo.\n");
        return 1;
    }

    fscanf(file, "%d", &numVertices);
    printf("Numero de vertices: %d\n", numVertices);

    
    vertices = (Ponto*) malloc(numVertices * sizeof(Ponto));
    if (vertices == NULL) {
        printf("Erro ao alocar memoria.\n");
        fclose(file);
        return 1;
    }

    
    for (i = 0; i < numVertices; i++) {
        fscanf(file, "%f %f", &vertices[i].X, &vertices[i].Y);
        printf("Vertice %d: X = %.2f, Y = %.2f\n", i + 1, vertices[i].X, vertices[i].Y);
    }

   
    fclose(file);

    areaTotal = AreaPoligono(vertices, numVertices);

    
    printf("A área do polígono equivale a %.2f\n", areaTotal);

    
    free(vertices);

    return 0;
}
