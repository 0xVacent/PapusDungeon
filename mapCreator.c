#include "mapCreator.h"
#include "color.h"

char archivoMapas[20] = "mapas.dat";

void iniciarCreador(){

    GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);
    hwndFound=FindWindow(NULL, pszOldWindowTitle);
    char mapa[28][96];
    indicator cursor;
    cursor.indicatorY = cursorPos.y/16 - 1;
    cursor.indicatorX = cursorPos.x/8 - 1;

    memset(mapa, 219, sizeof(mapa));

    char eleccion='j';
while(eleccion !='c' && eleccion!='v')
    {

    printf("\n Ingrese c para cargar un mapa o v para ver el archivo\n");
    fflush(stdin);
    scanf("%c", &eleccion);


        printf("INCORRECTO, ingrese c o v porfavor");
    }

    if(eleccion == 'c'){
    for(;;){

    system("");
    estrucuraBasica(mapa);
    indicador(mapa, &cursor);
    printf("\x1b[H");
    mostrarMapa(mapa, &cursor);

    if((cursorPos.y/16 - 1) > 0 && (cursorPos.x/8 - 1) > 0 && (cursorPos.y/16 - 1) < 28 && (cursorPos.x/8 - 1) < 96){

    cursor.indicatorY = cursorPos.y/16 - 1;
    cursor.indicatorX = cursorPos.x/8 - 1;

    }else{
    cursor.indicatorY = cursor.indicatorY;
    cursor.indicatorX = cursor.indicatorX;
    }
    }

    }else if(eleccion == 'v'){
    leerArchivo();
    system("pause");
    }
}


void fixMapa(char mapa[fil][col]){
    int i, j;
    for(i = 0; i<fil;i++){
        for(j = 0; j<col; j++){
            if(mapa[i][j] == -37){
                mapa[i][j] = ' ';
            }
        }
    }
}

void estrucuraBasica(char mapa[fil][col]){

        int i,j;
 //PAREDES BORDER NO BORRAR BAJO NINGUNA SIRCUNSTANCIA :3
    for(i = 0; i < fil; i++){
        for(j = 0; j<2; j++){
            mapa[i][j] = '#';
        }
    }
    for(i = 0; i < fil; i++){
        for(j = col - 2; j<col; j++){
            mapa[i][j] = '#';
        }
    }
    for(i = fil - 2; i < fil; i++){
        for(j = 0; j<col; j++){
            mapa[i][j] = '#';
        }
    }
    for(i = 0; i < 2; i++){
        for(j = 0; j<col; j++){
            mapa[i][j] = '#';
        }
    }

}

void mostrarMapa(char mapa[fil][col], indicator * cursor){
    int i, j;

    printf("%c------------------------------------------------------------------------------------------------%c\n",219, 191);

    for(i = 0; i<fil; i++){
        printf("|");

        for(j = 0; j<col; j++){
        if(i == cursor->indicatorY && j == cursor->indicatorX){
            printf(RED"%c", mapa[i][j]);
        }else{
            printf(BWHT"%c", mapa[i][j]);
        }
        }
        printf("|\n");

    }
    printf("%c------------------------------------------------------------------------------------------------%c\n", 192, 217);

    printf("C o Click Izquierdo para escribir\n");
    printf("X  o Shift + Click Izqueirdo para borrar\n");
    printf("R para borrar TODO\n");
    printf("G para guardar en el archivo\n");

    GetCursorPos(&cursorPos);
    ScreenToClient(hwndFound, &cursorPos);

}

void indicador(char mapa[fil][col], indicator * cursor){


    if(GetKeyState('W') & 0x8000){
     cursor->indicatorY = cursor->indicatorY - 1;
    }
    if(GetKeyState('S') & 0x8000){
     cursor->indicatorY = cursor->indicatorY + 1;

    }
    if(GetKeyState('A') & 0x8000){
     cursor->indicatorX = cursor->indicatorX - 1;
    }
    if(GetKeyState('D') & 0x8000){
     cursor->indicatorX = cursor->indicatorX + 1;
    }
    mapa[cursor->indicatorY][cursor->indicatorX] = mapa[cursor->indicatorY][cursor->indicatorX];

    if(GetKeyState('C') & 0x8000){

        mapa[cursor->indicatorY][cursor->indicatorX] = '#';

    }
    if(GetAsyncKeyState(VK_LBUTTON)){

        mapa[cursor->indicatorY][cursor->indicatorX] = '#';

    }
    if(GetAsyncKeyState(VK_LSHIFT)){
        if(GetAsyncKeyState(VK_LBUTTON)){

        mapa[cursor->indicatorY][cursor->indicatorX] = 219;

    }
    }

    if(GetKeyState('X') & 0x8000){

        mapa[cursor->indicatorY][cursor->indicatorX] = 219;

    }if(GetKeyState('R') & 0x8000){
        memset(mapa, 219, fil*col);
    }
    if(GetKeyState('G') & 0x8000){
        infoArchivo(mapa);
        exit(0);
    }

}

void infoArchivo(char mapa[fil][col]){
    FILE * archi = fopen(archivoMapas, "a");
    char nivel;
    system("cls");
    system("pause");
    if(archi){

        printf("A que nivel pertenece el mapa?\n");
        fflush(stdin);
        scanf("%c", &nivel);

        mapa[0][0] = nivel;
        fixMapa(mapa);

        fwrite(mapa, fil*col, 1, archi);

        fclose(archi);
    }

}

void leerArchivo(){
    FILE * archi = fopen(archivoMapas, "r");

    char mapaAux[fil][col];

    if(archi){
        while(!feof(archi)){
        fread(&mapaAux, fil*col, 1, archi);
            if(!feof(archi)){
                printearMapa(mapaAux);
            }
        }
        fclose(archi);
    }
}

