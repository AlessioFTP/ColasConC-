#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
using namespace std;

void Texto_centrado(string Texto, int y);

void Texto_Ascii (string Texto);

class Cola{
	protected:
	class NodoDoctores{
		public:
			string  Cedula;
			string Nombre, Especializacion;
			NodoDoctores* siguiente;
		};
	NodoDoctores* RaizDoc;
	class NodoPacientesNoAtendidos{
		public:
			string  Cedula;
			string Nombre, Condicion;
			NodoPacientesNoAtendidos* siguiente;
		};
	NodoPacientesNoAtendidos* RaizPacientesNo;
	class NodoPacientesAtendidos{
		public:
			string  Cedula;
			string Nombre, Condicion;
			string Doctor;
			NodoPacientesAtendidos* siguiente;
		};
	NodoPacientesAtendidos* RaizPacientes;
	public:
		Cola();
		~Cola();
		void EliminarPacientesA();
		void EliminarPacientesNoA();
		void EliminarDoctores();
		int CantidadPacientesNoAtendidos();
		int CantidadPacientesAtendidos();
		void InsertarPaciente(string  _Cedula, string _Nombre, string _Condicion);
		void InsertarPacienteAtendido(string  _Cedula, string _Nombre, string _Condicion, string _Doctor);
		void AtencionAPaciente();
		void ImprimirPacientesNo();
		void ImprimirPacientesSi();
		int CantidadDoctores();
		void InsertarDoctor(string  _Cedula, string _Nombre, string _Especializacion);
		void ImprimirDoctores();
		void GuardarRegistrosPNA();
		void GuardarRegistrosPA();
		void GuardarRegistrosDC();
};
				
Cola::Cola(){
	RaizPacientesNo = NULL;
	RaizPacientes = NULL;
	RaizDoc = NULL;
}

Cola::~Cola(){
	NodoPacientesNoAtendidos* recorrido = RaizPacientesNo;
	NodoPacientesNoAtendidos* borrar;
	while (recorrido!= NULL){
		borrar = recorrido;
		recorrido = recorrido->siguiente;
		delete borrar;
	}
	NodoDoctores* recorridoD = RaizDoc;
	NodoDoctores* borrarD;
	while (recorridoD!= NULL){
		borrarD = recorridoD;
		recorridoD = recorridoD->siguiente;
		delete borrarD;
	}
	NodoPacientesAtendidos* recorrido1 = RaizPacientes;
	NodoPacientesAtendidos* borrar1;
	while (recorrido1!= NULL){
		borrar1 = recorrido1;
		recorrido1 = recorrido1->siguiente;
		delete borrar1;
	}
	RaizPacientes = NULL;
	RaizPacientesNo = NULL;
	RaizDoc = NULL;
}

void Cola::EliminarPacientesA(){
	NodoPacientesAtendidos* recorrido = RaizPacientes;
	NodoPacientesAtendidos* borrar;
	while (recorrido!= NULL){
		borrar = recorrido;
		recorrido = recorrido->siguiente;
		delete borrar;
	}
	RaizPacientes = NULL;
}

void Cola::EliminarDoctores(){
	NodoDoctores* recorridoD = RaizDoc;
	NodoDoctores* borrarD;
	while (recorridoD!= NULL){
		borrarD = recorridoD;
		recorridoD = recorridoD->siguiente;
		delete borrarD;
	}
	RaizDoc = NULL;	
}

void Cola::EliminarPacientesNoA(){
	NodoPacientesNoAtendidos* recorrido = RaizPacientesNo;
	NodoPacientesNoAtendidos* borrar;
	while (recorrido!= NULL){
		borrar = recorrido;
		recorrido = recorrido->siguiente;
		delete borrar;
	}	
	RaizPacientesNo = NULL;
}

int Cola::CantidadPacientesNoAtendidos(){
	NodoPacientesNoAtendidos* recorrido = RaizPacientesNo;
	int cantidad = 0;
	while (recorrido != NULL){
		cantidad++;
		recorrido = recorrido->siguiente;
	}
	return cantidad;
}

int Cola::CantidadPacientesAtendidos(){
	NodoPacientesAtendidos* recorrido = RaizPacientes;
	int cantidad = 0;
	while (recorrido != NULL){
		cantidad++;
		recorrido = recorrido->siguiente;
	}
	return cantidad;
}

void Cola::InsertarPaciente(string  _Cedula, string _Nombre, string _Condicion){
	if (CantidadPacientesNoAtendidos() > 0){
		NodoPacientesNoAtendidos* nuevo = new NodoPacientesNoAtendidos ();
		nuevo->Cedula = _Cedula;
		nuevo->Nombre = _Nombre;
		nuevo->Condicion = _Condicion;
		NodoPacientesNoAtendidos* recorrido = RaizPacientesNo;
		while (recorrido->siguiente != NULL){
			recorrido = recorrido->siguiente;
		}
		recorrido->siguiente = nuevo;
		nuevo->siguiente = NULL;
	}
	else {
		NodoPacientesNoAtendidos* nuevo = new NodoPacientesNoAtendidos ();
		nuevo->Cedula = _Cedula;
		nuevo->Nombre = _Nombre;
		nuevo->Condicion = _Condicion;
		nuevo->siguiente = NULL;	
		RaizPacientesNo = nuevo;
	}
}

