package app;
import modelo.Estudiante;
import negocio.Curso;
import java.util.Scanner;
public class Main {
    private static Scanner sc = new Scanner(System.in);
    private static Curso curso = new Curso();

    public static void main(String[] args) {
        int opcion;
        do {
            System.out.println("\n=== GESTOR DE PERSONAS ===");
            System.out.println("1.- Estudiantes.");
            System.out.println("2.- Registro de calificaciones.");
            System.out.println("3.- Determinar el promedio de notas de un estudiante.");
            System.out.println("4.- Determinar el promedio de notas del curso.");
            System.out.print("Teclee su opcion (1-4): ");
            opcion = leerInt();

            switch (opcion) {
                case 1: opcionEstudiantes(); break;
                case 2: opcionCalificaciones(); break;
                case 3: opcionPromedioEstudiante(); break;
                case 4: opcionPromedioCurso(); break;
                default: System.out.println("Opcion no valida."); break;
            }
        } while (opcion >= 1 && opcion <= 4);
    }

    private static String pedirFecha() {
        System.out.print(" Dia: "); int d = leerInt();
        System.out.print(" Mes: "); int m = leerInt();
        System.out.print(" Anio: "); int a = leerInt();
        return String.format("%02d/%02d/%04d", d, m, a);
    }

    private static void listar() {
        System.out.println("\n--- LISTADO ACTUAL ---");
        if (curso.getTope() == 0) {
            System.out.println("No hay estudiantes registrados.");
        } else {
            Estudiante[] lista = curso.listar();
            for (int i = 0; i < lista.length; i++) {
                System.out.println((i + 1) + ". " + lista[i].toString());
            }
        }
    }

    // OPCION 1
    private static void opcionEstudiantes() {
        listar();
        System.out.println("\n-- Submenu Estudiantes --");
        System.out.println("1. Ingresar");
        System.out.println("2. Modificar");
        System.out.println("3. Eliminar");
        System.out.println("4. Volver");
        System.out.print("Opcion: ");
        int op = leerInt();

        switch (op) {
            case 1:
                do {
                    if (curso.getTope() >= curso.getCapacidad()) {
                        System.out.println("No se permite insertar, cupo de 20 alcanzado.");
                        break;
                    }
                    System.out.print("Cedula (10 digitos): "); String ced = sc.nextLine();
                    System.out.print("Nombres: "); String nom = sc.nextLine();
                    System.out.print("Apellidos: "); String ape = sc.nextLine();
                    System.out.println("Fecha nacimiento: ");
                    String fec = pedirFecha();
                    try {
                        Estudiante e = new Estudiante(ced, nom, ape, fec);
                        if (!curso.insertar(e)) System.out.println("Cedula duplicada.");
                        else System.out.println("Ingresado correctamente.");
                    } catch (Exception ex) { System.out.println("Error: " + ex.getMessage()); }
                } while (preguntar("Desea ingresar de nuevo? s/n: "));
                break;

            case 2:
                do {
                    if (curso.getTope() == 0) { System.out.println("No hay estudiantes."); break; }
                    System.out.print("Autonumerico a modificar: "); int idx = leerInt() - 1;
                    Estudiante actual = curso.obtener(idx);
                    if (actual == null) { System.out.println("Autonumerico no existe."); }
                    else {
                        System.out.print("Nueva Cedula [" + actual.getCedula() + "]: "); String ced = sc.nextLine();
                        System.out.print("Nuevos Nombres [" + actual.getNombres() + "]: "); String nom = sc.nextLine();
                        System.out.print("Nuevos Apellidos [" + actual.getApellidos() + "]: "); String ape = sc.nextLine();
                        String fec = actual.getFechaNacimientoTexto();
                        if (preguntar("Cambiar fecha? s/n: ")) { System.out.println("Nueva fecha:"); fec = pedirFecha(); }

                        String cedF = ced.isEmpty()? actual.getCedula() : ced;
                        String nomF = nom.isEmpty()? actual.getNombres() : nom;
                        String apeF = ape.isEmpty()? actual.getApellidos() : ape;
                        try {
                            Estudiante nuevo = new Estudiante(cedF, nomF, apeF, fec);
                            if (curso.modificar(idx, nuevo)) System.out.println("Modificado.");
                            else System.out.println("Cedula duplicada con otro estudiante.");
                        } catch (Exception ex) { System.out.println("Error: " + ex.getMessage()); }
                    }
                } while (preguntar("Desea modificar otro? s/n: "));
                break;

            case 3:
                if (curso.getTope() == 0) { System.out.println("No se permite eliminar, no hay estudiantes registrados."); return; }
                do {
                    System.out.print("Autonumerico a eliminar: "); int idx = leerInt() - 1;
                    if (curso.eliminar(idx)) System.out.println("Eliminado.");
                    else System.out.println("Autonumerico no valido.");
                } while (preguntar("Desea eliminar otro? s/n: "));
                break;
        }
    }

