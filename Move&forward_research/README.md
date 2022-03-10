
# Small study on std::move & std:forward

## Intro
In the last article, it was found that moves are more efficient than copies. After that, the thought may arise that displacements should be used everywhere. Is it true?

In the examples you will find the following functions: my_move and my_forward. This is the author's implementation of functions std::move and std::forward.

## First comparison: getting to know the moves
Let's look at the following two simple examples. We pass the argument to the function and do nothing with it. The second example assigns not just the passed argument, but the result of the my_move function from this argument.
<!-- | Pass by value | Pass by reference  |
|----------------|:---------:|
| 
```
template<class T>
void example_1(T&& arg) {
	BEGIN_ANY_FUNC
	volatile auto new_tmp = arg;
}

template<class T>
void wrapper(T&& arg) {
	BEGIN_ANY_FUNC
	example_1(arg);
}

void testing() {
	VAR(Int, a, 10);
	wrapper(a);
}
```
| ggg s|
Note: BEGIN_ANY_FUNC is a macro that creates a subgraph in the picture with the name of the function called by the user.

| Pass by value | Pass by reference  |
|----------------|:---------:|
| ![Examples3](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Dumping_int/Examples/picture3.png) | ![Examples4](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Dumping_int/Examples/picture4.png) |

Wow! By passing by reference, we prevented two extra **copies**. Adorably!

## Second comparison: on/off moves + on/off copy-ellision
At the very beginning of the article, it was said about the existence of the compilation flag **-fno-elide-constructors**. Let's try to run with on/off move-optimization and with/without this flag. Let's look at an example of such a simple program, what happens:

```
Int sum(Int& a, Int& b) {
	BEGIN_ANY_FUNC

	return a + b;
}

void testing() {
	VAR(Int, a, 130);
	VAR(Int, b, 20);
	VAR(Int, c, 0);

	c =  sum(a, b);
}
```

| Off moves <br/> Off copy-ellision | Off moves <br/> On copy-ellision  | On moves <br/> Off copy-ellision | On moves <br/> On copy-ellision |
|----------------|:---------:|----------------|-------------|
| ![Examples10](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Dumping_int/Examples/fno-elide-no-moves.png) | ![Examples11](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Dumping_int/Examples/elide-no-moves.png)  | ![Examples12](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Dumping_int/Examples/fno-elide-with-moves.png) | ![Examples13](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Dumping_int/Examples/elide-with-moves.png) |

Green boxes mean that the variable's move constructor/assignment has been called.

## Third comparison: lots about on/off moves
Now consider the most important example for us. Obviously, no one turns on the flag that removes copy optimization. So let's dive into move-optimization. Look at an example:

```
Int get_var(Int var) {
	BEGIN_ANY_FUNC
	
	return var;
}

void testing() {
	VAR(Int, a, 130);
	VAR(Int, b, 20);
	VAR(Int, c, 0);

	c = get_var(a) + get_var(b);
}
```

| Without moves | With moves  |
|----------------|:---------:|
| ![Examples7](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Dumping_int/Examples/picture7.png) | ![Examples6](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Dumping_int/Examples/picture6.png) |


 -->