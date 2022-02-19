#ifndef GRAPH_DUMPER_H
#define GRAPH_DUMPER_H

#include "../Int/my_int.h"

struct Node_identity {
	size_t left_id;
	Type_functions type;
	size_t right_id;
	bool is_binary;
	bool is_used;

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

	Graph_dumper() : last_node(0, Type_functions::NOT_FUNCTION) {
		strcpy(graph_name, "new.dot");

		dumper = fopen(graph_name, "w");
		fprintf(dumper, "digraph graphname {\n");
	}

	void dump(const Int& object, Int_signal int_signal) {
		Type_functions type = Type_functions::NOT_FUNCTION;

		if(int_signal == Int_signal::CONSTRUCT)
			type = Type_functions::CONSTRUCT;
		else
		if(int_signal == Int_signal::COPY)
			type = Type_functions::COPY;
		else
		if(int_signal == Int_signal::DESTRUCT)
			type = Type_functions::DESTRUCT;
		else { printf("[Graph_dumper] [dump(..., ...)\n"); return; }

		fprintf(dumper, "\tnode%ld%s [shape=\"record\", color=\"red\", label=\"{{%s | %s=%d}|{%p | id=%ld}}\"]\n",
												object.get_id(), char_type_functions[(int)type], char_type_functions[(int)type],
												object.get_name().c_str(), object.get_value(), &object, object.get_id());

		// arrows show order
		// if(!(last_node.type == Type_functions::NOT_FUNCTION && last_node.id == 0)) {
		// 	fprintf(dumper, "\tnode%ld%s -> node%ld%s\n",
		// 					last_node.id, char_type_functions[(int)last_node.type],
		// 					object.get_id(), char_type_functions[(int)type]);
		// }
		if(last_node.is_used) {
			fprintf(dumper, "\t");
			print_node(&last_node);

			fprintf(dumper, " -> ");

			Node_identity now_node(object.get_id(), type);
			now_node.is_binary = false;
			print_node(&now_node);

			fprintf(dumper, "\n");
		} else {
			last_node.is_used = true;
		}

		last_node.left_id = object.get_id();
		last_node.type = type;
		last_node.is_binary = false;		
	}

	void dump(const Int& left_object, const Int_signal int_signal, const Int& right_object) {
		Type_functions type = Type_functions::NOT_FUNCTION;

		// if(int_signal == Int_signal::OPERATION)
		if(int_signal == Int_signal::ADD || int_signal == Int_signal::SUB || int_signal == Int_signal::MUL || int_signal == Int_signal::DIV)
			type = Type_functions::OPERATION;
		else { printf("[Graph_dumper] [dump(..., ..., ...)]\n"); return; }

		fprintf(dumper, "\tnode%ld%s%ld [shape=\"record\", color=\"red\", label=\"{{%s | %s%s%s}|{%p | id=%ld | value=%d}|{%p | id=%ld | value=%d}}\"]\n",
						left_object.get_id(), char_type_functions[(int)type], right_object.get_id(),
						char_type_functions[(int)type], left_object.get_name().c_str(), signals[(int)int_signal],
						right_object.get_name().c_str(),
						&left_object, left_object.get_id(), left_object.get_value(),
						&right_object, right_object.get_id(), right_object.get_value());

		// arrows show order
		// if(!(last_node.type == Type_functions::NOT_FUNCTION && last_node.id == 0)) {
		// 	fprintf(dumper, "\tnode%ld%s -> node%ld%s\n",
		// 					last_node.id, char_type_functions[(int)last_node.type],
		// 					object.get_id(), char_type_functions[(int)type]);
		// }

		// last_node.id = object.get_id();
		// last_node.type = type;

		if(last_node.is_used) {
			fprintf(dumper, "\t");
			print_node(&last_node);

			fprintf(dumper, " -> ");
			Node_identity now_node(left_object.get_id(), type, right_object.get_id());
			now_node.is_binary = true;
			print_node(&now_node);			
			
			fprintf(dumper, "\n");
		} else {
			last_node.is_used = true;
		}

		last_node.left_id = left_object.get_id();
		last_node.type = type;
		last_node.right_id = right_object.get_id();
		last_node.is_binary = true;
	}

	void print_node(Node_identity* node) {
		if(node->is_binary)
			fprintf(dumper, "node%ld%s%ld", node->left_id, char_type_functions[(int)node->type], node->right_id);
		else
			fprintf(dumper, "node%ld%s", node->left_id, char_type_functions[(int)node->type]);
	}

	~Graph_dumper() {
		fprintf(dumper, "}\n");
		fclose(dumper);
	}
};

#endif