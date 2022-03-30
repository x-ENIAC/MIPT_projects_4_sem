
# Small study on std::move & std:forward

## Intro
In the [last article](https://github.com/x-ENIAC/MIPT_projects_4_sem/tree/master/Dumping_int), it was found that moves are more efficient than copies. After that, the thought may arise that displacements should be used everywhere. Is it true?

In the examples you will find the following functions: my_move and my_forward. This is the author's implementation of functions std::move and std::forward.

## First comparison: getting to know the moves
Let's look at the following two simple examples. We pass the argument to the function and do nothing with it. The second example assigns not just the passed argument, but the result of the my_move function from this argument.

```
template<class T>
void example(T&& arg) {
	BEGIN_ANY_FUNC
	volatile auto new_tmp = arg; // my_move(arg)
}

template<class T>
void wrapper(T&& arg) {
	BEGIN_ANY_FUNC
	example(arg);
}

void testing() {
	VAR(Int, a, 10);
	wrapper(a);
}
```
Note: BEGIN_ANY_FUNC is a macro that creates a subgraph in the picture with the name of the function called by the user.

| Without my_move | With my_move  |
|----------------|:---------:|
| ![Code0](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Move&forward_research/Examples/code0.png) | ![Code1](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Move&forward_research/Examples/code1.png) |
| ![Examples0](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Move&forward_research/Examples/picture0.png) | ![Examples1](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Move&forward_research/Examples/picture1.png) |

What can be the conclusion? If you look at the implementation of std::move, you can see that all references are truncated first, and then the truncated argument is cast to an rvalue using static_cast. This is really handy because it allows you to call move constructors 

## Second comparison: std::move vs std::forward
Let's take a look at this example:
```
template<class T>
void push_into_container(T arg) {
	BEGIN_ANY_FUNC
	volatile auto new_tmp = arg;
}

template<class T>
void wrapper(T&& arg) {
	push_into_container(my_move(arg)); // my_forward<T>(arg);
}

void testing() {
	VAR(Int, a, 10);

	printf("a = %d\n", a.get_value()); // move: 10, forward: 10
	wrapper(a);
	printf("a = %d\n", a.get_value()); // move: 0, forward: 10
}
```

| my_move | my_forward |
|----------------|-------------|
| ![Code2](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Move&forward_research/Examples/code2.jpg) | ![Code3](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Move&forward_research/Examples/code3.jpg) |
| ![Examples2](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Move&forward_research/Examples/picture2.png) | ![Examples3](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Move&forward_research/Examples/picture3.png) |

Look at the pictures. When using a move, the variable is reset to zero, but it moves. And with a forward, it’s the other way around: copying occurs, but the value is saved.


Let's try to pass rvalue:
```
template<class T>
void example_1(T arg) {
	BEGIN_ANY_FUNC
	volatile auto new_tmp = arg;
}

template<class T>
void wrapper(T arg) {
	printf("a = %d\n", arg.get_value());
	example_1(arg); // my_forward<T>(arg);
	printf("a = %d\n", arg.get_value());
}

void testing() {
	wrapper(Int(10, "a"));
} 
```


| pass rvalue<br/>without my_forward | pass rvalue<br/>with my_forward  |
|----------------|:---------:|
| ![Code7](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Move&forward_research/Examples/code7.jpg) | ![Code5](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Move&forward_research/Examples/code5.jpg) |
| ![Examples7](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Move&forward_research/Examples/picture7.png) | ![Examples5](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Move&forward_research/Examples/picture5.png) |


## Conclusion
The std::forward is supposed to be used for ideal parameter passing + it always requires the type to be specified. This allows rvalue arguments to be passed on as rvalues, and lvalues to be passed on as lvalues. This scheme is known as perfect forwarding. The std::move is used for displacing. It is quite important to differentiate these two purposes and to use correctly.
