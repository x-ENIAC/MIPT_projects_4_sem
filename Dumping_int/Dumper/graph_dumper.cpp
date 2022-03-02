#include "graph_dumper.h"

#define IF_DEBUG(code) //code
// #define HORIZONTAL_GRAPH
#define VERTICAL_GRAPH

Graph_dumper::Graph_dumper() : last_node(0, Type_functions::NOT_FUNCTION) {
	strcpy(graph_name, "new.dot");

	dumper = fopen(graph_name, "w");
	fprintf(dumper, "digraph graphname {\n");

	#ifdef HORIZONTAL_GRAPH
	fprintf(dumper, "\trankdir = LR;\n");
	#endif

	subgraph_number = 0;
	subgraph_colour = 200;
}

void Graph_dumper::dump(const Int& object, Int_signal int_signal, const Console_colours colour = Console_colours::RESET) {
	Type_functions type = Type_functions::NOT_FUNCTION;

	if(int_signal == Int_signal::CONSTRUCT)
		type = Type_functions::CONSTRUCT;
	else
	if(int_signal == Int_signal::COPY)
		type = Type_functions::COPY;
	else
	if(int_signal == Int_signal::COPY_ASSIGNMENT)
		type = Type_functions::COPY_ASSIGNMENT;
	else
	if(int_signal == Int_signal::MOVE)
		type = Type_functions::MOVE;
	else
	if(int_signal == Int_signal::MOVE_ASSIGNMENT)
		type = Type_functions::MOVE_ASSIGNMENT;
	else
	if(int_signal == Int_signal::DESTRUCT)
		type = Type_functions::DESTRUCT;
	else { printf("[Graph_dumper] [dump(..., ...)\n"); return; }

	fprintf(dumper, "\tnode%ld%s [shape=\"record\", style=\"filled\", fillcolor=\"%s\", label=\"{{%s | %s=%d}|{%p | id=%ld}}\"]\n",
											object.get_id(), char_type_functions[(int)type], colours_text[(int)colour],
											char_type_functions[(int)type], object.get_name().c_str(),
											object.get_value(), &object, object.get_id());

	Node_identity now_node(object.get_id(), type);
	now_node.is_binary = false;		

	add_order_arrows(&last_node, &now_node);
	add_ctor_dtor_arrows(object, &now_node, int_signal);

	IF_DEBUG(printf("#### now_node: left_id=%ld, type=%d, right_id=%ld, is_binary=%d\n", now_node.left_id, now_node.type, now_node.right_id, now_node.is_binary);
			 printf("#### last_node: left_id=%ld, type=%d, right_id=%ld, is_binary=%d\n", last_node.left_id, last_node.type, last_node.right_id, last_node.is_binary);)

	last_node.left_id = object.get_id();
	last_node.type = type;
	last_node.is_binary = false;

}

