#ifndef __RELATED_CODE_H__
#define __RELATED_CODE_H__

#include <vector>

#include "disassembly/disassembler.h"
#include "code_element.h"

std::vector<unsigned int> make_combination(int num);
std::vector<code_element *> make_group(int num);
unsigned int get_index(std::vector<code_element*> gr, code_element *b);
bool element_present(std::vector<code_element*> gr, address a);
bool reference_present(std::vector<code_element*> gr, address a);
bool non_self_reference(std::vector<code_element*> gr, address a);

class related_code
{
	public:
		related_code();
		address start_address;
		void add_block(code_element *c);
		void gather_instructions(disassembler &disas);
		void get_calls(std::vector<address> &c);	//get a list of addresses called as functions
		void fprint(std::ostream &dest, int depth);
		void print_graph(std::ostream &dest);
		void simplify();
		bool simplified();
	private:
		std::vector<code_element *> blocks;	//The basic elements of code
		void finalize_blocks();
		code_element *get_block(address a);	//return the block starting with address a
		void replace_element(code_element* old, code_element *n);
		void replace_group(std::vector<code_element*>a, code_element *b);
		std::vector<code_element *> outside_references(std::vector<code_element *> gr);
		std::vector<code_element *> external_inputs(std::vector<code_element *> gr);
		void apply_combination(std::vector<unsigned int> cmb, std::vector<code_element *> &gr);
		bool next_combo(std::vector<unsigned int> &cmb);
		int process_blocks(int n);
};

#endif
