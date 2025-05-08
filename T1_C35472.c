#include <stdio.h>

//funciones necesarias
int min(int arreglo[], int tamaño) {
    int min = arreglo[0];
    for (int i = 1; i < tamaño; i++) {
        if (arreglo[i] < min)
            min = arreglo[i];
    }
    return min;
}

int max(int arreglo[], int tamaño) {
    int max = arreglo[0];
    for (int i = 1; i < tamaño; i++) {
        if (arreglo[i] > max)
            max = arreglo[i];
    }
    return max;
}

void imprimir_matriz(int tamano, int matriz[tamano][tamano]) {
    for (int i = 0; i < tamano; i++) {           // Recorremos las filas
        for (int j = 0; j < tamano; j++) {       // Recorremos las columnas
            printf("%d ", matriz[i][j]);         // Imprimimos el elemento en la posición i,j
        }
        printf("\n");                            // cambiamos de línea al final de cada fila
    }
}


int revisar_archivo(char *archivo){
    char ch; //creamos una valiable para almacenar cada caracter del texto
    FILE *fptr = fopen( archivo , "r"); //abrimos el archivo en modo de lectura
//verificamos si la matriz es cuadrada y si solamente tiene ceros y unos
    int contador_numeros=0;
    int contador_saltos=0;
    while ((ch = fgetc(fptr)) != EOF) {//leemos el archivo caracter por caracter
        switch(ch){
            case '\n':
                contador_saltos++;
                break;
            case '1':
            case '0':                            
                contador_numeros++;
                break;
            case ' ':
                break;//no hace nada
            default:
                printf("Error: la matriz no es binaria\n");
                fclose(fptr); //cerramos el archivo
                return 0; //salimos del programa
        }       
    }
    //este bloque if revisa si la matriz no es cuadrada
    if (((contador_saltos)*(contador_saltos))==contador_numeros){ //si los saltos(las lineas) es la raiz cuadrada de la cantidad de numeros, la matriz es cuadrada
        printf("la matriz es cuadrada\n");
    }
    else{
        printf("Error: la matriz no es cuadrada\n");
        fclose(fptr); //cerramos el archivo
        return 0; //salimos del programa
    }
    fclose(fptr); //cerramos el archivo
    return contador_saltos; //retornamos el tamaño de la matriz, si todo sale bien
    
}
void crear_matriz( int tamano,int matriz[tamano][tamano], char *archivo ){
    char ch; //creamos una valiable para almacenar cada caracter del texto
    FILE *fptr = fopen( archivo , "r"); //abrimos el archivo en modo de lectura
    
    int indice_matriz_fila=0;
    int indice_matriz_columna=0;
    while ((ch = fgetc(fptr)) != EOF) {//leemos el archivo caracter por caracter
        if (ch == '0' || ch == '1') {
            matriz[indice_matriz_fila][indice_matriz_columna] = ch - '0'; // Convertimos de caracter a nnmero

            indice_matriz_columna++;
            if (indice_matriz_columna == tamano) {
                indice_matriz_columna = 0;
                indice_matriz_fila++;
                if (indice_matriz_fila == tamano) break; // si ya llenamos toda la matriz
            }
        }
    }
            // Si es espacio, salto de línea u otro caracter permitido, lo ignoramos
fclose(fptr); //cerramos el archivo
}


int encontrar_diagonal_mas_larga(int tamano,int matriz[tamano][tamano]) {
// reutilizamos  codigo del ejercicio 2 para organizar la matriz por diagonales
int celdas[2][100];//creamos una matriz donde la fila 0 corresponde al valor de una casilla y la fila 1 al numero de diagonal de tipo A y la fila 2 será el numero de tipo B 
    //recorrer la matriz por diagonales y clasificar valores
    int contador_celdas = 0;
    for (int fila=0; fila<tamano ;fila++){
        for(int columna=0; columna<tamano;columna++){ //recorremos la matriz
            //para separar las diagonales, vamos a seguir dos criterios
            int tipoB=fila+columna;//las diagonales que van de izquierda-abajo a derecha-arriba, se cuentan en la misma diagonal las que si se suma filas+columnas, da el mismo resultado; estas serán de tipo B
            int valor= matriz[fila][columna];//tomamos el valor guardado en la matriz
            //guardamos en celdas, la informacion
            celdas[0][contador_celdas] = valor;
            celdas[1][contador_celdas] = tipoB;
            contador_celdas++;
}
}
//al terminar con esto nos queda una matriz que anota el orden para recorrer las celdas por diagonales
//reccorremos nuevamente la matriz en este orden
    int secuencia=0;//esta lleva la cuenta de unos
    int secuencia_max=0;//esta guarda la cuenta más grande registrada

    int minimo=min(celdas[1], contador_celdas);//para ambos recorridos, encontramos el menor y el mayor para conocer el orden para recorrerlos
    int maximo=max(celdas[1], contador_celdas);//esto funciona porque los numeros de diagonal terminan siguiendo una secuencia creciente para ambos casos


    for (int diagonal=minimo; diagonal<=maximo; diagonal++){//en orden de numero de diagonal, evaluamos si el valor guardado es uno o cero
        for (int indice=0;indice<contador_celdas;indice++){//recorremos la matriz celdas
            if (celdas[1][indice]==diagonal){ //si encontramos un elemento con el numero de tipo que estamos buscando lo evaluamos
                if(celdas[0][indice]==1){
                secuencia+=1; //si el elemento es uno, aumentamos la secuencia
                    if (secuencia>secuencia_max){
                        secuencia_max=secuencia;//si la cuenta supera a la mayor encontrada, la actualizamos
                    }
                }
                else{
                    secuencia=0;//si el elemento es cero, la secuencia se reinicia
                }

            }
            

        }
       
    }
    //al terminar, guardamos la secuencia para comparar la mas larga de los dos recorridos
    return secuencia_max;
}

int main() {
    char archivo[]="/home/aaron/Escritorio/progra/tarea1/matriz3x3"; //aislamos la direccion del archivo para modificarla mas facil
    int tamano=revisar_archivo(archivo);
    if (tamano!=0){//si tenemos un tamaño mayor a cero, se puede crear una matriz cuadrada binaria
        //aqui va la funcion de creacion de matriz
        int matriz[tamano][tamano];
        crear_matriz(tamano, matriz, archivo);
        imprimir_matriz(tamano , matriz);
        int diagonal_mas_larga = encontrar_diagonal_mas_larga(tamano, matriz);
        printf("La secuencia de 1s más grande es: %d\n", diagonal_mas_larga);
    }
    else{
        return 1;//si no se pasa la verificacion, salimos del programa
    }

return 0;
}















