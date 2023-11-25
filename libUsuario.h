#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#ifndef LIBUSUARIO_H_INCLUDED
#define LIBUSUARIO_H_INCLUDED

typedef struct
{
    char nombreJugador[30];
    char contraseniaJugador[30];
    int bajaLogica;
    int id;
    char admin;///s=si  n=no
} puntuacionJugador;


typedef struct nodoArbol
{
    puntuacionJugador dato;
    struct nodoArbol* izq;
    struct nodoArbol* der;
} nodoArbol;



void cargarArchivoJugadores(char nombreArchivo[],puntuacionJugador persona);
int buscaJugadorEnArchivo(char nombreArchivo[],puntuacionJugador persona);
nodoArbol* crearNodoArbol(puntuacionJugador dato);
nodoArbol* insertarNodoArbol(nodoArbol* arbol, nodoArbol* nuevo);
void mostrarPuntaje (puntuacionJugador dato);
void mostrarInorder (nodoArbol* arbol);
void mostrarInorderActivos (nodoArbol* arbol);
void mostrarInorderBaja (nodoArbol* arbol);
void mostrarEspecifico(nodoArbol* arbol,int id);
nodoArbol* archivoArbol2(char nombreArchivo[],nodoArbol* arbol);
puntuacionJugador inicJugador(puntuacionJugador dato);
void nuevoUsuarioAlArchivo(char nombreArchivo[]);
int creaID(char nombreArchivo[]);
int iniciarSesion(char nombreArchivo[], puntuacionJugador jugador);
int iniciarSesionAdmin(char nombreArchivo[]);
nodoArbol* darDeBajaUsuario(nodoArbol* arbol,int id);
void guardarNodoEnArchivo(nodoArbol* nodo, FILE* archi);
void guardarArbolEnArchivo(nodoArbol* arbol,char nombreArchivo[]);
nodoArbol * inicArbol();
nodoArbol* daDeAlta(int id,nodoArbol* arbol);
nodoArbol* cambiarNombre(int id,char nombreNuevo[],nodoArbol* arbol);
nodoArbol* cambiaContrasenia(int id,char contraseniaNueva[],nodoArbol* arbol);
nodoArbol* convertirEnAdmin(int id,nodoArbol* arbol);

#endif // LIBUSUARIO_H_INCLUDED