    // OPCION 2
    private static void opcionCalificaciones() {
        while (true) {
            System.out.print("\nIngrese cedula del estudiante: ");
            String ced = sc.nextLine();
            int idx = curso.buscar(ced);
            if (idx == -1) {
                System.out.println("Estudiante no registrado.");
                if (!preguntar("Desea ingresar otra cedula? s/n: ")) return;
                else continue;
            }
            Estudiante e = curso.obtener(idx);
            System.out.println("Datos: " + e.getNombres() + " " + e.getApellidos() + " Edad: " + e.calcularEdad());

            int op;
            do {
                double[] notas = e.getCalificaciones();
                System.out.println("\nCalificaciones registradas:");
                if (notas.length == 0) System.out.println(" - sin notas -");
                else for (int i = 0; i < notas.length; i++) System.out.println(" " + (i+1) + ". " + notas[i]);

                if (e.getTope() >= Estudiante.MAX_CALIFICACIONES) {
                    System.out.println("Se han ingresado todas las calificaciones posibles");
                    break;
                }
                System.out.println("\n1. Insertar 2. Modificar 3. Eliminar 4. Volver/Buscar otro");
                System.out.print("Opcion: "); op = leerInt();
                switch (op) {
                    case 1:
                        do {
                            if (e.getTope() >= 7) { System.out.println("Se han ingresado todas las calificaciones posibles"); break; }
                            System.out.print("Nota (0-10): "); double n = leerDouble();
                            if (!e.registrarCalificacion(n)) System.out.println("Nota no valida.");
                            else System.out.println("Insertada.");
                        } while (preguntar("Desea insertar otra? s/n: "));
                        break;
                    case 2:
                        System.out.print("Indice a modificar: "); int im = leerInt() - 1;
                        System.out.print("Nueva nota: "); double nm = leerDouble();
                        if (e.modificarCalificacion(im, nm)) System.out.println("Modificada."); else System.out.println("Error.");
                        break;
                    case 3:
                        System.out.print("Indice a eliminar: "); int ie = leerInt() - 1;
                        if (e.eliminarCalificacion(ie)) System.out.println("Eliminada."); else System.out.println("Indice no valido.");
                        break;
                }
            } while (op!= 4);
            if (!preguntar("Desea consultar otra cedula? s/n: ")) return;
        }
    }

    // OPCION 3
    private static void opcionPromedioEstudiante() {
        System.out.print("Cedula del estudiante: "); String ced = sc.nextLine();
        int idx = curso.buscar(ced);
        if (idx == -1) {
            System.out.println("No se encontro un estudiante con el numero de cedula indicado");
        } else {
            Estudiante e = curso.obtener(idx);
            System.out.println("Nombres: " + e.getNombres() + " " + e.getApellidos());
            System.out.println("Edad: " + e.calcularEdad());
            if (!e.tieneCalificaciones()) System.out.println("Sin calificaciones registradas.");
            else System.out.println("Promedio: " + e.calcularPromedio());
        }
    }

    // OPCION 4
    private static void opcionPromedioCurso() {
        Double prom = curso.calcularPromedioGeneral();
        if (prom == null) System.out.println("No se han registrado calificaciones de estudiantes");
        else System.out.println("Promedio general del curso: " + prom);
    }

    private static int leerInt() { try { return Integer.parseInt(sc.nextLine()); } catch (Exception ex) { return -1; } }
    private static double leerDouble() { try { return Double.parseDouble(sc.nextLine()); } catch (Exception ex) { return -1; } }
    private static boolean preguntar(String msg) { System.out.print(msg); String r = sc.nextLine().toLowerCase(); return r.equals("s") || r.equals("si"); }
}