void Graph_dumper::dump(const Int& left_object, const Int_signal int_signal, const Int& right_object,
												const Console_colours colour = Console_colours::RESET) {

	Type_functions type = Type_functions::NOT_FUNCTION;

	if(int_signal >= Int_signal::MORE && int_signal <= Int_signal::ASSIGNMENT)
		type = Type_functions::OPERATION;
	else
	if(int_signal == Int_signal::COPY)
		type = Type_functions::COPY;
	else
	if(int_signal == Int_signal::COPY_ASSIGNMENT)
		type = Type_functions::COPY_ASSIGNMENT;
	else
	if(int_signal == Int_signal::MOVE)
		type = Type_functions::MOVE;
	else
	if(int_signal == Int_signal::MOVE_ASSIGNMENT)
		type = Type_functions::MOVE_ASSIGNMENT;
	else { printf("[Graph_dumper] [dump(..., ..., ...) signal %d]\n", (int)int_signal); return; }

	IF_DEBUG(printf("type %d\n", (int)type);)
	if(type == Type_functions::COPY_ASSIGNMENT || type == Type_functions::MOVE_ASSIGNMENT) {
		// IF_DEBUG(printf("\t2 draw type! != CM\n");)
		fprintf(dumper, "\tnode%ld%s%ld [shape=\"record\", style=\"filled\", fillcolor=\"%s\", label=\"{{%s | %s = %s}|{%p | id=%ld | value=%d}|{%p | id=%ld | value=%d}}\"]\n",
					left_object.get_id(), char_type_functions[(int)type], right_object.get_id(), colours_text[(int)colour],
					char_type_functions[(int)type], left_object.get_name().c_str(), right_object.get_name().c_str(), /*signals[(int)int_signal],*/
					&left_object, left_object.get_id(), left_object.get_value(),
					&right_object, right_object.get_id(), right_object.get_value());
	}

	else
	if(type != Type_functions::COPY && type != Type_functions::COPY_ASSIGNMENT &&
		type != Type_functions::MOVE && type != Type_functions::MOVE_ASSIGNMENT) {
		IF_DEBUG(printf("\t2 draw type! != CM\n");)
		fprintf(dumper, "\tnode%ld%s%ld [shape=\"record\", style=\"filled\", fillcolor=\"%s\", label=\"{{%s | %s%s%s}|{%p | id=%ld | value=%d}|{%p | id=%ld | value=%d}}\"]\n",
					left_object.get_id(), char_type_functions[(int)type], right_object.get_id(), colours_text[(int)colour],
					char_type_functions[(int)type], left_object.get_name().c_str(), signals[(int)int_signal],
					right_object.get_name().c_str(),
					&left_object, left_object.get_id(), left_object.get_value(),
					&right_object, right_object.get_id(), right_object.get_value());
		IF_DEBUG(printf("\tnode%ld%s%ld [shape=\"record\", style=\"filled\", fillcolor=\"%s\", label=\"{{%s | %s%s%s}|{%p | id=%ld | value=%d}|{%p | id=%ld | value=%d}}\"]\n",
					left_object.get_id(), char_type_functions[(int)type], right_object.get_id(), colours_text[(int)colour],
					char_type_functions[(int)type], left_object.get_name().c_str(), signals[(int)int_signal],
					right_object.get_name().c_str(),
					&left_object, left_object.get_id(), left_object.get_value(),
					&right_object, right_object.get_id(), right_object.get_value());)
	}

	else {
		IF_DEBUG(printf("\t2 draw type! = C || = m\n");)
		fprintf(dumper, "\tnode%ld%s  [shape=\"record\", style=\"filled\", fillcolor=\"%s\" label=\"{{%s | %s}|{%p | id=%ld | value=%d}|{%p | id=%ld | value=%d}}\"]\n",
					left_object.get_id(), char_type_functions[(int)type], colours_text[(int)colour],
					char_type_functions[(int)type], left_object.get_name().c_str(),
					&left_object, left_object.get_id(), left_object.get_value(),
					&right_object, right_object.get_id(), right_object.get_value());
		IF_DEBUG(printf("\tnode%ld%s  [shape=\"record\", style=\"filled\", fillcolor=\"%s\" label=\"{{%s | %s}|{%p | id=%ld | value=%d}|{%p | id=%ld | value=%d}}\"]\n",
					left_object.get_id(), char_type_functions[(int)type], colours_text[(int)colour],
					char_type_functions[(int)type], left_object.get_name().c_str(),
					&left_object, left_object.get_id(), left_object.get_value(),
					&right_object, right_object.get_id(), right_object.get_value());)
	}

	Node_identity now_node(left_object.get_id(), type, right_object.get_id());
	now_node.is_binary = true;

	add_order_arrows(&last_node, &now_node);
	add_operation_arrows(left_object, int_signal, right_object, now_node);

	IF_DEBUG(printf("#### now_node: left_id=%ld, type=%d, right_id=%ld, is_binary=%d\n", now_node.left_id, now_node.type, now_node.right_id, now_node.is_binary);
			 printf("#### last_node: left_id=%ld, type=%d, right_id=%ld, is_binary=%d\n", last_node.left_id, last_node.type, last_node.right_id, last_node.is_binary);)

	last_node.left_id = left_object.get_id();
	last_node.type = type;
	last_node.right_id = right_object.get_id();
	last_node.is_binary = true;

}

void Graph_dumper::print_node(const Node_identity* node, Console_colours colour = Console_colours::RESET) {
	if(node->is_binary && node->type != Type_functions::COPY && node->type != Type_functions::MOVE) {
		fprintf(dumper, "node%ld%s%ld", node->left_id, char_type_functions[(int)node->type], node->right_id);
		IF_DEBUG(printf("node%ld%s%ld", node->left_id, char_type_functions[(int)node->type], node->right_id);)
	}
	else {
		fprintf(dumper, "node%ld%s", node->left_id, char_type_functions[(int)node->type]);
		IF_DEBUG(printf("node%ld%s", node->left_id, char_type_functions[(int)node->type]);)
	}

	if(colour != Console_colours::RESET)
		fprintf(dumper, "[]");
}