void Cola::InsertarPacienteAtendido(string  _Cedula, string _Nombre, string _Condicion, string _Doctor){
	NodoPacientesAtendidos* nuevo = new NodoPacientesAtendidos();
	nuevo->Cedula = _Cedula;
	nuevo->Nombre = _Nombre;
	nuevo->Condicion = _Condicion;
	nuevo->Doctor = _Doctor;
	if(CantidadPacientesAtendidos() == 0){
		nuevo->siguiente = NULL;
		RaizPacientes = nuevo;
	}
	else{
		NodoPacientesAtendidos* recorrido = RaizPacientes;
		while (recorrido->siguiente != NULL){
			recorrido = recorrido->siguiente;
		}
		nuevo->siguiente = NULL;
		recorrido->siguiente = nuevo;
	}
}

void Cola::AtencionAPaciente(){
	short int x;
	ImprimirDoctores();
	NodoDoctores* recorrido = RaizDoc;
	NodoPacientesNoAtendidos* Traspaso = RaizPacientesNo;
	Texto_centrado("Indique el indice el doctor que lo atendió: ", 0);
	cin >> x;
	if (x > 0 && x <= CantidadDoctores()){
		for (int i = 1; i < x; i++){
			recorrido = recorrido->siguiente;
		}
		InsertarPacienteAtendido(Traspaso->Cedula, Traspaso->Nombre, Traspaso->Condicion, recorrido->Nombre);
		string Mensaje = "El paciente " + RaizPacientesNo->Nombre + " ha sido marcado como atendido con exito.";
		Texto_centrado(Mensaje, 1);
		RaizPacientesNo = RaizPacientesNo->siguiente;
		delete Traspaso;
	}
	else {
		Texto_centrado("No hay un doctor registrado con ese indicie.", 1);
	}
}

void Cola::ImprimirPacientesNo(){
	NodoPacientesNoAtendidos* recorrido = RaizPacientesNo;
	int i = 1;
	while (recorrido != NULL){
			string Mensaje = to_string(i++) + ". Paciente " + recorrido->Nombre + ", con N° de cédula: " + recorrido->Cedula + ", fue ingresado por: " + recorrido->Condicion;
			Texto_centrado(Mensaje,1);
			recorrido = recorrido->siguiente;
	}
}

void Cola::ImprimirPacientesSi(){
	NodoPacientesAtendidos* recorrido = RaizPacientes;
	int i = 1;
	while (recorrido != NULL){
			string Mensaje = to_string(i++) + ". Paciente " + recorrido->Nombre + ", con N° de cédula: " + recorrido->Cedula + ", fue ingresado por: " + recorrido->Condicion + " Fue atendido por el doctor: " + recorrido->Doctor;
			Texto_centrado(Mensaje,1);
			recorrido = recorrido->siguiente;
	}
}


int Cola::CantidadDoctores(){
	NodoDoctores* recorrido = RaizDoc;
	int cantidad = 0;
	while (recorrido != NULL){
		cantidad++;
		recorrido = recorrido->siguiente;
	}
	return cantidad;
}

void Cola::InsertarDoctor(string  _Cedula, string _Nombre, string _Especializacion){
	if (CantidadDoctores() > 0){
		NodoDoctores* nuevo = new NodoDoctores ();
		nuevo->Cedula = _Cedula;
		nuevo->Nombre = _Nombre;
		nuevo->Especializacion = _Especializacion;
		NodoDoctores* recorrido = RaizDoc;
		while (recorrido->siguiente != NULL){
			recorrido = recorrido->siguiente;
		}
		recorrido->siguiente = nuevo;
		nuevo->siguiente = NULL;
	}
	else {
		NodoDoctores* nuevo = new NodoDoctores ();
		nuevo->Cedula = _Cedula;
		nuevo->Nombre = _Nombre;
		nuevo->Especializacion = _Especializacion;
		nuevo->siguiente = NULL;	
		RaizDoc = nuevo;
	}
}

void Cola::ImprimirDoctores(){
	NodoDoctores* recorrido = RaizDoc;
	int i = 1;
	while (recorrido != NULL){
		string Mensaje= to_string(i++) + ". Doctor " + recorrido->Nombre + ", con N° de cédula: " + recorrido->Cedula + ", especializado en: " + recorrido->Especializacion;
		Texto_centrado(Mensaje, 1);
		recorrido = recorrido->siguiente;
	}
}

void Cola::GuardarRegistrosPNA(){
	fstream RegistrosPNA("RegistrosPacientesNOAtendidos.csv", ios::out);
	RegistrosPNA << "Nombre;Cedula;Condición" << endl;
	NodoPacientesNoAtendidos* recorrido = RaizPacientesNo;
		while (recorrido != NULL){
			RegistrosPNA << recorrido->Nombre << ";" << recorrido->Cedula << ";" << recorrido->Condicion << endl;
			recorrido = recorrido->siguiente;
		}
	RegistrosPNA.close();
}

