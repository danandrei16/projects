#include <stdio.h>

#include <string.h>

// associating a number to each color (working with numbers is easier)
void colorToInt(int a[3][3], int i, int j, char c[11]) {
    if (strcmp(c, "ros") == 0)
        a[i][j] = 1;
    if (strcmp(c, "gal") == 0)
        a[i][j] = 2;
    if (strcmp(c, "albs") == 0)
        a[i][j] = 3;
    if (strcmp(c, "vd") == 0)
        a[i][j] = 4;
    if (strcmp(c, "port") == 0)
        a[i][j] = 5;
    if (strcmp(c, "alb") == 0)
        a[i][j] = 6;
}

// builds matrix of a face of the cube
void matrix(int A[3][3]) {
    char linie[33], * p;
    int i;
    for (i = 0; i < 3; i++) {
        scanf("%s", linie); // input color1.color2.color3
        p = strtok(linie, "."); // color1
        colorToInt(A, i, 0, p);
        p = strtok(NULL, "."); // color2
        colorToInt(A, i, 1, p);
        p = strtok(NULL, "."); // color3
        colorToInt(A, i, 2, p);
    }
}

// rotating matrix clockwise/reverse clockwise
void rotate(int a[3][3], char sens[15]) {
    int aux;
    if (strcmp(sens, "invers") == 0) {
        aux = a[0][0];
        a[0][0] = a[2][0];
        a[2][0] = a[2][2];
        a[2][2] = a[0][2];
        a[0][2] = aux;
        aux = a[0][1];
        a[0][1] = a[1][0];
        a[1][0] = a[2][1];
        a[2][1] = a[1][2];
        a[1][2] = aux;
    }
    if (strcmp(sens, "ceasornic") == 0) {
        aux = a[0][0];
        a[0][0] = a[0][2];
        a[0][2] = a[2][2];
        a[2][2] = a[2][0];
        a[2][0] = aux;
        aux = a[0][1];
        a[0][1] = a[1][2];
        a[1][2] = a[2][1];
        a[2][1] = a[1][0];
        a[1][0] = aux;
    }
}

// makes a move in the cube
void move(char X[3], int Front[3][3], int Back[3][3], int Up[3][3], int Down[3][3], int Left[3][3], int Right[3][3]) {
    int i, aux;
    char sens[15];

    if (strlen(X) == 1) // clockwise move
        strcpy(sens, "ceasornic");
    else // reverse clockwise move
        strcpy(sens, "invers");

    for (i = 0; i < 3; i++) {
        if (strcmp(X, "U") == 0) {
            aux = Front[0][i];
            Front[0][i] = Right[0][i];
            Right[0][i] = Back[0][i];
            Back[0][i] = Left[0][i];
            Left[0][i] = aux;
            rotate(Up, sens);
        }
        if (strcmp(X, "U'") == 0) {
            aux = Front[0][i];
            Front[0][i] = Left[0][i];
            Left[0][i] = Back[0][i];
            Back[0][i] = Right[0][i];
            Right[0][i] = aux;
            rotate(Up, sens);
        }
        if (strcmp(X, "D") == 0) {
            aux = Front[2][i];
            Front[2][i] = Left[2][i];
            Left[2][i] = Back[2][i];
            Back[2][i] = Right[2][i];
            Right[2][i] = aux;
            rotate(Down, sens);
        }
        if (strcmp(X, "D'") == 0) {
            aux = Front[2][i];
            Front[2][i] = Right[2][i];
            Right[2][i] = Back[2][i];
            Back[2][i] = Left[2][i];
            Left[2][i] = aux;
            rotate(Down, sens);
        }
        if (strcmp(X, "R") == 0) {
            aux = Front[i][2];
            Front[i][2] = Down[i][2];
            Down[i][2] = Back[2 - i][0];
            Back[2 - i][0] = Up[i][2];
            Up[i][2] = aux;
            rotate(Right, sens);
        }
        if (strcmp(X, "R'") == 0) {
            aux = Front[i][2];
            Front[i][2] = Up[i][2];
            Up[i][2] = Back[2 - i][0];
            Back[2 - i][0] = Down[i][2];
            Down[i][2] = aux;
            rotate(Right, sens);
        }
        if (strcmp(X, "L") == 0) {
            aux = Front[i][0];
            Front[i][0] = Up[i][0];
            Up[i][0] = Back[2 - i][2];
            Back[2 - i][2] = Down[i][0];
            Down[i][0] = aux;
            rotate(Left, sens);
        }
        if (strcmp(X, "L'") == 0) {
            aux = Front[i][0];
            Front[i][0] = Down[i][0];
            Down[i][0] = Back[2 - i][2];
            Back[2 - i][2] = Up[i][0];
            Up[i][0] = aux;
            rotate(Left, sens);
        }
        if (strcmp(X, "F") == 0) {
            aux = Up[2][i];
            Up[2][i] = Left[2 - i][2];
            Left[2 - i][2] = Down[0][2 - i];
            Down[0][2 - i] = Right[i][0];
            Right[i][0] = aux;
            rotate(Front, sens);
        }
        if (strcmp(X, "F'") == 0) {
            aux = Up[2][i];
            Up[2][i] = Right[i][0];
            Right[i][0] = Down[0][2 - i];
            Down[0][2 - i] = Left[2 - i][2];
            Left[2 - i][2] = aux;
            rotate(Front, sens);
        }
        if (strcmp(X, "B") == 0) {
            aux = Up[0][i];
            Up[0][i] = Right[i][2];
            Right[i][2] = Down[2][2 - i];
            Down[2][2 - i] = Left[2 - i][0];
            Left[2 - i][0] = aux;
            rotate(Back, sens);
        }
        if (strcmp(X, "B'") == 0) {
            aux = Up[0][i];
            Up[0][i] = Left[2 - i][0];
            Left[2 - i][0] = Down[2][2 - i];
            Down[2][2 - i] = Right[i][2];
            Right[i][2] = aux;
            rotate(Back, sens);
        }
    }
}

// re-associating number with initial color to see the output
char * intToColor(int x) {
    if (x == 1)
        return "ros";
    if (x == 2)
        return "gal";
    if (x == 3)
        return "albs";
    if (x == 4)
        return "vd";
    if (x == 5)
        return "port";
    if (x == 6)
        return "alb";
    return 0;
}

// prints a face of the cube
void printFace(int A[3][3]) {
    int i;
    for (i = 0; i < 3; i++)
        printf("%s.%s.%s\n", intToColor(A[i][0]), intToColor(A[i][1]), intToColor(A[i][2]));
}

int main() {
    int i, m, Front[3][3], Back[3][3], Up[3][3], Down[3][3], Left[3][3], Right[3][3];
    char c[6], *p;

    // inputs 6 colors: by default should always be "ros gal albs vd port alb"
    for (i = 0; i < 6; i++)
        scanf("%s", c);
    
    // building the cube
    matrix(Front);
    matrix(Back);
    matrix(Up);
    matrix(Down);
    matrix(Left);
    matrix(Right);

    // number of moves
    scanf("%d", &m);
    char litera[3], sir[300] = "";

    for (i = 0; i < m; i++) {
        scanf("%s", litera); // inputs each move ex: F, L', etc.
        strcat(sir, litera);
        strcat(sir, " "); // building string with all moves
    }
    p = strtok(sir, " ");

    // making the moves
    while (p) {
        move(p, Front, Back, Up, Down, Left, Right);
        p = strtok(NULL, " ");
    }
    
    // printing the new cube after all moves
    printFace(Front);
    printFace(Back);
    printFace(Up);
    printFace(Down);
    printFace(Left);
    printFace(Right);
}
