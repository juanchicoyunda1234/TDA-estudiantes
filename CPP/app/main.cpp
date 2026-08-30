#include <iostream>
#include <string>
#include <cstdio>
#include "../negocio/Curso.cpp"

Curso curso;

int leerInt() {
    std::string l;
    std::getline(std::cin, l);
    if(l.empty()) return -1;
    try { return std::stoi(l); } catch (...) { return -1; }
}
double leerDouble() {
    std::string l;
    std::getline(std::cin, l);
    if(l.empty()) return -1;
    try { return std::stod(l); } catch (...) { return -1; }
}
bool preguntar(std::string msg) {
    std::cout << msg;
    std::string r;
    std::getline(std::cin, r);
    return r=="s" || r=="S" || r=="si" || r=="SI";
}
std::string pedirFecha() {
    std::cout << " Dia: "; int d = leerInt();
    std::cout << " Mes: "; int m = leerInt();
    std::cout << " Anio: "; int a = leerInt();
    char buf[20];
    snprintf(buf, sizeof(buf), "%02d/%02d/%04d", d, m, a);
    return std::string(buf);
}
void listar() {
    std::cout << "\n--- LISTADO ACTUAL ---\n";
    if (curso.getTope()==0) std::cout << "No hay estudiantes registrados.\n";
    else {
        Estudiante* lista = curso.listar();
        for(int i=0;i<curso.getTope();i++)
            std::cout << (i+1) << ". | " << lista[i].getCedula() << " | "
                      << lista[i].getNombres() << " " << lista[i].getApellidos()
                      << " | " << lista[i].getFechaNacimientoTexto()
                      << " | Edad: " << lista[i].calcularEdad() << "\n";
        delete[] lista;
    }
}