void Graph_dumper::add_order_arrows(Node_identity* last_node, Node_identity* now_node) {
	if(last_node->is_used) {
		fprintf(dumper, "\t");
		IF_DEBUG(printf("\t");)
		print_node(last_node);

		fprintf(dumper, " -> ");
		IF_DEBUG(printf(" -> ");)
		print_node(now_node);

		fprintf(dumper, "\n");
		IF_DEBUG(printf("\n");)
	} else {
		last_node->is_used = true;
	}
}

void Graph_dumper::add_ctor_dtor_arrows(const Int& object, Node_identity* node, Int_signal int_signal) {
	if(int_signal != Int_signal::DESTRUCT)
		return;

	Node_identity ctor_node(object.get_id(), Type_functions::CONSTRUCT);

	if(object.get_is_copy_anyone())
		ctor_node.type = Type_functions::COPY;

	if(object.get_is_move_anyone())
		ctor_node.type = Type_functions::MOVE;

	fprintf(dumper, "\t");
	IF_DEBUG(printf("\t");)
	print_node(&ctor_node);
	fprintf(dumper, " -> ");
	IF_DEBUG(printf("->");)
	print_node(node);

	fprintf(dumper, "[style=\"dashed\"]\n");
	IF_DEBUG(printf("[style=\"dashed\"]\n");)

	// arrows.push_back({&ctor_node, &now_node, "", "red"});
}

void Graph_dumper::add_operation_arrows(const Int& left_object, const Int_signal int_signal, const Int& right_object, Node_identity& now_node) {
	// left -> now
	add_one_operation_arrow(left_object, int_signal, now_node);

	// right -> now
	add_one_operation_arrow(right_object, int_signal, now_node);
}

void Graph_dumper::add_one_operation_arrow(const Int& object, const Int_signal int_signal, Node_identity& now_node) {
	if(object.last_operation != now_node) {
		fprintf(dumper, "\t");
		IF_DEBUG(printf("\t");)
		print_node(&object.last_operation);
		fprintf(dumper, " -> ");
		IF_DEBUG(printf("->");)
		print_node(&now_node);

		fprintf(dumper, "[color=\"red\"]\n");
		IF_DEBUG(printf("[color=\"red\"]\n");)
		
		// arrows.push_back({get_node_name(object.last_operation), get_node_name(now_node), "", "red"});
	}
}

// std::string Graph_dumper::get_node_name(const Node_identity& node) {
// 	std::string name = "node";
// 	name += node.left_id.to_string();
// 	name += char_type_functions[(int)node->type].to_string();

// 	if(node.is_binary && node.type != Type_functions::COPY && node.type != Type_functions::MOVE)
// 		name += node.right_id.to_string();

// 	return name;

// }

void Graph_dumper::begin_subgraph(Elem_t& name_function) {
	fprintf(dumper, "\nsubgraph \"cluster_%ld\" {\n\tstyle=filled;\n\tcolor=\"#%02x%02x%02x\";\n\t", subgraph_number++,
																			subgraph_colour, subgraph_colour, subgraph_colour);
	subgraph_colour -= SUBGRAPH_COLOUR_OFFSET;
}

void Graph_dumper::end_subgraph(Elem_t& name_function) {
	fprintf(dumper, "\tlabel = \"%s\" \n}\n\n", name_function.c_str());
	subgraph_colour += SUBGRAPH_COLOUR_OFFSET;
}

void Graph_dumper::dump_arrows() {
	// int count_arrows = arrows.size();

	// for(int i = 0; i < count_arrows; ++i) {
	// 	fprintf(dumper, "%s -> %s", arrows[i].)
	// }
}

Graph_dumper::~Graph_dumper() {
	// dump_arrows();
	fprintf(dumper, "}\n");
	fclose(dumper);
}

#include "int_dumping.h"

Function_name_sender::Function_name_sender(Elem_t arg_name_func) {
	name_func = arg_name_func;
	Dumper::get_dumper()->get_graph_dumper()->begin_subgraph(name_func);
}

Function_name_sender::~Function_name_sender() {
	Dumper::get_dumper()->get_graph_dumper()->end_subgraph(name_func);
}