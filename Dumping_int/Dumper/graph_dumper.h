#include "../Int/my_int.h"
#include "../Tools/stack.h"

#ifndef GRAPH_DUMPER_H
#define GRAPH_DUMPER_H

struct Node_identity;

#include <string.h>
#include <vector>

struct Node_identity {
	size_t left_id;
	Type_functions type;
	size_t right_id;
	bool is_binary;
	bool is_used;

	Node_identity() {
		left_id = right_id = 0;
		is_used = is_binary = false;
		type = Type_functions::NOT_FUNCTION;
	}

	Node_identity(const size_t arg_id, const Type_functions arg_type) {
		left_id = arg_id;
		type = arg_type;
		right_id = 0;
		is_binary = false;
		is_used = false;
	}

	Node_identity(const size_t arg_left_id, const Type_functions arg_type, const size_t arg_right_id) {
		left_id = arg_left_id;
		type = arg_type;
		right_id = arg_right_id;
		is_binary = true;
		is_used = false;
	}

	bool operator==(const Node_identity &other) {
		return (left_id == other.left_id && right_id == other.right_id && type == other.type && is_binary == other.is_binary);
	}

	bool operator!=(const Node_identity &other) {
		return !(left_id == other.left_id && right_id == other.right_id && type == other.type && is_binary == other.is_binary);
	}
};

const int SUBGRAPH_COLOUR_OFFSET = 50;

struct Arrow {
    std::string from;
    std::string to;

    std::string type;
    std::string color;

    Arrow(std::string arg_from, std::string arg_to, std::string arg_type, std::string arg_color) {
    	from = arg_from;
    	to = arg_to;
    	type = arg_type;
    	color = arg_color;
    }
};

class Graph_dumper {
public:
	FILE* dumper;
	Node_identity last_node;
	char graph_name[128];
	size_t subgraph_number;
	int subgraph_colour;
	std::vector<Arrow> arrows;

	Graph_dumper();

	void dump(const Int& object, Int_signal int_signal, const Console_colours colour);
	void dump(const Int& left_object, const Int_signal int_signal, const Int& right_object, const Console_colours colour);
	
	void print_node(const Node_identity* node, Console_colours colour);

	void add_order_arrows(Node_identity* last_node, Node_identity* now_node);

	void add_ctor_dtor_arrows(const Int& object, Node_identity* node, Int_signal int_signal);

	void add_operation_arrows(const Int& left_object, const Int_signal int_signal, const Int& right_object, Node_identity& now_node);
	void add_one_operation_arrow(const Int& object, const Int_signal int_signal, Node_identity& now_node);

	void begin_subgraph(Elem_t& name_function);
	void end_subgraph(Elem_t& name_function);
	void dump_arrows();

	~Graph_dumper();
};

class Function_name_sender {
  public:
	Elem_t name_func;

	Function_name_sender(Elem_t arg_name_func);

	~Function_name_sender();

};

#endif