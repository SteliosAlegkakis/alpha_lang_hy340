<h1>Alpha Programming Language</h1> 

<h2>Overview</h2>
<p>Alpha is a dynamically typed programming language developed for the purposes of the course "Languages and Compilers" of the computer science dpt in Univerity of Crete. It compiles to byte code with the alpha compiler and runs with the alpha virtual machine. </p>

<h2>Install and Build</h2>
<p>GNU <a href="https://www.gnu.org/software/bison/">Bison</a> and <a href="https://gothub.frontendfriendly.xyz/westes/flex/blob/master/README.md/">Flex</a> are required to build the alpha compiler so make sure to download these first.</p>

```
git clone "https://github.com/SteliosAlegkakis/alpha_lang_hy340.git"
cd alpha_lang_hy340
make all
```
<p>After following these steps you should see two executable files inside the projects root folder, one named alphac and one named alphavm. </p>

<h2>How to Run</h3>

To compile an alpha source file 
```
./alphac alpha_source.asc
```
To execute an alpha binary file
```
 ./alphavm alpha_binary.abc
 ```

<h3>Compiler flags</h3>

 * ``-g`` generates two files, the file quads.txt and instructions.txt containing the intermediate code and the final instructions respectively for debugging purposes.
 ```
 usage
 ./alphac -g alpha_source.asc
 ```
  * ``-o`` by default the compiler gives to the executable binary file the name a.abc. However, you can change that using the -o flag.
 ```
 usage
 ./alphac alpha_source.asc -o executable_name
 ```

<h2>Data types in alpha</h2>

* ``number`` Both integers and doubles are converted to doubles with two decimals for simplicity. Numbers support all the arithmetic and relative operations. In boolean operations, all numbers convert to true except 0 that converts to false.
* ``string`` Character strings can consist of any asci symbols including escpae characters. In boolean operations, all non-empty strings convert to true.
* ``bool`` Can get the value true or false.
* ``table`` Can consist of of random values of any type, or key-value pairs where the key has to be of type number or string. In boolean operations, all tables are converted to true.
* ``nil`` In boolean operations, nil is converted to false.
* ``undef`` All the symbols that don't have a type at runtime are assigned as undef. In boolean operations, undef is converted to false.
* ``userfunc`` Any functions written by the user. In boolean operations, userfunc is converted to false.
* ``libfunc`` All the library functions are of type libfunc. In boolean operations, libfunc is converted to false.


<h2>Library functions</h3>

 * ``print(...)`` Takes any number of arguments and prints them to the console.
 * ``input()`` Returns input from the console. Automatically converts to the responding data type (number, bool, nil, string).
 * ``argument(i)`` Returns the i'th argument of the function where it is called. Returns nil when used outside of a function. Throws error if an invalid i is given( less than 0 or bigger than totalarguments() - 1).
 * ``totalarguments()`` Returns the total number of actual arguments of the function that called it. Returns nil if called outside of a function.
 * ``objectmemberkeys(t)`` Returns a new table that contains all the keys of the given table t. Throws error if t is not of type table.
 * ``objecttotalmembers(t)`` Returns the total number of mebers in the table t. Throws error if t is not of type table.
* ``objectcopy(t)`` Returns a shallow copy of the table t. Throws error if t is not of type table.
* ``typeof(x)`` Returns the type of x as a string value.
* ``strtonum(str)`` Converts str to a number if possible and returns it else returns nil. Throws error if str is not of type string.
* ``sin(x)`` Returns the sin of x. Throws error if x is not a number.
* ``cos(x)`` Returns the cos of x. Throws error if x is not a number.
* ``sqrt(x)`` Returns the square root of x for non negative values and nil for negatives. Throws error if x is not of type number.

 