void Cola::GuardarRegistrosPA(){
	fstream RegistrosPA("RegistrosPacientesAtendidos.csv", ios::out);
	RegistrosPA << "Nombre;Cedula;Condición;Doctor" << endl;
	NodoPacientesAtendidos* recorrido = RaizPacientes;
		while (recorrido != NULL){
			RegistrosPA << recorrido->Nombre << ";" << recorrido->Cedula << ";" << recorrido->Condicion << ";" << recorrido->Doctor << endl;
			recorrido = recorrido->siguiente;
		}
	RegistrosPA.close();
}

void Cola::GuardarRegistrosDC(){
	fstream RegistrosD("RegistrosDoctores.csv", ios::out);
	RegistrosD << "Nombre;Cedula;Especialidad" << endl;
	NodoDoctores* recorrido = RaizDoc;
		while (recorrido != NULL){
			RegistrosD << recorrido->Nombre << ";" << recorrido->Cedula << ";" << recorrido->Especializacion << endl;
			recorrido = recorrido->siguiente;
		}
	RegistrosD.close();
}

class Manejo{
	public:
		Manejo(){
		}
		void GestionarPacientesNO(Cola &Clinica);
		void GestionarPacientesSI(Cola &Clinica);
		void GestionarDoctores(Cola &Clinica);
};

void Manejo::GestionarPacientesNO(Cola &Clinica){
	short op;
	do{
		Texto_Ascii("Pacientes no Atendidos");
		Texto_centrado("-----------------------Menú-----------------------",1 );
		Texto_centrado("Digite una opción.", 1);
		Texto_centrado("0. Salir.", 1);
		Texto_centrado("1. Ingresar un paciente.", 1);
		Texto_centrado("2. Mostrar los pacientes NO atendidos.", 1);
		Texto_centrado("3. Registrar la atención de un paciente.", 1);
		Texto_centrado("4. Vaciar el registro de los NO pacientes atendidos.", 1);
		Texto_centrado("5. Guardar en el archivo los registros. ", 1);
		Texto_centrado("Ingrese la opción: ", 0);
		cin >> op;
		switch (op){
			case 0:{
				break;
			}
			case 1:{
				string _Cedula;
				string _Nombre, _Condicion;
				Texto_centrado("Ingrese el nombre del paciente: ", 0);
				cin.ignore();
				getline(cin, _Nombre);
				Texto_centrado("Ingrese la cedula del paciente: ", 0);
				cin >> _Cedula;
				Texto_centrado("Ingrese la condicion del paciente: ", 0);
				cin.ignore();
				getline(cin, _Condicion);
				Clinica.InsertarPaciente(_Cedula, _Nombre, _Condicion);							
				string Mensaje = "El paciente " + _Nombre + " ha sido guardado con exito.";
				Texto_centrado(Mensaje, 1);
				system ("Pause");
				system ("cls");
				break;
			}
			case 2:{
				if (Clinica.CantidadPacientesNoAtendidos() > 0)
					Clinica.ImprimirPacientesNo();
				else Texto_centrado("La cola de pacientes NO atendidos está vacía.", 1);
				system ("Pause");
				system ("cls");
				break;
			}
			case 3:{
				if (Clinica.CantidadPacientesNoAtendidos() > 0){
					if(Clinica.CantidadDoctores() < 1)
						Texto_centrado("No hay doctores en el registro para poder atender a un paciente.", 1);
					else Clinica.AtencionAPaciente();
				}
				 else Texto_centrado("La cola de pacientes NO atendidos está vacía, por ende no se puede registrar como atendido un paciente.", 1);
				system ("Pause");
				system ("cls");
				break;
			}
			case 4:{
				if (Clinica.CantidadPacientesNoAtendidos() > 0){
					Clinica.EliminarPacientesNoA();
					Texto_centrado("Registro de pacientes NO atendidos eliminados con exito.", 1);
				}else Texto_centrado("La cola de pacientes NO atendidos ya está vacía.", 1);
				system ("Pause");
				system ("cls");
				break;
			}
			case 5:{
				Clinica.GuardarRegistrosPNA();
				Texto_centrado("Registro de pacientes NO atendidos guardados con exito.", 1);
				system ("Pause");
				system ("cls");
				break;
			}
			default:{
				Texto_centrado("Opción no valida, vuelva y digite una opción.", 1);
				system ("Pause");
				system ("cls");
				break;
			}
		}
	}while(op != 0);
}

