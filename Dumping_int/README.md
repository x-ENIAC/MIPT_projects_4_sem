
# Small study on copying variables 

## Intro
This project provides code for the Int class that implements an integer, as well as a set of tools for tracking the behavior of various operations on objects. All actions with this object (summation, subtraction, multiplication, division, assignment, and many others) are recorded, then written to the terminal, to an html file, and also presented as a graph. Investigation is done with the compilation flag turned on **-fno-elide-constructors** (not including the third paragraph).

Why is this needed? Everyone around says that extra copying is bad, everyone argues that passing arguments should be done only by reference. But why? What happens if you do it differently? This mini-project is a small illustration and an answer to these questions. 

Let's look at this simple example: 
```
	VAR(Int, a, 10);
	VAR(Int, b, 20);
```
![Examples1](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Dumping_int/Examples/picture1.png)

Here two variables a=10 and b=20 are created using the VAR macro. In the picture you see four rectangles. Yellow boxes mean that the variable's constructor has been called, while pink boxes indicate that the variable's destructor has been called. The black solid lines show the order in which the commands are executed. Dashed lines connect the constructor and destructor of the same variable. The red lines show which variables are involved in this operation. 

This picture is simple. Two variables are built, two are destroyed. Let's take a more complicated example:
```
	VAR(Int, a, 10);
	VAR(Int, b, 20);
	VAR(Int, c, 100);

	c = a + b;
```
![Examples2](https://github.com/x-ENIAC/MIPT_projects_4_sem/blob/master/Dumping_int/Examples/picture2.png)

Operators are marked in blue. Three constructors are called first; then the operation takes place and the result is assigned to the **temporary variable**, which in turn is assigned to c. The summation operator calls the constructor and creates a temporary object.

## First comparison: pass by value VS pass by reference
Okay, now let's look at situations using different ways of passing an object to a function as an argument:

```
Int mult(Int var1, Int var2) {
	BEGIN_ANY_FUNC
	
	return var1 * var2;
}

void testing() {
	VAR(Int, a, 10);
	VAR(Int, b, 20);
	VAR(Int, c, 100);

	c = mult(a, b);
}
```
Note: BEGIN_ANY_FUNC is a macro that creates a subgraph in the picture with the name of the function called by the user.

The first way is to pass the function object by value, the second way is to pass by reference.

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


