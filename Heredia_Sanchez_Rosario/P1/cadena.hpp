#ifndef CADENA_HPP
#define CADENA_HPP

#include <iostream>
#include <iterator>
#include <functional>
#include <cstring>
#include <stdexcept>

class Cadena {
public:
	explicit Cadena(size_t tam = 0, char caracter = ' ');
	Cadena(const Cadena& cadena);
	Cadena(Cadena&& cadena);
	Cadena(const char* cadena);
	
	Cadena& operator =(const Cadena& cadena);
	Cadena& operator =(Cadena&& cadena);
	
	
	inline const char* c_str() const noexcept{return s_;} 
	inline size_t length() const noexcept{return tam_;}
	
	Cadena& operator +=(const Cadena& cadena);
	Cadena& operator =(const char* cadena);

	Cadena substr(size_t indice, size_t tam) const;
	
	char operator [](size_t i) const noexcept;
    char& operator [](size_t i) noexcept;
	char at(size_t i) const;
    char& at(size_t i);
	~Cadena();

	typedef char* iterator;
	typedef char const* const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    inline iterator begin() noexcept{return s_;}
    inline iterator end() noexcept{return (s_+tam_);} // s lo posicionas en la última pos
    inline reverse_iterator rbegin() noexcept{return reverse_iterator(end());}
    inline reverse_iterator rend() noexcept{return reverse_iterator(begin());}
    inline iterator begin() const noexcept{return s_;}
    inline iterator end() const noexcept{return (s_+tam_);}
    inline const_iterator cbegin() const noexcept{return s_;}
    inline const_iterator cend() const noexcept{return (s_+tam_);}
    inline const_reverse_iterator rbegin() const noexcept{return const_reverse_iterator(end());}
    inline const_reverse_iterator rend() const noexcept{return const_reverse_iterator(begin());}
    inline const_reverse_iterator crbegin() const noexcept{return const_reverse_iterator(end());}
    inline const_reverse_iterator crend() const noexcept{return const_reverse_iterator(begin());}


private:
	char* s_;
	size_t tam_;
};

Cadena operator +(const Cadena& cadena1, const Cadena& cadena2);

bool operator == (const Cadena& cadena1, const Cadena& cadena2);
bool operator != (const Cadena& cadena1, const Cadena& cadena2);
bool operator < (const Cadena& cadena1, const Cadena& cadena2);
bool operator <= (const Cadena& cadena1, const Cadena& cadena2);
bool operator > (const Cadena& cadena1, const Cadena& cadena2);
bool operator >= (const Cadena& cadena1, const Cadena& cadena2);

std::istream& operator >>(std::istream& is, Cadena& cadena);
std::ostream& operator <<(std::ostream& os, const Cadena& cadena);

namespace std {
	template <> struct hash<Cadena>
	{
		size_t operator()(const Cadena& cad) const
		{ 
			return hash<string>{}(cad.c_str());
		}
	};
}

#endif /* CADENA_HPP */
