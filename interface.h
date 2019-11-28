#ifndef _INTERFACE_H
#define _INTERFACE_H

#include <string>
#include "windows.h"
#include "estruturas.h"
using namespace std;

void print_date(const date& D)
{
	
	cout << D.year << '/' << D.month << '/' << D.day << ' ' << D.hour << '|' << D.minutes << '|' << D.seconds << endl;
};

void print_rating(const rating& R)
{
	cout << R.rating_id << '\t' << R.user_id << '\t' << R.movie_id << '\t' << R.rating_value << '\t';
	print_date(R.timestamp);
};

void print_movie(const movie& M)
{
	cout << M.id << '\t' << M.title << '\t';
	for (auto G : M.genres_list)
		cout << G << '/';
	cout << '\t' << M.rating_sum/(double)M.rating_count << '\t' << M.rating_count << endl;
};

void print_tag(const tag& T)
{
	cout << T.user_id << '\t' << T.tag_content << '\t';
	for (auto i : T.movie_id_list)
	print_date(T.timestamp);
};

void print_user(const user& User)
{
	//movie* assoc_movie;
	for (auto R: User.ratings_list)
	{
		// apenas uma funcao para obter endereco do filme a partir da tabela hash; usos subsequentes apenas acessam o endereco
		// assoc_movie = get_movie_pointer(R.movie_id);
		// if (assoc_movie != nullptr)
			//cout << R.rating_value << '\t' << M << assoc_movie->title << assoc_movie->global_rating << '\t' << assoc_movie->rating_count << endl;
		
		// 3 chamadas de funcao para acessar os valores de 1 mesmo filme
		//cout << R.rating_value << '\t' << get_movie_title(R.movie_id) << get_movie_globalrating(R.movie_id) << get_movie_ratingcount(R.movie_id) << endl;
		cout << R.rating_value << '\t' << R.movie_id << endl;
	}
};

void print_movie_header()
{
	cout << "movie_id" << '\t' << "title" << '\t' << "genres" << '\t' << "rating" << '\t' << "count" << endl;
};

void print_user_header()
{
	cout << "user_rating" << '\t' << "title" << '\t' << "global_rating" << '\t' << "count" << endl;
};

void search_user(int user_id)
{
	user* User;
	movie* assoc_movie;
	//User = get_user_pointer(user_id);
	for (auto R: User->ratings_list)
	{
		// apenas uma funcao para obter endereco do filme a partir da tabela hash; usos subsequentes apenas acessam o endereco
		// assoc_movie = get_movie_pointer(R.movie_id);
		// if (assoc_movie != nullptr)
			//cout << R.rating_value << '\t' << M << assoc_movie->title << assoc_movie->global_rating << '\t' << assoc_movie->rating_count << endl;
		
		// 3 chamadas de funcao para acessar os valores de 1 mesmo filme
		//cout << R.rating_value << '\t' << get_movie_title(R.movie_id) << get_movie_globalrating(R.movie_id) << get_movie_ratingcount(R.movie_id) << endl;
		cout << R.rating_value << '\t' << R.movie_id << endl;
	}
	
};

void clear_screen()
{
	HANDLE hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count;
	DWORD cellCount;
	COORD homeCoords = {0, 0};

	// handle para o buffer atual
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;
  // Obtem o numero de celulas no buffer atual
	if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) 
		return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;
  // Preenche o buffer com espacos
	if (!FillConsoleOutputCharacter(hStdOut, (TCHAR) ' ', cellCount, homeCoords, &count)) 
		return;
  // Preenche todo o buffer com as cores e atributos atuais
	if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count))
		return;
  // Move o cursor para o inicio
	SetConsoleCursorPosition( hStdOut, homeCoords );
};

#endif