int main() {
    int opcion;
    do {
        std::cout << "\n=== GESTOR DE PERSONAS ===\n";
        std::cout << "1.- Estudiantes.\n";
        std::cout << "2.- Registro de calificaciones.\n";
        std::cout << "3.- Determinar el promedio de notas de un estudiante.\n";
        std::cout << "4.- Determinar el promedio de notas del curso.\n";
        std::cout << "Teclee su opcion (1-4) otra para salir: ";
        opcion = leerInt();
        if (opcion==1) {
            listar();
            std::cout << "\n-- Submenu Estudiantes --\n1. Ingresar\n2. Modificar\n3. Eliminar\n4. Volver\nOpcion: ";
            int op = leerInt();
            if (op==1) {
                do {
                    if (curso.getTope()>=curso.getCapacidad()) { std::cout << "No se permite insertar, cupo de 20 alcanzado.\n"; break; }
                    std::string ced,nom,ape;
                    std::cout << "Cedula (10 digitos): "; std::getline(std::cin,ced);
                    std::cout << "Nombres: "; std::getline(std::cin,nom);
                    std::cout << "Apellidos: "; std::getline(std::cin,ape);
                    std::cout << "Fecha nacimiento:\n";
                    std::string fec = pedirFecha();
                    try { Estudiante e(ced,nom,ape,fec); if(!curso.insertar(e)) std::cout<<"Cedula duplicada.\n"; else std::cout<<"Ingresado correctamente.\n"; }
                    catch(std::exception &ex){ std::cout<<"Error: "<<ex.what()<<"\n"; }
                } while(preguntar("Desea ingresar de nuevo? s/n: "));
            } else if (op==2) {
                do {
                    if(curso.getTope()==0){ std::cout<<"No hay estudiantes.\n"; break; }
                    std::cout<<"Autonumerico a modificar: "; int idx=leerInt()-1;
                    Estudiante* act=curso.obtener(idx);
                    if(!act) std::cout<<"Autonumerico no existe.\n";
                    else {
                        std::string ced,nom,ape;
                        std::cout<<"Nueva Cedula ["<<act->getCedula()<<"]: "; std::getline(std::cin,ced);
                        std::cout<<"Nuevos Nombres ["<<act->getNombres()<<"]: "; std::getline(std::cin,nom);
                        std::cout<<"Nuevos Apellidos ["<<act->getApellidos()<<"]: "; std::getline(std::cin,ape);
                        std::string fec=act->getFechaNacimientoTexto();
                        if(preguntar("Cambiar fecha? s/n: ")){ std::cout<<"Nueva fecha:\n"; fec=pedirFecha(); }
                        std::string cf=ced.empty()?act->getCedula():ced;
                        std::string nf=nom.empty()?act->getNombres():nom;
                        std::string af=ape.empty()?act->getApellidos():ape;
                        try{ Estudiante nuevo(cf,nf,af,fec); if(curso.modificar(idx,nuevo)) std::cout<<"Modificado.\n"; else std::cout<<"Cedula duplicada.\n"; }
                        catch(std::exception &ex){ std::cout<<"Error: "<<ex.what()<<"\n"; }
                    }
                } while(preguntar("Desea modificar otro? s/n: "));
            } else if (op==3) {
                do{ if(curso.getTope()==0){ std::cout<<"No hay estudiantes.\n"; break; } std::cout<<"Autonumerico a eliminar: "; int idx=leerInt()-1; if(curso.eliminar(idx)) std::cout<<"Eliminado.\n"; else std::cout<<"Autonumerico no valido.\n"; } while(preguntar("Desea eliminar otro? s/n: "));
            }
        }
        else if (opcion==2) {
            while(true){
                std::cout<<"\nIngrese cedula: "; std::string ced; std::getline(std::cin,ced);
                int idx=curso.buscar(ced);
                if(idx==-1){ std::cout<<"Estudiante no registrado.\n"; if(!preguntar("Otra cedula? s/n: ")) break; else continue; }
                Estudiante* e=curso.obtener(idx);
                std::cout<<"Datos: "<<e->getNombres()<<" "<<e->getApellidos()<<" Edad: "<<e->calcularEdad()<<"\n";
                int op;
                do{
                    std::cout<<"\nCalificaciones:\n";
                    if(e->getTope()==0) std::cout<<" - sin notas -\n"; else { const double* n=e->getCalificaciones(); for(int i=0;i<e->getTope();i++) std::cout<<" "<<(i+1)<<". "<<n[i]<<"\n"; }
                    if(e->getTope()>=7){ std::cout<<"Se han ingresado todas las calificaciones posibles\n"; break; }
                    std::cout<<"\n1. Insertar 2. Modificar 3. Eliminar 4. Volver\nOpcion: "; op=leerInt();
                    if(op==1){ do{ if(e->getTope()>=7) break; std::cout<<"Nota (0-10): "; double no=leerDouble(); if(!e->registrarCalificacion(no)) std::cout<<"Nota no valida.\n"; else std::cout<<"Insertada.\n"; } while(preguntar("Otra? s/n: ")); }
                    else if(op==2){ std::cout<<"Indice a modificar: "; int im=leerInt()-1; std::cout<<"Nueva nota: "; double nm=leerDouble(); if(e->modificarCalificacion(im,nm)) std::cout<<"Modificada.\n"; else std::cout<<"Error.\n"; }
                    else if(op==3){ std::cout<<"Indice a eliminar: "; int ie=leerInt()-1; if(e->eliminarCalificacion(ie)) std::cout<<"Eliminada.\n"; else std::cout<<"Indice no valido.\n"; }
                    else break;
                }while(op!=4);
                if(!preguntar("Consultar otra cedula? s/n: ")) break;
            }
        }
        else if (opcion==3) {
            std::cout<<"Cedula: "; std::string ced; std::getline(std::cin,ced);
            int idx=curso.buscar(ced);
            if(idx==-1) std::cout<<"No se encontro un estudiante con el numero de cedula indicado\n";
            else { Estudiante* e=curso.obtener(idx); std::cout<<"Nombres: "<<e->getNombres()<<" "<<e->getApellidos()<<"\nEdad: "<<e->calcularEdad()<<"\n"; if(!e->tieneCalificaciones()) std::cout<<"Sin calificaciones.\n"; else std::cout<<"Promedio: "<<e->calcularPromedio()<<"\n"; }
        }
        else if (opcion==4) {
            auto prom=curso.calcularPromedioGeneral();
            if(!prom.has_value()) std::cout<<"No se han registrado calificaciones de estudiantes\n";
            else std::cout<<"Promedio general del curso: "<<prom.value()<<"\n";
        } else break;
    } while(opcion>=1 && opcion<=4);
    return 0;
}