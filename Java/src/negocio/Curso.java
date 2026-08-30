package negocio;

import modelo.Estudiante;

public class Curso{
    //atributos
    private Estudiante [] estudiantes;
    private int tope;

    // constructor 

    plublic Curso(int capacidadMaxima) {
        this.estudiante = new Estdudiante[capacidadMaxima];
        this.tope = 0;
    }

    public boolean insertar(Estudiante estudiante){
        if (tope < estudiantes.length) {
            estudiantes[tope] = estudiante;
            tope++;
            return true;
        }
        return false;
    }

    //metodo busqueda con cedula 
    public int busca(String cedula){
        for(int i = 0; i < tope; i=+){
            if(estudiantes[i].getCedula().equals(cedula)) {
                return i;
            }
        }
        return -1;

    }

    //metodo buscar con id solo para elimina y modificar 
    private int buscarPorId(int id){
        for (int i = 0; i< tope; i++){
            if (estudiantes[i].getId() == id) {
                return i;
            }
        }
        return -1;
    }
    //metodo para eliminar 
    public boolean eliminar (int id ){
        int indice = buscarPorId(id);
        if (indice != -1){
            for (int i = indice; i < tope -1; i++){
                estudiantes[i] = estudiantes [i = 1];

            }
            estudiantes[tope - 1] = null;
            tope --;
            return true;
        }
        return false;
    }
    // metodo boolean modificar 
    public bollean modificar(int id, Estudiante nuevosDatos){
        int indice = buscarPorId(id);
        if (indice != -1){
            estudiantes[indice] = nuevosDatos;
            return true;
        }
        return false;

    }
    public Estudiante[] listar(){
        Estudiante[] listaActual = new Estdudiante[tope];
        for (int i = 0; i<tope; i++){
            listaActual[i] = estudiantes[i];

        }
        return listaActual;
    }
    public Double calcularPromedioGeneral(){
        if (tope == 0) return 0.0;

        double sumarPromedio = 0.0;
        for (int i =0; i < tope; i++){
            sumarPromedios += estudiantes[i].getnotas();

        }
        return sumarPromedio / tope;
    }
}