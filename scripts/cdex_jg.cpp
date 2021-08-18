#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

void write_to_dict (string dic, vector<string> names, vector<string> path)
{// write to path_dict
	ofstream out(dic);
	for (int i=0 ; i<names.size(); i++){
		out << names[i] << " " << path[i] << endl;
	}
	out.close();
}

void swap_v (int a, int b, vector<string> &v_key, vector<string> &v_val)
{// Swap value
	string tmp_k=v_key[a], tmp_v=v_val[a];
	v_key[a] = v_key[b];
	v_val[a] = v_val[b];
	v_key[b] = tmp_k;
	v_val[b] = tmp_v;
}

void print_dict(vector<string> v_key, vector<string> v_val)
{
	cout << "Dictionay: \n";
	for (int i=0; i<v_key.size(); i++){
		cout << "(" << i << ") " << v_key[i] << ": " << v_val[i] << endl;
	}
}

int main(int argc, char const *argv[])
{
	unordered_map<string, int> um;	// faster find operations
	vector<string> v_key, v_val;		// for random access
	string 	key="", val="",
			source_direc = "/home/yzlin/Shells/cdex",
			action_out = "", action_file = source_direc + "/action",
			dictionary = source_direc + "/path_set.txt",
			help = "./help.txt";
	int target=0, now=0, i=0;

	fstream path_dict;
	try{
		path_dict.open(dictionary, ios::in);
	}
	catch(exception ex){
		cerr << ex.what() << endl;
		cerr << "CANT find path_dict." << endl;
		return -1;
	}

	// Build umap and vector
	while (path_dict >> key >> val)
	{
		um[key] = i++;
		v_key.push_back(key);
		v_val.push_back(val);
	}


	// add path
	if (argc == 4){
		if (string(argv[1]) == "add"){
			if (um.find(argv[2]) != um.end()){
				cerr << "TARGET error: \"" << argv[2] << "\" has existed." << endl;
			}
			else{
				string name_p = argv[2], p = argv[3];
				v_key.push_back(name_p);
				v_val.push_back(p);

				write_to_dict(dictionary, v_key, v_val);
				cout << name_p << ": " << p << " appened." << endl;
			}
		}
		else{
			cout << "COMMAND error: undefined command -> " << argv[1] << "." << endl;
		}
	}
	// del set setn
	else if (argc == 3){
		// del
		if (string(argv[1]) == "del"){
			string target = argv[2];
			if (um.find(target) == um.end()){
				cerr << "TARGET error: \"" << argv[2] << "\" doesn't existed." << endl;
			}
			else{	// delete target
				auto it = um.find(target);

				v_key.erase(v_key.begin()+it->second);
				v_val.erase(v_val.begin()+it->second);
				
				write_to_dict(dictionary, v_key, v_val);
				cout << target << " erased." << endl; 
			}
		}
		// set
		else if (string(argv[1]) == "set"){
			string target = argv[2];
			if (um.find(target) == um.end()){
				cerr << "TARGET error: \"" << argv[2] << "\" doesn't existed." << endl;
			}
			else{	// set to first
				auto it = um.find(target);

				swap_v(0, it->second, v_key, v_val);
				write_to_dict(dictionary, v_key, v_val);
				
				cout << target << " (" << v_val[it->second] << ") has set." << endl; 
			}
		}
		// setn
		else if (string(argv[1]) == "setn" || string(argv[1]) == "-sn"){
			int target=-2;
			bool can_convert = true;
			try{
				string j = string(argv[2]);
				target = stoi(j);
			}
			catch(invalid_argument){
				can_convert = false;
			}

			if (!can_convert){
				cerr <<  "TARGET error: must input a \"n\"umber" << endl;
			}
			else if (target >= v_key.size() || target < 0){
				print_dict(v_key, v_val);
				cerr << "TARGET error: \"" << target << "\" are not in "
					 << "0 ~ " << to_string(v_key.size()-1) << endl;
			}
			else{	// set to first
				swap_v(0, target, v_key, v_val);
				write_to_dict(dictionary, v_key, v_val);
				
				cout << v_key[0] << " (" << v_val[0] << ") has set." << endl; 
			}
		}
	}
	// show help
	else if (argc == 2){
		string cmd = string(argv[1]);
		// show
		if (cmd == "show" || cmd == "-s"){
			print_dict(v_key, v_val);
		}
		// help
		else if (cmd == "help"){
			ifstream in(help);
			string eat;
			while (getline(in, eat)){
				cout << eat << endl;
			}
			in.close();
		}
		else{
			cout << "COMMAND error: undefined command -> " << cmd << "." << endl;
		}
	}
	// go
	else if (argc == 1){
		cout << v_val[0] << endl;
	}


	// write for .sh action judge
	ofstream out(action_file);
	out << action_out;
	out.close();

	path_dict.close();
	return 0;
}
