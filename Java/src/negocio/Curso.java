package negocio;

import modelo.Estudiante;

public class Curso {

    public static final int CAPACIDAD_MAXIMA = 20;

    private Estudiante[] estudiantes;
    private int tope;
    private int capacidad;

    public Curso() {
        this(CAPACIDAD_MAXIMA);
    }

    public Curso(int capacidadMaxima) {
        this.capacidad = capacidadMaxima;
        this.estudiantes = new Estudiante[capacidadMaxima];
        this.tope = 0;
    }

    public boolean insertar(Estudiante estudiante) {
        if (tope >= capacidad || estudiante == null) {
            return false;
        }
        if (buscar(estudiante.getCedula()) != -1) {
            return false;
        }
        estudiantes[tope] = estudiante;
        tope++;
        return true;
    }

    public int buscar(String cedula) {
        if (cedula == null) {
            return -1;
        }
        for (int i = 0; i < tope; i++) {
            if (estudiantes[i] != null && estudiantes[i].getCedula().equals(cedula)) {
                return i;
            }
        }
        return -1;
    }

    public Estudiante obtener(int indice) {
        if (indice < 0 || indice >= tope) {
            return null;
        }
        return estudiantes[indice];
    }

    public boolean eliminar(int indice) {
        if (indice < 0 || indice >= tope) {
            return false;
        }
        for (int i = indice; i < tope - 1; i++) {
            estudiantes[i] = estudiantes[i + 1];
        }
        tope--;
        estudiantes[tope] = null;
        return true;
    }

    public boolean modificar(int indice, Estudiante nuevosDatos) {
        if (indice < 0 || indice >= tope || nuevosDatos == null) {
            return false;
        }
        int existente = buscar(nuevosDatos.getCedula());
        if (existente != -1 && existente != indice) {
            return false;
        }
        Estudiante actual = estudiantes[indice];
        actual.setCedula(nuevosDatos.getCedula());
        actual.setNombres(nuevosDatos.getNombres());
        actual.setApellidos(nuevosDatos.getApellidos());
        actual.setFechaNacimiento(nuevosDatos.getFechaNacimientoTexto());
        return true;
    }

    public Estudiante[] listar() {
        Estudiante[] listaActual = new Estudiante[tope];
        System.arraycopy(estudiantes, 0, listaActual, 0, tope);
        return listaActual;
    }

    public Double calcularPromedioGeneral() {
        if (tope == 0) {
            return null;
        }
        double sumaPromedios = 0.0;
        int estudiantesConNotas = 0;
        for (int i = 0; i < tope; i++) {
            if (estudiantes[i].tieneCalificaciones()) {
                sumaPromedios += estudiantes[i].calcularPromedio();
                estudiantesConNotas++;
            }
        }
        if (estudiantesConNotas == 0) {
            return null;
        }
        return sumaPromedios / estudiantesConNotas;
    }

    public int getTope() {
        return tope;
    }

    public int getCapacidad() {
        return capacidad;
    }
}
