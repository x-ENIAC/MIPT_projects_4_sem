#include "graph_dumper.h"

Graph_dumper::Graph_dumper() : last_node(0, Type_functions::NOT_FUNCTION) {
	strcpy(graph_name, "new.dot");

	dumper = fopen(graph_name, "w");
	fprintf(dumper, "digraph graphname {\n");
}

void Graph_dumper::dump(const Int& object, Int_signal int_signal) {
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

	Node_identity now_node(object.get_id(), type);
	now_node.is_binary = false;		

	add_order_arrows(&last_node, &now_node);
	add_ctor_dtor_arrows(object, &now_node, int_signal);

	last_node.left_id = object.get_id();
	last_node.type = type;
	last_node.is_binary = false;
}

void Graph_dumper::dump(const Int& left_object, const Int_signal int_signal, const Int& right_object) {
	Type_functions type = Type_functions::NOT_FUNCTION;

	if(int_signal >= Int_signal::MORE && int_signal <= Int_signal::ASSIGNMENT)
		type = Type_functions::OPERATION;
	else { printf("[Graph_dumper] [dump(..., ..., ...) signal %d]\n", (int)int_signal); return; }

	fprintf(dumper, "\tnode%ld%s%ld [shape=\"record\", color=\"red\", label=\"{{%s | %s%s%s}|{%p | id=%ld | value=%d}|{%p | id=%ld | value=%d}}\"]\n",
					left_object.get_id(), char_type_functions[(int)type], right_object.get_id(),
					char_type_functions[(int)type], left_object.get_name().c_str(), signals[(int)int_signal],
					right_object.get_name().c_str(),
					&left_object, left_object.get_id(), left_object.get_value(),
					&right_object, right_object.get_id(), right_object.get_value());

	Node_identity now_node(left_object.get_id(), type, right_object.get_id());
	now_node.is_binary = true;

	add_order_arrows(&last_node, &now_node);
	add_operation_arrows(left_object, int_signal, right_object, now_node);

	last_node.left_id = left_object.get_id();
	last_node.type = type;
	last_node.right_id = right_object.get_id();
	last_node.is_binary = true;
}

void Graph_dumper::print_node(const Node_identity* node) {
	if(node->is_binary)
		fprintf(dumper, "node%ld%s%ld", node->left_id, char_type_functions[(int)node->type], node->right_id);
	else
		fprintf(dumper, "node%ld%s", node->left_id, char_type_functions[(int)node->type]);
}

void Graph_dumper::add_order_arrows(Node_identity* last_node, Node_identity* now_node) {
	if(last_node->is_used) {
		fprintf(dumper, "\t");
		print_node(last_node);

		fprintf(dumper, " -> ");
		print_node(now_node);

		fprintf(dumper, "\n");
	} else {
		last_node->is_used = true;
	}
}

void Graph_dumper::add_ctor_dtor_arrows(const Int& object, Node_identity* node, Int_signal int_signal) {
	if(int_signal != Int_signal::DESTRUCT)
		return;

	Node_identity ctor_node(object.get_id(), Type_functions::CONSTRUCT);

	fprintf(dumper, "\t");
	print_node(&ctor_node);
	fprintf(dumper, " -> ");
	print_node(node);

	fprintf(dumper, "[style=\"dashed\"]\n");
}

void Graph_dumper::add_operation_arrows(const Int& left_object, const Int_signal int_signal, const Int& right_object, Node_identity& now_node) {
	fprintf(dumper, "\t");
	print_node(&left_object.last_operation);

	fprintf(dumper, " -> ");
	print_node(&now_node);

	fprintf(dumper, "[color=\"red\"]\n");

	fprintf(dumper, "\t");
	print_node(&right_object.last_operation);

	fprintf(dumper, " -> ");
	print_node(&now_node);

	fprintf(dumper, "[color=\"red\"]\n");
} // need last object operation!!

Graph_dumper::~Graph_dumper() {
	fprintf(dumper, "}\n");
	fclose(dumper);
}