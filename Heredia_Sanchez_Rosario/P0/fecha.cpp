#include <ctime>
#include <iostream>
#include "fecha.hpp"

unsigned namespace std;

////FUNCIONES PRIVATE////
void Fecha::actualiza() 
{
	try
	{
		while(mm_>12)
		{
			mm_-=12;
			aaaa_++;
		}
		while (dd_ > dia_max())
		{
			dd_ -= dia_max();
			if (++mm_ > 12)
			{
				mm_ = 1;
				aaaa_++;
			}
		}
		while (dd_ <= 0)
		{
			if (--mm_ <=0)
			{
				mm_ = 12;
				aaaa_--;
			}
			dd_ += dia_max();
		}
		if(!comprueba()) {Fecha::Invalida in("Fecha invalida"); throw in;}

	}//try
	catch(Fecha::Invalida in) {cerr<<in.por_que()<<endl;}
}

bool Fecha::comprueba()const
{
	return !(dd_>dia_max() || dd_<1 || mm_>12 || mm_<1 || aaaa_>Fecha::AnnoMaximo || aaaa_< Fecha::AnnoMinimo);
}

int Fecha::dia_max() const
{
	try
	{
		if(mm_ == 1 || mm_ == 3 || mm_ == 5 || mm_ == 7 || mm_ == 8 || mm_ == 10 || mm_ == 12 ) return 31;
		
		//el mes es de 31 días
		else if(mm_ == 4 || mm_ == 6 || mm_ == 9 || mm_ == 11 ) return 30;
		
		//el mes es de 30 días
		else if(mm_ == 2 )
		{
			//¿AÑO BISIESTO?//
			if (aaaa_ % 4 == 0 && (aaaa_ % 400 == 0 || aaaa_ % 100 != 0)) return 29;
		
			//año bisiesto - febrero de 29 días
			else return 28;
		
		//año no bisiesto - febrero con 28 días
		}else {Fecha::Invalida in("Mes invalido"); throw in;}
	}//try
		catch (Fecha::Invalida in) {cerr << in.por_que() << endl;}
	
	return 0;
}

////INVALIDA////
Fecha::Invalida::Invalida(const char *in): info_(in){}
inline const char* Fecha::Invalida::por_que()const{return info_;}

////CONSTRUCTOR////
Fecha::Fecha(int dd, int mm, int aaaa) :dd_(dd), mm_(mm), aaaa_(aaaa)
{
	std::time_t tiempo_calendario = std::time(0);
	std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
	if(aaaa_==0) aaaa_ = tiempo_descompuesto->tm_year + 1900;
		else while(aaaa_>9999) aaaa_/=10; //se toma solo los 4 primeros dígitos del año, si se introducen más se descartan
	if(mm_==0) mm_ = tiempo_descompuesto->tm_mon + 1;
	if(dd_==0) dd_ = tiempo_descompuesto->tm_mday;