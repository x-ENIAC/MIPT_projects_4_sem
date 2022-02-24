
This project provides code for the Int class that implements an integer, as well as a set of tools for tracking the behavior of various operations on objects. All actions with this object (summation, subtraction, multiplication, division, assignment, and many others) are recorded, then written to the terminal, to an html file, and also presented as a graph

Let's look at this simple example: 
```
	VAR(Int, a, 10);
	VAR(Int, b, 20);
```
![Examples1](https://github.com/owl1234/MIPT_projects_4_sem/blob/master/Dumping_int/Examples/picture1.png)

Here two variables a=10 and b=20 are created using the VAR macro. In the picture you see four rectangles. Green boxes mean that the variable's constructor has been called, while pink boxes indicate that the variable's destructor has been called. The black solid lines show the order in which the commands are executed. Dashed lines connect the constructor and destructor of the same variable. The red lines show which variables are involved in this operation. 

This picture is simple. Two variables are built, two are destroyed. Let's take a more complicated example:
```
	VAR(Int, a, 10);
	VAR(Int, b, 20);
	VAR(Int, c, 100);

	c = a + b;
```
![Examples2](https://github.com/owl1234/MIPT_projects_4_sem/blob/master/Dumping_int/Examples/picture2.png)

Operators are marked in blue. Three constructors are called first; then the operation takes place and the result is assigned to the **temporary variable**, which in turn is assigned to c. The summation operator calls the constructor and creates a temporary object.

Okay, now let's look at situations using different ways of passing an object to a function as an argument:

```
Int mult(Int var1, Int var2) {
	return var1 * var2;
}

void testing() {
	VAR(Int, a, 10);
	VAR(Int, b, 20);
	VAR(Int, c, 100);

	c = mult(a, b);
}
```

The first way is to pass the function object by value, the second way is to pass by reference.

![Examples3](https://github.com/owl1234/MIPT_projects_4_sem/blob/master/Dumping_int/Examples/picture3.png)

![Examples4](https://github.com/owl1234/MIPT_projects_4_sem/blob/master/Dumping_int/Examples/picture4.png)

Wow! By passing by reference, we prevented two extra copies. Adorably!

Well, this is the last example. Beware, very large chart. 

```
Int get_var(Int var) {
	return var;
}

Int mult(Int& var) {
	return var * var * 5 + get_var(var) * 3 + 1;
}

void testing() {
	VAR(Int, a, 130);
	VAR(Int, b, 20);

	b = mult(a);
}
```

![Examples4](https://github.com/owl1234/MIPT_projects_4_sem/blob/master/Dumping_int/Examples/picture5.png)

