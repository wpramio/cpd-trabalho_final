#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#define POLINOMIAL 1
#define POLINOMIAL_V2 2
#define QUADRATIC 3
#define DOUBLE_HASH 4

class hashtable
{
public:
	int table_size;
	int entry_count;
	int collision_count;
	int hash_type;
	int collision_handler_type;
	
	hashtable(int size, int hash_t, int collision_handler_t) {	// construtor do objeto
		table_size = size;
		memory_used = 0;
		entry_count = 0;
		collision_count = 0;
		hash_type = hash_t;
		collision_handler_type = collision_handler_t;
		
		table = new string[table_size];
		occupied = new bool[table_size];
		used = new bool[table_size];
		
		for (int k=0; k<table_size; k++)	// esvazia tabela
		{
			table[k] = "\0";
			occupied[k] = false;
			used[k] = false;
		}
	};
	
	void insert(string str)
	{
		int key = string_to_key(str);
		int hash = key%table_size;
		int i = 0;
		bool inserted = false;
		
		do
		{
			if (is_empty(hash))	// tentativa de insercao
			{
				table[hash] = str;
				occupied[hash] = true;
				used[hash] = true;
				inserted = true;
				entry_count++;
			}
			else 	// houve colisao, chama o devido resolvedor de colisao
			{
				collision_count++; 
				i++;
				hash = collision_handler(key, i);
			}
		} while (!inserted);
	};
	
	bool remove(string str)
	{
		int key = string_to_key(str);
		int hash = key%table_size;
		int i = 0;
		
		while (true)
		{
			if (used[hash])
				if (occupied[hash] && table[hash] == str)
				{
					occupied[hash] = false;
					return true;
				}
				else
				{
					i++;
					hash = collision_handler(key, i);
				}
			else
				return false;
		};
	};

	int search(string query)
	{
		int acess_count = 0;
		int key = string_to_key(query);
		int hash = key%table_size;
		bool found = false;
		int i = 0;
		
		while (true)
		{
			acess_count++;
			if (used[hash])
				if (occupied[hash] && table[hash] == query)
					return acess_count;
				else
				{
					i++;
					hash = collision_handler(key, i);
				}
			else
				return -1;
		};
	};
	
	int string_to_key(string str)
	{
		int key = 0;
		
		if (hash_type == POLINOMIAL)	// polinomio dos caracteres
		{
			for (int k=0; k < str.size(); ++k)
				key += str[k]*(coef^k);
		}
		else if (hash_type == POLINOMIAL_V2) // // polinomio dos caracteres com quadrado do caractere
		{
			for (int k=0; k < str.size(); ++k)
				key += (str[k]*str[k])*(coef^k);	// acumula produto do quadrado do ascii pelo coeficiente
		}
		return key;
	};
	
	int collision_handler(int key, int i)
	{
		int hash;
		int c1 = 1; int c2 = 1;
		int aux_hash = key%(table_size/2);
		
		if (collision_handler_type == QUADRATIC)	// enderecamento aberto com busca quadratica
			hash = (key + c1*i + c2*i*i)%table_size;
		else if (collision_handler_type == DOUBLE_HASH)	// enderecamento aberto com duplo hashing
			hash = (key + i*aux_hash)%table_size; 
		return hash;
	};
	
	double load_factor()
	{ return ((double)entry_count/(double)table_size); };
	
	long int get_memory_used(int unit=1)
	{
		return (memory_used/unit);
	};
	
	void print_stats(string table_name)
	{
		cout << table_name << endl;
		cout << "Tamanho da tabela: " << table_size << endl;
		cout << "Entradas: " << entry_count << endl;
		cout << "Fator de carga: " << load_factor() << endl;
		cout << "Colisoes: " << collision_count << endl;
		cout << endl;
	};
	
	void print_stats_file(string file_name, string table_name)
	{
		ofstream output (file_name, ios::out | ios::app);
		
		output << table_name << endl;
		output << "Tamanho da tabela: " << table_size << endl;
		output << "Entradas: " << entry_count << endl;
		output << "Fator de carga: " << load_factor() << endl;
		output << "Colisoes: " << collision_count << endl;
		output << endl;
	};
	
	void print_search_stats_file(vector<string> array_consultas, string table_name, string file_name)
	{
		ofstream output (file_name, ios::out | ios::app);
		vector<string> encontrados, nao_encontrados;
		double media_acessos = 0;
		int menor_nro_acessos = 999999, maior_nro_acessos = 0;
		string nome_menor_nro_acessos, nome_maior_nro_acessos;
		
		for (auto full_name : array_consultas)
		{
			int acessos = search(full_name);
			if (acessos == -1)
				nao_encontrados.push_back(full_name);
			else
			{
				media_acessos += acessos;
				encontrados.push_back(full_name);
				if (acessos < menor_nro_acessos)
				{
					menor_nro_acessos = acessos;
					nome_menor_nro_acessos = full_name;
				}
				else if (acessos > maior_nro_acessos)
				{
					maior_nro_acessos = acessos;
					nome_maior_nro_acessos = full_name;
				}
			}
		}
		media_acessos = media_acessos/(double)array_consultas.size();
		
		output << table_name << endl;
		output << "Nomes encontrados:" << endl;
		for (auto full_name : encontrados)
			output << full_name << endl;
		output << "\nNomes nao encontrados:" << endl;
		for (auto full_name : nao_encontrados)
			output << full_name << endl;
		output << "\nMedia de acessos: " << media_acessos << endl;
		output << "Nome com menor numero de acessos: " << nome_menor_nro_acessos << " (" << menor_nro_acessos << " acessos)" << endl;
		output << "Nome com maior numero de acessos: " << nome_maior_nro_acessos << " (" << maior_nro_acessos << " acessos)" << endl;
		output << "********************************************************************************************************" << endl;
	};
	int closest_prime_to(int n) // menor numero primo maior ou igual a n
	{
		int prime;
		int k;
		bool found = false;
		
		if (n < 2)
			return 2;
		
		while (true)
		{
			k = 2;
			while (true) // itera para dividir n por todos os k menores que ele, 
			// enquanto o resto não for zero
			{
				if (k == n)
				{
					found = true;
					break;
				}
				if (n%k == 0)
					break;
				k++;
			}
			if (found)
			{
				prime = n;
				break;
			}
			n++;	
		}
		return prime;
	};
	
private:
	string* table;
	bool* occupied;
	bool* used;
	int coef = closest_prime_to('z');
	long int memory_used;
	
	bool is_empty(int ref) {
		if (occupied[ref] == false) return true; 
		else return false;
	};
};


#endif