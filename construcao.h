#ifndef _CONSTRUCAO_H
#define _CONSTRUCAO_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "estruturas.h"
#include "interface.h"
using namespace std;

void construct_trietree_from(string filename)
{
	
};

void construct_hashtable_from(string filename)
{
	
};

date extract_date_from(const string& rawdata)
{
	date new_date;
	string extraction_piece;
	extraction_piece = rawdata.substr(0, 4);	// year
	new_date.year = stoi(extraction_piece, nullptr);
	extraction_piece = rawdata.substr(5, 2);	// month
	new_date.month = stoi(extraction_piece, nullptr);
	extraction_piece = rawdata.substr(8, 2);	// day
	new_date.day = stoi(extraction_piece, nullptr);
	extraction_piece = rawdata.substr(11, 2);	// hour
	new_date.hour = stoi(extraction_piece, nullptr);
	extraction_piece = rawdata.substr(14, 2);	// minutes
	new_date.minutes = stoi(extraction_piece, nullptr);
	extraction_piece = rawdata.substr(17, 2);	// seconds
	new_date.seconds = stoi(extraction_piece, nullptr);
	return new_date;
};

rating extract_rating_from(const string& rawdata)
{
	rating new_rating;
	
	return new_rating;
};

tag extract_tag_from(const string& rawdata)
{
	tag new_tag;
	
	return new_tag;
};

movie extract_movie_from(const string& rawdata)
{
	movie new_movie;
	string extraction_piece;
	size_t fquote, lquote, fbar, lbar, fcolon;
	// movie_id
	fcolon = rawdata.find(',');	// encontra a posicao da primeira virgula
	extraction_piece = rawdata.substr(0, fcolon); // extrai substring do inicio ate antes da virgula
	if (!extraction_piece.empty())
		new_movie.id = stoi(extraction_piece, nullptr);	// transforma substring em inteiro
	// movie_id
	// title
	fquote = rawdata.find('\"', fcolon+1); // encontra primeira aspa dupla
	lquote = rawdata.find('\"', fquote+1); // encontra a posicao da aspa dupla correspondente
	new_movie.title = rawdata.substr(fquote+1, (lquote - fquote) - 1); // extrai substring entre as duas aspas
	// title
	// genres_list
	fquote = rawdata.find('\"', lquote+1);
	lquote = rawdata.find('\"', fquote+1);
	lbar = fquote; // primeiro separador eh a aspa
	while(lbar != string::npos) // enquanto nao chegar ao fim da string
	{
		fbar = rawdata.find("|", lbar+1); // encontra posicao do proximo separador
		if (fbar != string::npos)
			extraction_piece = rawdata.substr(lbar+1, (fbar - lbar) - 1); // extrai substring entre dois separadores
		else
			extraction_piece = rawdata.substr(lbar+1, (lquote - lbar) - 1);	// evita a extracao da aspa dupla final
		lbar = fbar; // ultimo separador guarda o inicio da substring seguinte
		if (!extraction_piece.empty())
			new_movie.genres_list.push_back(extraction_piece);	// insere termo na lista
	}
	// genres_list
	return new_movie;
};

class database 
{
public:
	ifstream input_stream;
	database()
	{
		memory_used = 0;
	};
	void read_csv_movie(string filename, bool print_str=false, bool skip_header=true)
	{
		input_stream.open(filename);
		char* str_read = new char[400];
		string extract;
		movie new_movie;
		
		if (input_stream.is_open())
		{
			if (skip_header)	// skip_header indica se eh necessario pular o cabecalho
				input_stream.ignore(256, '\n');
			while(!input_stream.eof())
			{
				input_stream.getline(str_read, 400);
				extract = str_read;
				if (extract != "\n")
					new_movie = extract_movie_from(extract);
				if (print_str)
				{
					print_movie(new_movie);
					cout << endl;
				}
				memory_used += sizeof(new_movie);
			}
		}
		input_stream.close();
	};
	void read_csv(string filename, bool print_str=false, bool skip_header=true)
	{
		input_stream.open(filename);
		char* str_read = new char[400];
		
		if (input_stream.is_open())
		{
			if (skip_header)	// skip_header indica se eh necessario pular o cabecalho
				input_stream.ignore(256, '\n');
			while(!input_stream.eof())
			{
				input_stream.getline(str_read, 400);
				if (print_str)
					cout << "string: " << str_read << endl;
				memory_used += sizeof(str_read);
			}
		}
		input_stream.close();
	};
	void read_csv_cbc(string filename, bool print_str=false, bool skip_header=true)
	{
		input_stream.open(filename);
		char chr_read;
		char* str_read = new char[256];
		int chr_count = 0;
		//string str_read;
		
		if (input_stream.is_open())
		{
			if (skip_header)	// skip_header indica se eh necessario pular o cabecalho
				input_stream.ignore(256, '\n');
			while(!input_stream.eof())
			{
				// le caracteres ate encontrar o fim de uma palavra: virgula ou nova linha
				input_stream.get(chr_read);
				if (chr_read != ',' && chr_read != '\n')
				{
					str_read[chr_count++] = chr_read;
				}
				else	// chegou ao fim da palavra; finaliza a string
				{
					str_read[chr_count] = '\0';
					chr_count = 0;
					if (print_str)
						cout << "string: " << str_read << endl;
					memory_used += sizeof(str_read);
				}
			}
		}
		input_stream.close();
	};
	long int get_memory_used(int unit=1)
	{
		return (memory_used/unit);
	};
private:
	long int memory_used;
};

#endif