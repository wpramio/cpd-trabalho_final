#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;

class database 
{
	public:
		ifstream input_stream;
		database()
		{
			memory_used = 0;
		};
		void read_csv(string filename, bool print_str=false, bool skip_header=true)
		{
			input_stream.open(filename);
			char* str_read;
			//string str_read;
			
			if (input_stream.is_open())
			{
				if (skip_header)	// skip_header indica se eh necessario pular o cabecalho
					input_stream.ignore(256, '\n');
				while(!input_stream.eof())
				{
					input_stream.getline(str_read, 256, ',');
					//getline(input_stream, str_read, ',');
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
					input_stream.get(chr_read);
					if (chr_read != ',' && chr_read != '\n')
					{
						str_read[chr_count++] = chr_read;
					}
					else
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
		void read_csv_to_string(string filename, bool print_str=false, bool skip_header=true)
		{
			input_stream.open(filename);
			string str_read;
			
			if (input_stream.is_open())
			{
				if (skip_header)	// skip_header indica se eh necessario pular o cabecalho
					input_stream.ignore(256, '\n');
				while(!input_stream.eof())
				{
					getline(input_stream, str_read, ',');
					if (print_str)
						cout << str_read << endl;
					memory_used += sizeof(str_read);
				}
			}
			input_stream.close();
		};
		long int get_memory_used(int unit=1)
		{
			return (memory_used/unit);
		}
	private:
		long int memory_used;
		void get_word(char* str)
		{
			char chr_read;
			int chr_count = 0;
			if (input_stream.good())
				do 
				{
					input_stream.get(chr_read);
					str[chr_count++] = chr_read;
				} while (chr_read != ',' && chr_read != '\n');
		};
};