void Manejo::GestionarPacientesSI(Cola &Clinica){
	short op;
	do{
		Texto_Ascii("Pacientes Atendidos");
		Texto_centrado("-----------------------Menú-----------------------",1 );
		Texto_centrado("Digite una opción.", 1);
		Texto_centrado("0. Salir.", 1);
		Texto_centrado("1. Mostrar los pacientes atendidos.", 1);
		Texto_centrado("2. Vaciar el registro de los pacientes atendidos.", 1);
		Texto_centrado("3. Guardar en el archivo los registros. ", 1);
		Texto_centrado("Ingrese la opción: ", 0);
		cin >> op;
		switch (op){
			case 0:{
				break;
			}
			case 1:{
				if (Clinica.CantidadPacientesAtendidos() > 0)
					Clinica.ImprimirPacientesSi();
				else Texto_centrado("La cola de pacientes atendidos está vacía.", 1);
				system ("Pause");
				system ("cls");
				break;
			}
			case 2:{
				if (Clinica.CantidadPacientesAtendidos() > 0){
					Clinica.EliminarPacientesA();
					Texto_centrado("Registro de pacientes atendidos eliminados con exito.", 1);
				} else Texto_centrado("La cola de pacientes atendidos ya está vacía.", 1);
				system ("Pause");
				system ("cls");
				break;
			}
			case 3:{
				Clinica.GuardarRegistrosPA();
				Texto_centrado("Registro de pacientes atendidos guardados con exito.", 1);
				system ("Pause");
				system ("cls");
				break;
			}
			default:{
				Texto_centrado("Opción no valida, vuelva y digite una opción.", 1);
				system ("Pause");
				system ("cls");
				break;
			}
			
		}
	}while (op != 0);
}

void Manejo::GestionarDoctores(Cola &Clinica){
	short op;
	do{
		Texto_Ascii("Doctores");
		Texto_centrado("-----------------------Menú-----------------------",1 );
		Texto_centrado("Digite una opción.", 1);
		Texto_centrado("0. Salir.", 1);
		Texto_centrado("1. Mostrar los Doctores.", 1);
		Texto_centrado("2. Agregar un Doctor nuevo.", 1);
		Texto_centrado("3. Vaciar el registro de los doctores.", 1);
		Texto_centrado("4. Guardar en el archivo los registros. ", 1);
		Texto_centrado("Ingrese la opción: ", 0);
		cin >> op;
		switch (op){
			case 0:{
				break;
			}
			case 1:{
				if (Clinica.CantidadDoctores() > 0)
					Clinica.ImprimirDoctores();
				else Texto_centrado("La cola de los doctores se encuentra vacía.", 1);
				system ("Pause");
				system ("cls");
				break;
			}
			case 2:{
				string _Cedula;
				string _Nombre;
				string _Especializacion;
				Texto_centrado("Ingrese el nombre del Doctor: ", 0);
				cin.ignore();
				getline(cin, _Nombre);
				Texto_centrado("Ingrese la cedula del Doctor: ", 0);
				cin >> _Cedula;
				Texto_centrado("Ingrese la especializacion del Doctor: ", 0);
				cin.ignore();
				getline(cin, _Especializacion);
				Clinica.InsertarDoctor(_Cedula, _Nombre, _Especializacion);
				string Mensaje = "El doctor " + _Nombre + " ha sido registrado con exito.";
				Texto_centrado(Mensaje, 1);
				system ("Pause");
				system ("cls");
				break;
			}
			case 3:{
				if (Clinica.CantidadDoctores() > 0){
					Clinica.EliminarDoctores();
					Texto_centrado("Registro de doctores eliminados con exito.", 1);
				} else Texto_centrado("La cola de los doctores ya se encuentra vacía.", 1);
				system ("Pause");
				system ("cls");
				break;
			}
			case 4:{
				Clinica.GuardarRegistrosDC();
				Texto_centrado("Registro de doctores guardados con exito.", 1);
				system ("Pause");
				system ("cls");
				break;
			}
			default:{
				Texto_centrado("Opción no valida, vuelva y digite una opción.", 1);
				system ("Pause");
				system ("cls");
				break;
			}
		}
	}while (op != 0);
	
}

void Menu(Manejo Administarcion, Cola &Clinica);

void CargarRegistros(Cola &Clinica);

int main(){
	setlocale(LC_ALL, "spanish");
	Cola Clinica; 
	CargarRegistros(Clinica);
	Manejo Administracion;
	Menu(Administracion, Clinica);
	return 0;
}

void Menu(Manejo Administracion, Cola &Clinica){
	short int op;
	do{
		Texto_Ascii("Clinica Paso al Infierno");
		Texto_centrado("-----------------------Menú-----------------------",1 );
		Texto_centrado("Digite una opción.", 1);
		Texto_centrado("0.Salir del programa", 1);
		Texto_centrado("1.Gestionar los pacientes no atendidos.", 1);
		Texto_centrado("2.Gestionar los pacientes atendidos.", 1);
		Texto_centrado("3.Gestionar los doctores.", 1);
		Texto_centrado("4.Vaciar todos los registros (Incluyendo doctores).", 1);
		Texto_centrado("Ingrese la opción: ", 0);
		cin >> op;
		switch (op){
			case 0:{
				Texto_centrado("Gracias por usar este programa.", 1);
				break;
			}
			case 1:{
				system ("cls");
				Administracion.GestionarPacientesNO(Clinica);
				system ("cls");
				break;
			}
			case 2:{
				system ("cls");
				Administracion.GestionarPacientesSI(Clinica);
				system ("cls");
				break;
			}
			case 3:{
				system ("cls");
				Administracion.GestionarDoctores(Clinica);
				system ("cls");
				break;
			}
			case 4:{
				Clinica.~Cola();
				short int x;
				Texto_centrado("Datos eliminados con exito. ¿Desea guardar los cambios en los archivos de los registros?", 1);
					Texto_centrado("Digite 1 para guardar, o 2 para NO guardarlos aun: ", 0);
				do{
					cin >> x;
					switch (x){
						case 1:{
							Clinica.GuardarRegistrosDC();
							Clinica.GuardarRegistrosPA();
							Clinica.GuardarRegistrosPNA();
							Texto_centrado("Archivos actualizados.", 1);
							system ("Pause");
							system ("cls");
							break;
						}
						case 2:{
							Texto_centrado("Archivos NO actualizados.", 1);
							system ("Pause");
							system ("cls");
							break;
						}
						default:{
							Texto_centrado("Opción no valida, intente de nuevo.", 1);
							break;
						}
					}
				}while (!(x != 1 or x != 2));
				break;
			}
			default:{
				Texto_centrado("Opción no valida, vuelva y digite una opción", 1);
				system ("Pause");
				system ("cls");
				break;
			}
		}
	}while (op != 0);
}

