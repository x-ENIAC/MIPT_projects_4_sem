#include "../Int/my_int.h"
#ifndef GRAPH_DUMPER_H
#define GRAPH_DUMPER_H

struct Node_identity;

#include <string.h>

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
};

class Graph_dumper {
public:
	FILE* dumper;
	Node_identity last_node;
	char graph_name[128];

	Graph_dumper();

	void dump(const Int& object, Int_signal int_signal);
	void dump(const Int& left_object, const Int_signal int_signal, const Int& right_object);
	
	void print_node(const Node_identity* node);

	void add_order_arrows(Node_identity* last_node, Node_identity* now_node);

	void add_ctor_dtor_arrows(const Int& object, Node_identity* node, Int_signal int_signal);

	void add_operation_arrows(const Int& left_object, const Int_signal int_signal, const Int& right_object, Node_identity& now_node);

	~Graph_dumper();
};

#endif