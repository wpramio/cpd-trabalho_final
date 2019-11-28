#include <iostream>
#include <string>
#include "estruturas.h"
#include "construcao.h"
#include "interface.h"
#include "Timer.cpp"
using namespace std;

#define RATINGS "minirating.csv"
#define MOVIES "movie.csv"
#define TAGS "tag.csv"

#define KILO 1000
#define MEGA 1000000

int main()
{
	database db;
	trie_tree movies_trie;
	hashtable movies_hash(10, POLINOMIAL, QUADRATIC);
	hashtable users_hash(10, POLINOMIAL, QUADRATIC);
	bool end_app = true;
	movie mtest;
	date dtest;
	rating rtest;
	user utest;
	tag ttest;
	
	ctrl_stats.monitorate_trie(movies_trie);
	ctrl_stats.monitorate_movies_hash(movies_hash);
	ctrl_stats.monitorate_users_hash(users_hash);
	
	// fase de construcao das estruturas
	cout << "Fase de construcao das estruturas:" << endl << endl;;
	ctrl_stats.start_timer();
	
	//movies_trie = construct_trietree_from(MOVIES);
	cout << "Lendo arquivo de filmes. " << "Criando arvore trie." << endl;
	ctrl_stats.print_time_stats();
	ctrl_stats.print_size_stats_of("movies_trie");
	
	//movies_hash = construct_hashtable_from(MOVIES);
	cout << "\nLendo arquivo de filmes. " << "Criando hashtable." << endl;
	ctrl_stats.print_time_stats();
	ctrl_stats.print_size_stats_of("movies_hash");
	
	//users_hash = construct_hashtable_from(RATINGS);
	cout << "\nLendo arquivo de ratings. " << "Criando hashtable." << endl;
	ctrl_stats.print_time_stats();
	ctrl_stats.print_size_stats_of("users_hash");
	
	cout << "\nLendo arquivo de tags. " << "Criando arvore trie." << endl;
	ctrl_stats.print_time_stats();
	
	ctrl_stats.print_total_time_stats();
	
	// trecho de debug
	cout << endl;
	db.read_csv(RATINGS, false);
	ctrl_stats.print_status_message(READING_RATINGS);
	ctrl_stats.print_time_stats();
	db.read_csv_movie(MOVIES, false);
	ctrl_stats.print_status_message(READING_MOVIES);
	ctrl_stats.print_time_stats();
	db.read_csv(TAGS, false);
	ctrl_stats.print_status_message(READING_TAGS);
	ctrl_stats.print_time_stats();
	ctrl_stats.print_total_time_stats();
	cout << "Memoria usada: " << db.get_memory_used(KILO) << " KB" << endl;
	
	/*
	rtest.timestamp.year = 1997;
	rtest.timestamp.month = 05;
	rtest.timestamp.day = 02;
	rtest.timestamp.hour = 11;
	rtest.timestamp.minutes = 35;
	rtest.timestamp.seconds = 59;
	*/
	cout << endl;
	print_movie_header();
	mtest = extract_movie_from("12,\"One(1997)\",\"Adventure|Children|Fantasy|Porn\"");
	mtest.rating_sum = 5332.114;
	mtest.rating_count = 1234;
	print_movie(mtest);
	cout << endl << endl;
	
	dtest = extract_date_from("1999-12-25 12:32:59");
	print_date(dtest);
	cout << endl << endl;
	
	//rtest = extract_rating_from("48644,7067,4.5,2004-01-26 03:58:10");
	//print_rating(rtest);
	cout << endl << endl;
	
	//ttest = extract_tag_from("18,4141,\"Mark Waters\",2009-04-24 18:19:40");
	//print_tag(ttest);
	cout << endl << endl;
	
	// fase de pesquisa
	cout << "Fase de pesquisa: " << endl;
	while (!end_app)
	{
		//queries
	}
	
	return 0;
}