void CargarRegistros(Cola &Clinica){
	fstream RegistrosPNA("RegistrosPacientesNOAtendidos.csv", ios::in), RegistrosPA("RegistrosPacientesAtendidos.csv", ios::in), RegistrosD("RegistrosDoctores.csv", ios::in);
	if (!RegistrosPNA.is_open()){
		fstream CrearCSV("RegistrosPacientesNOAtendidos.csv", ios::out);
		CrearCSV << "Nombre;Cedula;Condición" << endl;
		CrearCSV.close();
	}else{
		string linea;
		getline(RegistrosPNA, linea);
		while(getline(RegistrosPNA, linea)){
			string _Nombre, _Condicion, _Cedula;
			stringstream Linea (linea);
			getline(Linea, _Nombre, ';');
			getline(Linea, _Cedula, ';');
			getline(Linea, _Condicion, ';');
			Clinica.InsertarPaciente(_Cedula, _Nombre, _Condicion);
		}
	}
	if(!RegistrosPA.is_open()){
		fstream CrearCSV("RegistrosPacientesAtendidos.csv", ios::out);
		CrearCSV << "Nombre;Cedula;Condición;Doctor" << endl;
		CrearCSV.close();
	}else{
		string linea;
		getline(RegistrosPA, linea);
		while(getline(RegistrosPA, linea)){
			string _Nombre, _Condicion, _Cedula, _Doctor;
			stringstream Linea (linea);
			getline(Linea, _Nombre, ';');
			getline(Linea, _Cedula, ';');
			getline(Linea, _Condicion, ';');
			getline(Linea, _Doctor, ';');
			Clinica.InsertarPacienteAtendido(_Cedula, _Nombre, _Condicion, _Doctor);
		}
	}
	if(!RegistrosD.is_open()){
		fstream CrearCSV("RegistrosDoctores.csv", ios::out);
		CrearCSV << "Nombre;Cedula;Especialidad" << endl;
		CrearCSV.close();
	}else{
		string linea;
		getline(RegistrosD, linea);
		while(getline(RegistrosD, linea)){
			string _Nombre, _Especialidad, _Cedula;
			stringstream Linea (linea);
			getline(Linea, _Nombre, ';');
			getline(Linea, _Cedula, ';');
			getline(Linea, _Especialidad, ';');
			Clinica.InsertarDoctor(_Cedula, _Nombre, _Especialidad);
		}
	}
	RegistrosPNA.close();
	RegistrosPA.close();
	RegistrosD.close();
}

void Texto_centrado(string Texto, int y){
	int x = Texto.size();
	x = (120 - x)/2;
	if (y > 0){
		for (int j = 0; j < x; j++){
					cout << " ";
				}
		cout << Texto << endl;
	}
	else {
		for (int j = 0; j < x; j++){
					cout << " ";
				}
		cout << Texto;
	}
	
}

