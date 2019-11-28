#ifndef _ESTRUTURAS_H
#define _ESTRUTURAS_H

#include <string>
#include <list>
#include "trietree.h"
#include "hashtable.h"
#include "Timer.h"
using namespace std;

#define KILO 1000
#define MEGA 1000000

class date
{
public:
	int year;
	int month;
	int day;
	int hour;
	int minutes;
	int seconds;
};

class rating
{
public:
	int rating_id;	//MAYBE
	int user_id;
	int movie_id;
	double rating_value;
	date timestamp;
};

class movie 
{
public:	
	int id;
	string title;
	list<string> genres_list;
	double global_rating;
	double rating_sum;
	int rating_count;
	double get_global_rating()
	{
		return (rating_sum/(double)rating_count);
	};
};

class tag 
{
public:	
	int user_id;
	string tag_content;
	list<int> movie_id_list;
	date timestamp; // precisa?
};

class user
{
public:	
	int id;
	list<rating> ratings_list; // precisa?
	list<tag> tags_list; // precisa?
};

class control_stats
{
public:
	double exec_time;
	trie_tree* movies_trie;
	hashtable* movies_hash;
	hashtable* users_hash;
	
	void monitorate_trie(trie_tree& T)
	{
		movies_trie = &T;
	};
	void monitorate_movies_hash(hashtable& Ht)
	{
		movies_hash = &Ht;
	};
	void monitorate_users_hash(hashtable& Ht)
	{
		users_hash = &Ht;
	};
	
	void start_timer()
	{
		my_timer.start();
	};
	void print_time_stats()
	{
		exec_time = my_timer.get_lap();
		cout << "Tempo de execucao: " << exec_time << " ms" << endl;
	};
	void print_total_time_stats()
	{
		exec_time = my_timer.get_total();
		cout << "Tempo total de execucao: " << exec_time << " ms" << endl;
	};
	void print_size_stats_of(string struc_option="all")
	{
		if (struc_option == "all" || struc_option == "movies_trie")
			cout << "Tamanho da arvore trie de filmes: " << movies_trie->get_memory_used(KILO) << " KB" << endl;
		if (struc_option == "all" || struc_option == "movies_hash")
			cout << "Tamanho da hashtable de filmes: " << movies_hash->get_memory_used(KILO) << " KB" << endl;
		if (struc_option == "all" || struc_option == "users_hash")
			cout << "Tamanho da hashtable de user: " << users_hash->get_memory_used(KILO) << " KB" << endl;
	};
	void print_all_stats()
	{
		print_time_stats();
		print_size_stats_of("all");
	};
	void print_status_message(int message_code)
	{
		#define READING_RATINGS 1
		#define READING_MOVIES 2
		#define READING_TAGS 3
		#define CREATING_TRIE 4
		#define CREATING_HASH 5
		switch (message_code)
		{
			case READING_RATINGS:
				cout << "Lendo arquivo de ratings." << endl;
				break;
			case READING_MOVIES:
				cout << "Lendo arquivo de filmes." << endl;
				break;
			case READING_TAGS:
				cout << "Lendo arquivo de tags." << endl;
				break;
			case CREATING_TRIE:
				cout << "Criando arvore trie." << endl;
				break;
			case CREATING_HASH:
				cout << "Criando tabela hash." << endl;
				break;
		}
	};
private:
	Timer my_timer;
} ctrl_stats;

#endif