#include "libUsuario.h"

void cargarArchivoJugadores(char nombreArchivo[],puntuacionJugador persona)
{
    FILE* archi=fopen(nombreArchivo,"ab");
    if(archi)
    {
        fwrite(&persona,sizeof(persona),1,archi);
        fclose(archi);
    }
}

int buscaJugadorEnArchivo(char nombreArchivo[],puntuacionJugador persona)
{
    FILE* archi=fopen(nombreArchivo,"rb");
    int busq=0;
    puntuacionJugador aux;
    if(archi)
    {
        while(fread(&aux,sizeof(puntuacionJugador),1,archi)>0)
        {
            if(aux.id==persona.id)
                busq=1;
        }
        fclose(archi);
    }

    return busq;
}

nodoArbol* crearNodoArbol(puntuacionJugador dato)
{
    nodoArbol* aux= (nodoArbol*) malloc(sizeof(nodoArbol));

    aux->dato=dato;
    aux->izq=NULL;
    aux->der=NULL;

    return aux;
}

nodoArbol* insertarNodoArbol(nodoArbol* arbol, nodoArbol* nuevo)
{
    if(arbol==NULL){//si encuentra un hueco agrega al nuevo nodo en ese espacio vacio
        arbol=nuevo;
    }
    else//si no lo encuentra lo busca en sus dos hijos
    {
        if(nuevo->dato.id>arbol->dato.id)
            arbol->der=insertarNodoArbol(arbol->der,nuevo);
        else
            arbol->izq=insertarNodoArbol(arbol->izq,nuevo);
    }


    return arbol;
}

void mostrarPuntaje (puntuacionJugador dato)
{
    printf("ID:%i\tNOMBRE: %s\tCONTRASENIA: %s\n",dato.id, dato.nombreJugador,dato.contraseniaJugador);
    printf("----------------------------------------------------\n");
}

void mostrarInorderActivos (nodoArbol* arbol)
{
    if(arbol)
    {
        mostrarInorder(arbol->izq);
        if(arbol->dato.bajaLogica==0)
            mostrarPuntaje(arbol->dato);
        mostrarInorder(arbol->der);
    }
}

void mostrarInorderBaja (nodoArbol* arbol)
{
    if(arbol)
    {
        mostrarInorderBaja(arbol->izq);
        if(arbol->dato.bajaLogica==1)
            mostrarPuntaje(arbol->dato);
        mostrarInorderBaja(arbol->der);
    }
}

void mostrarInorder (nodoArbol* arbol)
{
    if(arbol)
    {
        mostrarInorder(arbol->izq);
        mostrarPuntaje(arbol->dato);
        mostrarInorder(arbol->der);
    }
}

void mostrarEspecifico(nodoArbol* arbol,int id)
{
    if(arbol)
    {
        mostrarEspecifico(arbol->izq,id);
        if(arbol->dato.id==id)
            mostrarPuntaje(arbol->dato);
        mostrarEspecifico(arbol->der,id);
    }
}

nodoArbol* archivoArbol2(char nombreArchivo[],nodoArbol* arbol)
{
    FILE* archi;
    archi=fopen(nombreArchivo,"rb");
    puntuacionJugador aux;
    if(archi)
    {

        while(fread(&aux,sizeof(puntuacionJugador),1,archi)>0){
            nodoArbol * nuevoNodo = crearNodoArbol(aux);
            arbol=insertarNodoArbol(arbol, nuevoNodo);
        }
        fclose(archi);
    }

    return arbol;
}

puntuacionJugador inicJugador(puntuacionJugador dato)
{
    dato.admin=NULL;
    dato.bajaLogica=0;

    return dato;
}

void nuevoUsuarioAlArchivo(char nombreArchivo[])
{
    puntuacionJugador aux;
    aux = inicJugador(aux);
    printf("Ingrese su nombre\n");
    fflush(stdin);
    gets(aux.nombreJugador);
    system("cls");
    printf("Ingrese la contrasenia\n");
    fflush(stdin);
    gets(aux.contraseniaJugador);
    system("cls");
    printf("Es admin? S o N\n");
    fflush(stdin);
    scanf("%c", &aux.admin);
    aux.id=creaID(nombreArchivo);
    cargarArchivoJugadores(nombreArchivo,aux);
}

