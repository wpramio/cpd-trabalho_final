#include "leitura.cpp"
#include "Timer.cpp"

#define KILO 1000
#define MEGA 1000000

class date
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
};

class rating
{
	//int rating_id;	//MAYBE
	int user_id;
	int movie_id;
	double rating_value;
	date timestamp;
};

class movie 
{
	int id;
	string title;
	list<string> genres;
};

class tag 
{
	int user_id;
	string tag_content;
	list<int> movie_id_list;
	date timestamp; // precisa?
};

class user
{
	int id;
	list<rating> ratings_list; // precisa?
	list<tag> tags_list; // precisa?
};

class trie_tree
{
	public:
		int index;
		void insert()
		{
			index = 1;
		};
};

class control_stats
{
	public:
		double exec_time;
		int movies_size;
		int ratings_size;
		int tags_size;
		void start_timer()
		{
			my_timer.start();
		};
		void get_time()
		{
			exec_time = my_timer.get_lap();
		};
		void print_time_stats()
		{
			cout << "Tempo de execucao: " << exec_time << " ms" << endl;
		};
		void print_size_stats()
		{
			cout << "Tamanho da estrutura de filmes:" << movies_size << " bytes" << endl;
			cout << "Tamanho da estrutura de ratings:" << ratings_size << " bytes" << endl;
			cout << "Tamanho da estrutura de tags:" << tags_size << " bytes" << endl;
		};
		void print_all_stats()
		{
			print_time_stats();
			print_size_stats();
		}
	private:
		Timer my_timer;
} ctrl_stats;

#define RATINGS "minirating.csv"
#define MOVIES "movie.csv"
#define TAGS "tag.csv"

int main()
{
	database db;
	bool end_app = true;
	
	Timer my_timer;
	
	// fase de construcao das estruturas
	ctrl_stats.start_timer();
	db.read_csv_cbc(RATINGS, true);
	db.read_csv(MOVIES);
	db.read_csv(TAGS);
	ctrl_stats.get_time();
	ctrl_stats.print_time_stats();
	cout << "Memoria usada: " << db.get_memory_used(KILO) << " KB" << endl;
	
	// fase de pesquisa
	while (!end_app)
	{
		//queries
	}
	
	return 0;
}