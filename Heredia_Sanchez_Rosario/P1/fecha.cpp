#include "fecha.hpp"

using namespace std;

Fecha::Fecha(int dia, int mes, int anno) : dia_(dia), mes_(mes), anno_(anno)
{
	std::time_t tiempo_calendario = std::time(nullptr);
	std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
	if (anno_ == 0) 
		anno_ = tiempo_descompuesto->tm_year +1900;
	if (mes_ == 0) 
		mes_ = tiempo_descompuesto->tm_mon +1 ;
	if (dia_ == 0) 
		dia_ = tiempo_descompuesto->tm_mday;
	validarFecha();
}

Fecha::Fecha(const char* fecha)
{

	std::time_t tiempo_calendario = std::time(nullptr);
	std::tm* tiempo_descompuesto = localtime(&tiempo_calendario);

	int dia,mes,anno;

	int conversiones = sscanf(fecha,"%d/%d/%d", &dia, &mes, &anno);

	if(conversiones!=3)
		throw Invalida("Error en conversion de cadena a fecha");
	else{
		dia_= dia;
		mes_ = mes;
		anno_= anno;
			if(dia_ == 0)
				dia_=tiempo_descompuesto->tm_mday;
			if(mes_ == 0)
				mes_=tiempo_descompuesto->tm_mon+1;
			if(anno_ == 0)
				anno_=tiempo_descompuesto->tm_year+1900;
		validarFecha();
	}
	
}

void Fecha::validarFecha() const
{
	// validar anno
	if (anno_ < AnnoMinimo || anno_ > AnnoMaximo)
		throw Invalida("Error anno fuera de rango.");
	// validar mes
	if (mes_ < 1 || mes_ > 12)
		throw Invalida("Error mes fuera de rango.");
	// validar dia
	if (dia_ < 1)
		throw Invalida("Error dia fuera de rango.");
	if ((mes_ == 1 || mes_ == 3 || mes_ == 5 || mes_ == 7 || mes_ == 8 || mes_ == 10 || mes_ == 12) && dia_ > 31)
		throw Invalida("Error dia fuera de rango.");

	if ((mes_ == 4 || mes_ == 6 || mes_ == 9 || mes_ == 11) && dia_ > 30)
		throw Invalida("Error dia fuera de rango.");

	// febrero
	if (mes_ == 2) {
		if (anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0)) {
			if (dia_ > 29)
				throw Invalida("Error dia fuera de rango");
		} else {
			if (dia_ > 28)
				throw Invalida("Error dia fuera de rango.");
		}
	}
	
}	

Fecha& Fecha::operator +=(int n)
{
	if (n == 0) return *this;
	
	std::tm tiempo_descompuesto={};
	tiempo_descompuesto.tm_mday = dia_ + n;
	tiempo_descompuesto.tm_mon = mes_ - 1;
	tiempo_descompuesto.tm_year = anno_ - 1900;
	mktime(&tiempo_descompuesto);
	dia_ = tiempo_descompuesto.tm_mday;
	mes_ = tiempo_descompuesto.tm_mon + 1;
	anno_ = tiempo_descompuesto.tm_year + 1900;
	validarFecha();
	return *this;
}

Fecha Fecha::operator +(int n)
{
	Fecha f(*this);
	f += n;
	return f;
}

Fecha Fecha::operator -(int n)
{
	Fecha f(*this);
	f += -n;
	return f;
}

Fecha operator +(const Fecha& f, int n)
{
	Fecha g(f);
    g += n;
    return g;
}

Fecha operator -(const Fecha& f, int n)
{
	Fecha g(f);
	g += -n;
	return g;
}

Fecha& Fecha::operator ++()
{
	return *this += 1;
}

Fecha Fecha::operator ++(int)
{
	Fecha f {*this};
	*this += 1;
	return f;
}

Fecha& Fecha::operator --()
{
	return *this += -1;
}

Fecha Fecha::operator --(int)
{
	Fecha f {*this};
	*this += -1;
	return f;
}

Fecha& Fecha::operator -=(int n)
{
	return *this += -n;
}

bool operator ==(const Fecha& fecha1, const Fecha& fecha2)
{
	return (fecha1.dia() == fecha2.dia()
		&& fecha1.mes() == fecha2.mes()
		&& fecha1.anno() == fecha2.anno());
}

bool operator !=(const Fecha& fecha1, const Fecha& fecha2)
{
	return !(fecha1 == fecha2);
}

bool operator <(const Fecha& fecha1, const Fecha& fecha2)
{

	if (fecha1.anno() < fecha2.anno())
        return true;
    else if (fecha1.anno() > fecha2.anno())
        return false;

    if (fecha1.mes() < fecha2.mes())
        return true;
    else if (fecha1.mes() > fecha2.mes())
        return false;

    return fecha1.dia() < fecha2.dia();

}

bool operator <=(const Fecha& fecha1, const Fecha& fecha2)
{
	return (fecha1 < fecha2 || fecha1 == fecha2);
}

bool operator >(const Fecha& fecha1, const Fecha& fecha2)
{
	return !(fecha1 < fecha2 || fecha1 == fecha2);
}

bool operator >=(const Fecha& fecha1, const Fecha& fecha2)
{
	return !(fecha1 < fecha2);
}

const char* Fecha::cadena() const
{
	char const* dias[7] = { "domingo", "lunes", "martes", "miércoles", "jueves", "viernes","sábado" };
	char const* meses[12] = { "enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre" };
	
	std::tm tiempo_descompuesto {0};
	tiempo_descompuesto.tm_mday = dia_;
	tiempo_descompuesto.tm_mon = mes_ - 1;
	tiempo_descompuesto.tm_year = anno_ - 1900;
	mktime(&tiempo_descompuesto);

	char* fecha = new char[40];
    sprintf(fecha, "%s %d de %s de %d", 
    	dias[tiempo_descompuesto.tm_wday],
    	dia_, meses[mes_ - 1], anno_);

    return (const char*)fecha;
}

Fecha::Invalida::Invalida(const char* motivo) : motivo_(motivo) 
{}

const char* Fecha::Invalida::por_que() const
{
	return motivo_;
}

std::istream& operator >>(std::istream& is, Fecha& fecha)
{
    try {
        char cadena[11] = "";
        is.width(11); 
        is >> cadena;
        fecha = Fecha(cadena);  
        return is;
    } catch(const Fecha::Invalida& e) {
        is.setstate(std::ios::failbit);
        throw e;
    }    
}

std::ostream& operator <<(std::ostream& os, const Fecha& fecha)
{
	return os << fecha.cadena();
}