#include "cadena.hpp"

Cadena::Cadena(size_t tam, char caracter) : s_{new char[tam+1]}, tam_{tam}
{
	for (size_t i = 0; i < tam_; i++)
		s_[i] = caracter;

	s_[tam_] = '\0';
}

Cadena::Cadena(const Cadena& cadena) : s_{new char[cadena.tam_+1]}, tam_{cadena.tam_}
{
	for (size_t i = 0; i < tam_; i++)
		s_[i] = cadena.s_[i];

	s_[tam_] = '\0';
}

Cadena::Cadena(Cadena&& cadena) : s_{cadena.s_}, tam_{cadena.tam_}
{
	cadena.tam_ = 0;
	cadena.s_ = nullptr;
}

Cadena::Cadena(const char* cadena) : s_{new char[strlen(cadena)+1]}, tam_{strlen(cadena)}
{
	strcpy(s_, cadena);
	s_[tam_]='\0';
}

Cadena& Cadena::operator =(const Cadena& cadena)
{
	if (this != &cadena) 
	{
		if (tam_ != cadena.tam_) {
			tam_ = cadena.tam_;
			delete[] s_;
			s_ = new char[tam_+1];
		}
		for (size_t i = 0; i <= tam_; i++) 
			s_[i] = cadena.s_[i];
	}
	return *this;
}

Cadena& Cadena::operator =(Cadena&& cadena)
{
	if (this != &cadena) 
	{
		tam_ = cadena.tam_;
		delete[] s_;
		s_ = cadena.s_;
		cadena.tam_=0;
		cadena.s_=nullptr;	
	}
	return *this;
}

Cadena& Cadena::operator =(const char* cadena)
{
	delete[] s_;
	tam_ = strlen(cadena);
	s_ = new char[strlen(cadena)+1];
	strcpy(s_, cadena);
	
	return *this; 
}

Cadena& Cadena::operator +=(const Cadena& cadena)
{
	Cadena copia {*this};
	tam_ += cadena.tam_;
	delete[] s_;
	s_ = new char [tam_+ 1];
	strcpy(s_, copia.s_);
	strcat(s_, cadena.s_);

	return *this;
}

Cadena operator +(const Cadena& cadena1, const Cadena& cadena2)
{
	Cadena c1 {cadena1};
	return c1 += cadena2;
}

Cadena Cadena::substr(size_t indice, size_t tam) const
{
	if (indice >= length())
		throw std::out_of_range("Error en subcadena: posicion inicial mayor que longitud.");
	if (tam > length() - indice)
		throw std::out_of_range("Error en subcadena: tamanno mayor que longitud restante.");
	if (indice + tam > tam_)
		throw std::out_of_range("Error en subcadena: tammano excesivo");
	Cadena c {tam};
	for (size_t i = 0; i < tam; i++)
		c.s_[i] = s_[indice+i];
	return c;
}

inline char Cadena::operator[](size_t i) const noexcept
{ 
	return s_[i]; 
}

char& Cadena::operator[](size_t i) noexcept
{ 
	return s_[i]; 
}

char Cadena::at(size_t i) const
{
	if (i >= length())
		throw std::out_of_range("Rango invalido");
	return s_[i];
}

char& Cadena::at(size_t i)
{
	if (i >= length())
		throw std::out_of_range("Rango invalido");
	return s_[i];
}

bool operator == (const Cadena& cadena1, const Cadena& cadena2)
{
	if (cadena1.length() != cadena2.length()) return false;
	for (size_t i = 0; i < cadena1.length(); i++) {
		if (cadena1[i] != cadena2[i]) return false;
	}
	return true;
}

bool operator != (const Cadena& cadena1, const Cadena& cadena2)
{
	return !(cadena1 == cadena2);
}

bool operator < (const Cadena& cadena1, const Cadena& cadena2)
{
	size_t min = 0;
	if (cadena1.length() < cadena2.length()) 
		min = cadena1.length();
	else
		min = cadena2.length();
	for (size_t i = 0; i < min; i++) {
		if (cadena1[i] < cadena2[i]) return true;
		if (cadena1[i] > cadena2[i]) return false;
	}
	return cadena1.length() < cadena2.length();
}

bool operator <= (const Cadena& cadena1, const Cadena& cadena2)
{
	return (cadena1 < cadena2 || cadena1 == cadena2);
}

bool operator > (const Cadena& cadena1, const Cadena& cadena2)
{
	return !(cadena1 <= cadena2);
}

bool operator >= (const Cadena& cadena1, const Cadena& cadena2)
{
	return (cadena1 > cadena2 || cadena1 == cadena2);
}

Cadena::~Cadena()
{
	delete[] s_;
}

std::istream& operator >>(std::istream& is, Cadena& cadena)
{
	char palabra[33]="";
  	is.width(33);
  	is>>palabra;
  	cadena=palabra;
  	return is;
}

std::ostream& operator <<(std::ostream& os, const Cadena& cadena)
{
	os << cadena.c_str();
	return os;
}