int creaID(char nombreArchivo[]) {
    FILE *archi = fopen(nombreArchivo, "rb");  // Abre el archivo en modo de lectura binaria

    int cantidad_de_datos = 0;  // Inicializa la variable fuera del bloque if

    if (archi) {
        // Mueve el puntero de posici�n al final del archivo
        fseek(archi, 0, SEEK_END);

        // Obtiene la posici�n actual del puntero, que es el tama�o total del archivo en bytes
        long tamanio = ftell(archi);

        // Calcula la cantidad de elementos en t�rminos de tama�o de datos
        size_t tamanio_dato = sizeof(puntuacionJugador);  // Utiliza el tama�o de tu estructura
        cantidad_de_datos = tamanio / tamanio_dato;

        fclose(archi);
    }

    return cantidad_de_datos+1;
}

int iniciarSesion(char nombreArchivo[], puntuacionJugador jugador)
{
    FILE *archi = fopen(nombreArchivo, "rb");
    puntuacionJugador aux2;
    int resul=0;
    if(archi)
    {
        while(fread(&aux2,sizeof(puntuacionJugador),1,archi)>0)
        {
            if(strcmp(jugador.nombreJugador,aux2.nombreJugador)==0 && strcmp(jugador.contraseniaJugador,aux2.contraseniaJugador)==0)
                resul=1;
        }
        fclose(archi);
    }
    return resul;
}

int iniciarSesionAdmin(char nombreArchivo[])
{
    FILE *archi = fopen(nombreArchivo, "rb");
    puntuacionJugador aux,aux2;
    int resul=0;
    printf("Ingrese el nombre del jugador\n");
    fflush(stdin);
    gets(aux.nombreJugador);
    printf("Ingrese la contrasenia\n");
    fflush(stdin);
    gets(aux.contraseniaJugador);
    if(archi)
    {
        while(fread(&aux2,sizeof(puntuacionJugador),1,archi)>0)
        {
            if(strcmp(aux.nombreJugador,aux2.nombreJugador) == 0 && strcmp(aux.contraseniaJugador, aux2.contraseniaJugador) == 0 && aux2.admin=='s')
                resul=2;
        }
        fclose(archi);
    }
    return resul;
}



nodoArbol* darDeBajaUsuario(nodoArbol* arbol,int id)
{
    if(arbol){
        arbol->izq=darDeBajaUsuario(arbol->izq,id);
        if(arbol->dato.id==id)
            arbol->dato.bajaLogica=1;
        arbol->der=darDeBajaUsuario(arbol->der,id);
    }

    return arbol;
}

void guardarArbolEnArchivo(nodoArbol* arbol,char nombreArchivo[]) {
    FILE* archi = fopen(nombreArchivo, "wb");

    if(archi){
    guardarNodoEnArchivo(arbol, archi);
    fclose(archi);
    }
}

void guardarNodoEnArchivo(nodoArbol* nodo, FILE* archi) {
    if(nodo)
    {
    fwrite(&(nodo->dato), sizeof(nodo->dato), 1, archi);
    guardarNodoEnArchivo(nodo->izq, archi);
    guardarNodoEnArchivo(nodo->der, archi);
    }
}

nodoArbol * inicArbol()
{
return NULL;
}

nodoArbol* daDeAlta(int id,nodoArbol* arbol)
{
    if(arbol){
    arbol->izq=daDeAlta(id,arbol->izq);
    if(arbol->dato.id==id)
        arbol->dato.bajaLogica=0;
    arbol->der=daDeAlta(id,arbol->der);
    }
    return arbol;
}

nodoArbol* cambiarNombre(int id,char nombreNuevo[],nodoArbol* arbol)
{
    if(arbol){
    arbol->izq=cambiarNombre(id,nombreNuevo,arbol->izq);
    if(arbol->dato.id==id)
        strcpy(arbol->dato.nombreJugador,nombreNuevo);
    arbol->der=cambiarNombre(id,nombreNuevo,arbol->der);
    }

    return arbol;
}

nodoArbol* cambiaContrasenia(int id,char contraseniaNueva[],nodoArbol* arbol)
{
    if(arbol){
    arbol->izq=cambiaContrasenia(id,contraseniaNueva,arbol->izq);
    if(arbol->dato.id==id)
        strcpy(arbol->dato.contraseniaJugador,contraseniaNueva);
    arbol->der=cambiaContrasenia(id,contraseniaNueva,arbol->der);
    }

    return arbol;
}

nodoArbol* convertirEnAdmin(int id,nodoArbol* arbol)
{
    if(arbol){
    arbol->izq=convertirEnAdmin(id,arbol->izq);
    if(arbol->dato.id==id)
        arbol->dato.admin='s';
    arbol->der=convertirEnAdmin(id,arbol->der);
    }
    return arbol;
}







