
# Small study on std::move & std:forward

## Intro
In the last article, it was found that moves are more efficient than copies. After that, the thought may arise that displacements should be used everywhere. Is it true?

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
| ![Examples0](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Move&forward_research/Examples/picture0.png) | ![Examples1](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Move&forward_research/Examples/picture1.png) |

What can be the conclusion? If you look at the implementation of std::move, you can see that all references are truncated first, and then the truncated argument is cast to an rvalue using static_cast. This is really handy because it allows you to call move constructors 

## Second comparison: std::move vs std::forward, lvalues
By the way, what if we want to avoid copying, but also don't want the variables to be reset to zero after they are moved? Let's remember the existence of std::forward, it was not in vain that it was mentioned at the beginning of the article. Let's try to use it: 

```
template<class T>
void example(T&& arg) {
	BEGIN_ANY_FUNC
	volatile auto new_tmp = my_move<T>(arg); // my_forward<T>(arg)
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

| pass lvalue<br/>my_move | pass lvalue<br/>my_forward | pass lvalue<br/>without moves<br/>and forwarding |
|----------------|-------------|-------------|
| ![Examples2](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Move&forward_research/Examples/picture2.png) | ![Examples3](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Move&forward_research/Examples/picture3.png) | ![Examples4](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Move&forward_research/Examples/picture4.png) |

Fun fact: my_forward and argument passing without my_move and my_forward are the same in terms of the number of copies.

## Third comparison: std::move vs std::forward, rvalues
And now let's pass the good old rvalue:

```
template<class T>
void example(T&& arg) {
	BEGIN_ANY_FUNC
	volatile auto new_tmp = arg; // my_forward<T>(arg)
}

template<class T>
void wrapper(T&& arg) {
	BEGIN_ANY_FUNC
	example(arg); // example(my_forward<T>(arg))
}

void testing() {
	wrapper(Int(5));
}
```

| pass rvalue<br/>without my_forward | pass rvalue<br/>with my_forward  |
|----------------|:---------:|
| ![Examples5](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Move&forward_research/Examples/picture5.png) | ![Examples6](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Move&forward_research/Examples/picture6.png) |


To be continued
