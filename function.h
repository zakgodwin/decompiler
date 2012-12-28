#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <fstream>
#include <iostream>
#include <vector>

#include "code_element.h"
#include "config.h"
#include "ce_block.h"

class function
{
	public:
		function(address addr, const char *n, disassembler &disas);
		function(address addr, disassembler &disas);
		~function();
		std::vector<address> get_calls();	//get a list of addresses called as functions
		void simplify();
		void set_name(const char *to);
		std::string get_name();
		address gets();
		friend std::ostream& operator << (std::ostream& output, function &me);
	private:
		std::string name;
		address s;
		std::vector<instr*> da_lines;	//all the lines of code for the function (delete these when done)
		std::vector<ce_block *> c_blocks;	//the basic blocks of instructions (delete these when done)
		std::vector<code_element *> xblocks; //extra blocks created to simplify logic (delete these when done)
		std::vector<code_element *> pieces;
		void remove_piece(code_element *rmv);	//removes a piece
		void replace_references(code_element *old, code_element *nw);

		//constructor helpers
		void work_on_block(address addr);
		void add_line(instr *addme);	//add a line of code to the function
		void finish_block(address addr);
		
		//used for simplification
		int find_if_else();
		int do_simple_if(code_element *a, code_element *b, int i);
		int do_multi_if(int i);
		int do_if_else(int i);
		int find_loop();
		int find_runs();
		//used for output
		void fprint(std::ostream& output);
};

#endif