void Texto_Ascii (string Texto){
	int x = Texto.size();
	x *= 4;
	x = (120 - x)/2;
	for (int i = 0; i < Texto.size(); i++){
		if (i == 0){
			for (int j = 0; j < x; j++){
				cout << " ";
			}
		}
		if (Texto[i] == '1')
			cout << " ## ";
		if (Texto[i] == '2')
			cout << "### ";
		if (Texto[i] == '3')
			cout << "### ";
		if (Texto[i] == '4')
			cout << "# # ";
		if (Texto[i] == '5')
			cout << "### ";
		if (Texto[i] == '6')
			cout << "### ";
		if (Texto[i] == '7')
			cout << "### ";
		if (Texto[i] == '8')
			cout << "### ";
		if (Texto[i] == '9')
			cout << "### ";
		if (Texto[i] == '0')
			cout << "### ";
		if (Texto[i] == 'A' || Texto[i] == 'a')
			cout << " #  ";
		if (Texto[i] == 'B' || Texto[i] == 'b')
			cout << "##  ";
		if (Texto[i] == 'C' || Texto[i] == 'c')
			cout << " ## ";
		if (Texto[i] == 'D' || Texto[i] == 'd')
			cout << "##  ";
		if (Texto[i] == 'E' || Texto[i] == 'e')
			cout << "### ";
		if (Texto[i] == 'F' || Texto[i] == 'f')
			cout << "### ";
		if (Texto[i] == 'G' || Texto[i] == 'g')
			cout << " ## ";
		if (Texto[i] == 'H' || Texto[i] == 'h')
			cout << "# # ";
		if (Texto[i] == 'I' || Texto[i] == 'i')
			cout << "### ";
		if (Texto[i] == 'J' || Texto[i] == 'j')
			cout << " ## ";
		if (Texto[i] == 'K' || Texto[i] == 'k')
			cout << "# # ";
		if (Texto[i] == 'L' || Texto[i] == 'l')
			cout << "#   ";
		if (Texto[i] == 'M' || Texto[i] == 'm')
			cout << "# # ";
		if (Texto[i] == 'N' || Texto[i] == 'n')
			cout << "### ";
		if (Texto[i] == 'Ñ' || Texto[i] == 'ñ')
			cout << "*** ";
		if (Texto[i] == 'O' || Texto[i] == 'o')
			cout << " #  ";
		if (Texto[i] == 'P' || Texto[i] == 'p')
			cout << "##  ";
		if (Texto[i] == 'Q' || Texto[i] == 'q')
			cout << " #  ";
		if (Texto[i] == 'R' || Texto[i] == 'r')
			cout << "##  ";
		if (Texto[i] == 'S' || Texto[i] == 's')
			cout << " ## ";
		if (Texto[i] == 'T' || Texto[i] == 't')
			cout << "### ";
		if (Texto[i] == 'U' || Texto[i] == 'u')
			cout << "# # ";
		if (Texto[i] == 'V' || Texto[i] == 'v')
			cout << "# # ";
		if (Texto[i] == 'W' || Texto[i] == 'w')
			cout << "# # ";
		if (Texto[i] == 'X' || Texto[i] == 'x')
			cout << "# # ";
		if (Texto[i] == 'Y' || Texto[i] == 'y')
			cout << "# # ";
		if (Texto[i] == 'Z' || Texto[i] == 'z')
			cout << "### ";
		if (Texto[i] == ' ')
			cout << "    ";
	} cout << endl;
	for (int i = 0; i < Texto.size(); i++){
		if (i == 0){
			for (int j = 0; j < x; j++){
				cout << " ";
			}
		}
		if (Texto[i] == '1')
			cout << "# # ";
		if (Texto[i] == '2')
			cout << "  # ";
		if (Texto[i] == '3')
			cout << "  # ";
		if (Texto[i] == '4')
			cout << "# # ";
		if (Texto[i] == '5')
			cout << "#   ";
		if (Texto[i] == '6')
			cout << "#   ";
		if (Texto[i] == '7')
			cout << "  # ";
		if (Texto[i] == '8')
			cout << "# # ";
		if (Texto[i] == '9')
			cout << "# # ";
		if (Texto[i] == '0')
			cout << "# # ";
		if (Texto[i] == 'A' || Texto[i] == 'a')
			cout << "# # ";
		if (Texto[i] == 'B' || Texto[i] == 'b')
			cout << "# # ";
		if (Texto[i] == 'C' || Texto[i] == 'c')
			cout << "#   ";
		if (Texto[i] == 'D' || Texto[i] == 'd')
			cout << "# # ";
		if (Texto[i] == 'E' || Texto[i] == 'e')
			cout << "#   ";
		if (Texto[i] == 'F' || Texto[i] == 'f')
			cout << "#   ";
		if (Texto[i] == 'G' || Texto[i] == 'g')
			cout << "#   ";
		if (Texto[i] == 'H' || Texto[i] == 'h')
			cout << "# # ";
		if (Texto[i] == 'I' || Texto[i] == 'i')
			cout << " #  ";
		if (Texto[i] == 'J' || Texto[i] == 'j')
			cout << "  # ";
		if (Texto[i] == 'K' || Texto[i] == 'k')
			cout << "# # ";
		if (Texto[i] == 'L' || Texto[i] == 'l')
			cout << "#   ";
		if (Texto[i] == 'M' || Texto[i] == 'm')
			cout << "### ";
		if (Texto[i] == 'N' || Texto[i] == 'n')
			cout << "# # ";
		if (Texto[i] == 'Ñ' || Texto[i] == 'ñ')
			cout << "### ";
		if (Texto[i] == 'O' || Texto[i] == 'o')
			cout << "# # ";
		if (Texto[i] == 'P' || Texto[i] == 'p')
			cout << "# # ";
		if (Texto[i] == 'Q' || Texto[i] == 'q')
			cout << "# # ";
		if (Texto[i] == 'R' || Texto[i] == 'r')
			cout << "# # ";
		if (Texto[i] == 'S' || Texto[i] == 's')
			cout << "#   ";
		if (Texto[i] == 'T' || Texto[i] == 't')
			cout << " #  ";
		if (Texto[i] == 'U' || Texto[i] == 'u')
			cout << "# # ";
		if (Texto[i] == 'V' || Texto[i] == 'v')
			cout << "# # ";
		if (Texto[i] == 'W' || Texto[i] == 'w')
			cout << "# # ";
		if (Texto[i] == 'X' || Texto[i] == 'x')
			cout << "# # ";
		if (Texto[i] == 'Y' || Texto[i] == 'y')
			cout << "# # ";
		if (Texto[i] == 'Z' || Texto[i] == 'z')
			cout << "  # ";
		if (Texto[i] == ' ')
			cout << "    ";
	} cout << endl;
	for (int i = 0; i < Texto.size(); i++){
		if (i == 0){
			for (int j = 0; j < x; j++){
				cout << " ";
			}
		}
		if (Texto[i] == '1')
			cout << "  # ";
		if (Texto[i] == '2')
			cout << "  # ";
		if (Texto[i] == '3')
			cout << " ## ";
		if (Texto[i] == '4')
			cout << "### ";
		if (Texto[i] == '5')
			cout << "### ";
		if (Texto[i] == '6')
			cout << "### ";
		if (Texto[i] == '7')
			cout << " ## ";
		if (Texto[i] == '8')
			cout << "### ";
		if (Texto[i] == '9')
			cout << "### ";
		if (Texto[i] == '0')
			cout << "# # ";
		if (Texto[i] == 'A' || Texto[i] == 'a')
			cout << "### ";
		if (Texto[i] == 'B' || Texto[i] == 'b')
			cout << "##  ";
		if (Texto[i] == 'C' || Texto[i] == 'c')
			cout << "#   ";
		if (Texto[i] == 'D' || Texto[i] == 'd')
			cout << "# # ";
		if (Texto[i] == 'E' || Texto[i] == 'e')
			cout << "##  ";
		if (Texto[i] == 'F' || Texto[i] == 'f')
			cout << "##  ";
		if (Texto[i] == 'G' || Texto[i] == 'g')
			cout << "# # ";
		if (Texto[i] == 'H' || Texto[i] == 'h')
			cout << "### ";
		if (Texto[i] == 'I' || Texto[i] == 'i')
			cout << " #  ";
		if (Texto[i] == 'J' || Texto[i] == 'j')
			cout << "  # ";
		if (Texto[i] == 'K' || Texto[i] == 'k')
			cout << "# # ";
		if (Texto[i] == 'L' || Texto[i] == 'l')
			cout << "#   ";
		if (Texto[i] == 'M' || Texto[i] == 'm')
			cout << "### ";
		if (Texto[i] == 'N' || Texto[i] == 'n')
			cout << "# # ";
		if (Texto[i] == 'Ñ' || Texto[i] == 'ñ')
			cout << "# # ";
		if (Texto[i] == 'O' || Texto[i] == 'o')
			cout << "# # ";
		if (Texto[i] == 'P' || Texto[i] == 'p')
			cout << "##  ";
		if (Texto[i] == 'Q' || Texto[i] == 'q')
			cout << "# # ";
		if (Texto[i] == 'R' || Texto[i] == 'r')
			cout << "##  ";
		if (Texto[i] == 'S' || Texto[i] == 's')
			cout << " #  ";
		if (Texto[i] == 'T' || Texto[i] == 't')
			cout << " #  ";
		if (Texto[i] == 'U' || Texto[i] == 'u')
			cout << "# # ";
		if (Texto[i] == 'V' || Texto[i] == 'v')
			cout << "# # ";
		if (Texto[i] == 'W' || Texto[i] == 'w')
			cout << "### ";
		if (Texto[i] == 'X' || Texto[i] == 'x')
			cout << " #  ";
		if (Texto[i] == 'Y' || Texto[i] == 'y')
			cout << " #  ";
		if (Texto[i] == 'Z' || Texto[i] == 'z')
			cout << " #  ";
		if (Texto[i] == ' ')
			cout << "    ";
	} cout << endl;
	for (int i = 0; i < Texto.size(); i++){
		if (i == 0){
			for (int j = 0; j < x; j++){
				cout << " ";
			}
		}
		if (Texto[i] == '1')
			cout << "  # ";
		if (Texto[i] == '2')
			cout << " #  ";
		if (Texto[i] == '3')
			cout << "  # ";
		if (Texto[i] == '4')
			cout << "  # ";
		if (Texto[i] == '5')
			cout << "  # ";
		if (Texto[i] == '6')
			cout << "# # ";
		if (Texto[i] == '7')
			cout << "  # ";
		if (Texto[i] == '8')
			cout << "# # ";
		if (Texto[i] == '9')
			cout << "  # ";
		if (Texto[i] == '0')
			cout << "# # ";
		if (Texto[i] == 'A' || Texto[i] == 'a')
			cout << "# # ";
		if (Texto[i] == 'B' || Texto[i] == 'b')
			cout << "# # ";
		if (Texto[i] == 'C' || Texto[i] == 'c')
			cout << "#   ";
		if (Texto[i] == 'D' || Texto[i] == 'd')
			cout << "# # ";
		if (Texto[i] == 'E' || Texto[i] == 'e')
			cout << "#   ";
		if (Texto[i] == 'F' || Texto[i] == 'f')
			cout << "#   ";
		if (Texto[i] == 'G' || Texto[i] == 'g')
			cout << "# # ";
		if (Texto[i] == 'H' || Texto[i] == 'h')
			cout << "# # ";
		if (Texto[i] == 'I' || Texto[i] == 'i')
			cout << " #  ";
		if (Texto[i] == 'J' || Texto[i] == 'j')
			cout << "# # ";
		if (Texto[i] == 'K' || Texto[i] == 'k')
			cout << "# # ";
		if (Texto[i] == 'L' || Texto[i] == 'l')
			cout << "#   ";
		if (Texto[i] == 'M' || Texto[i] == 'm')
			cout << "# # ";
		if (Texto[i] == 'N' || Texto[i] == 'n')
			cout << "# # ";
		if (Texto[i] == 'Ñ' || Texto[i] == 'ñ')
			cout << "# # ";
		if (Texto[i] == 'O' || Texto[i] == 'o')
			cout << "# # ";
		if (Texto[i] == 'P' || Texto[i] == 'p')
			cout << "#   ";
		if (Texto[i] == 'Q' || Texto[i] == 'q')
			cout << " ## ";
		if (Texto[i] == 'R' || Texto[i] == 'r')
			cout << "# # ";
		if (Texto[i] == 'S' || Texto[i] == 's')
			cout << "  # ";
		if (Texto[i] == 'T' || Texto[i] == 't')
			cout << " #  ";
		if (Texto[i] == 'U' || Texto[i] == 'u')
			cout << "# # ";
		if (Texto[i] == 'V' || Texto[i] == 'v')
			cout << "# # ";
		if (Texto[i] == 'W' || Texto[i] == 'w')
			cout << "### ";
		if (Texto[i] == 'X' || Texto[i] == 'x')
			cout << "# # ";
		if (Texto[i] == 'Y' || Texto[i] == 'y')
			cout << " #  ";
		if (Texto[i] == 'Z' || Texto[i] == 'z')
			cout << "#   ";
		if (Texto[i] == ' ')
			cout << "    ";
	} cout << endl;
		for (int i = 0; i < Texto.size(); i++){
			if (i == 0){
			for (int j = 0; j < x; j++){
				cout << " ";
			}
		}
		if (Texto[i] == '1')
			cout << "  # ";
		if (Texto[i] == '2')
			cout << "### ";
		if (Texto[i] == '3')
			cout << "### ";
		if (Texto[i] == '4')
			cout << "  # ";
		if (Texto[i] == '5')
			cout << "### ";
		if (Texto[i] == '6')
			cout << "### ";
		if (Texto[i] == '7')
			cout << "  # ";
		if (Texto[i] == '8')
			cout << "### ";
		if (Texto[i] == '9')
			cout << "### ";
		if (Texto[i] == '0')
			cout << "### ";
		if (Texto[i] == 'A' || Texto[i] == 'a')
			cout << "# # ";
		if (Texto[i] == 'B' || Texto[i] == 'b')
			cout << "##  ";
		if (Texto[i] == 'C' || Texto[i] == 'c')
			cout << " ## ";
		if (Texto[i] == 'D' || Texto[i] == 'd')
			cout << "##  ";
		if (Texto[i] == 'E' || Texto[i] == 'e')
			cout << "### ";
		if (Texto[i] == 'F' || Texto[i] == 'f')
			cout << "#   ";
		if (Texto[i] == 'G' || Texto[i] == 'g')
			cout << " ## ";
		if (Texto[i] == 'H' || Texto[i] == 'h')
			cout << "# # ";
		if (Texto[i] == 'I' || Texto[i] == 'i')
			cout << "### ";
		if (Texto[i] == 'J' || Texto[i] == 'j')
			cout << " #  ";
		if (Texto[i] == 'K' || Texto[i] == 'k')
			cout << "# # ";
		if (Texto[i] == 'L' || Texto[i] == 'l')
			cout << "### ";
		if (Texto[i] == 'M' || Texto[i] == 'm')
			cout << "# # ";
		if (Texto[i] == 'N' || Texto[i] == 'n')
			cout << "# # ";
		if (Texto[i] == 'Ñ' || Texto[i] == 'ñ')
			cout << "# # ";
		if (Texto[i] == 'O' || Texto[i] == 'o')
			cout << " #  ";
		if (Texto[i] == 'P' || Texto[i] == 'p')
			cout << "#   ";
		if (Texto[i] == 'Q' || Texto[i] == 'q')
			cout << "  # ";
		if (Texto[i] == 'R' || Texto[i] == 'r')
			cout << "# # ";
		if (Texto[i] == 'S' || Texto[i] == 's')
			cout << "##  ";
		if (Texto[i] == 'T' || Texto[i] == 't')
			cout << " #  ";
		if (Texto[i] == 'U' || Texto[i] == 'u')
			cout << "### ";
		if (Texto[i] == 'V' || Texto[i] == 'v')
			cout << " #  ";
		if (Texto[i] == 'W' || Texto[i] == 'w')
			cout << "# # ";
		if (Texto[i] == 'X' || Texto[i] == 'x')
			cout << "# # ";
		if (Texto[i] == 'Y' || Texto[i] == 'y')
			cout << " #  ";
		if (Texto[i] == 'Z' || Texto[i] == 'z')
			cout << "### ";
		if (Texto[i] == ' ')
			cout << "    ";
	} cout << endl;
}
