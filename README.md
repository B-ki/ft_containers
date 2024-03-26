# ft_containers

---

## 42-Subject

### Objectives : 

Recreate some of the Standard Template Library containers : vector, stack, map and set. [https://en.cppreference.com/w/cpp/container]

### Requirements : 

* We have to use std::allocator (thus I don't leave the possibility to use another allocator), 
* C++ 98 only, compiling with -Wextra -Werror and -Wall flags.
* We have to code also some others templates :
   - std::iterator_traits
   - std::enable_if (this is C++11, we are forced to stick to C++98 but this aims to teach us the magic of SFINAE)
   - std::reverse_iterator
   - std::is_integral
   - std::equal / std::lexicographical_compare
   - std::pair
   - std::make_pair
* More details in the subject

---

## How to use it ?

Run ./test.sh in order to compile 2 executable, one using ft (forty-two) namespace, and the other using std namespace. The output of several tests will be redirected in 2 .txt files, and the diff between them will be the final output.

There should be only time difference, otherwise it means that ft_containers don't work like std containers.

You can also use :
`make` to create an executable `ft_containers` that will output the tests results using the namespace ft.

Or you can use `make -DNS=std` to create an executable `ft_containers` that will output the tests results using the namespace std.

---

## Structure of this project

### includes/

* All .hpp required for the project :
   * enable_if
   * equal
   * is_integral
   * iterator_traits
   * map : with a Red Black Tree. Also, some functions not in STL : printRBT and checkRBT that helped verify the RBT inside of map.
   * pair
   * RBT
   * RBT_iterator : iterator and const_iterator used for RBT
   * RBT_node : node structure used for RBT
   * remove_cv
   * reverse_iterator
   * set : with a Red Black Tree
   * stack
   * tests : header for test files
   * vector
* AVL, binary_search and binary_heap : Some trees, simplier than a RBT, that helped me to learn how it works.

### srcs/

All tests files. Same pattern, getting time between block of tests. Vector/stack regrouped in one file. Map split in sevral files.

### Makefile and test.sh

While using `make` it compiles with `-DNS=ft -DUSING_FT=1`, those variables help me to define the namespace as ft (and not std), and print the namespace name correctly. 

If you want to compile with std use `make re NS=std USING_FT=0`

The tester compile one executable with ft, write the output in a txt file. Then does it again with std. diff the two files and delete the 2 output.txt files.

If it works, diff output should be only time differences, otherwise the difference between output should appear.
   
---

## Main topics learned in container

### SFINAE

**Substitution Failure Is Not An Error** : Check at compile time if a condition is true or false. 

Mainly use it to make sure we will be using Iterator in a function, and not real int, when there exists 2 overload possible of a constructor :

- Overload 1 - Real integers :
`	explicit vector(size_type n, const T& value = T()) : vector_base<T, Alloc>(n) 
	{
		std::uninitialized_fill_n(_first, n, value);
		_last = _first + n;
	}`
- Overload 2 - Iterators : 
`	template <class It>
   vector(It first, It last, 
		typename ft::enable_if<!ft::is_integral<It>::value, It>::type* = 0) : vector_base<T, Alloc>(std::distance(first, last))
	{
		std::uninitialized_copy(first, last, _first);
		_last = _first + std::distance(first, last);
	}`

Thanks to the `enable_if` in the 2nd overload, the compiler will know if it has to pick overload 1 or 2 to construct the vector instance.

*How does it work ?*
If `It` is a real integral (char, bool, uchar, signed  char, short, ushort, int, uint, long, ulong) then `ft::is_integral<It>::value = true`. 

And `enable_if` is a template structure :
`template<bool B, class T = void>
 struct enable_if {};`

This structure posess an object type (of type T) only if B is true.

Thus if `It` is a real integer, `type` is defined and `ft::enable_if<!ft::is_integral<It>::value, It>::type* = 0` sends an error, and compiler knows it's not the right overload of the function.

### Exceptions management

Mainly in vector, construction of objects can sometimes generate many errors. For example, a class throwing an execption every 3 objects created is a good tester.

Thus, after discovering that those exceptions really need to be managed, I started to use `std::copy`,`std::uninitialized_copy` and `std::fill` as much as I could. The algorithm to insert elements is then a little tricky, but gave a good problem to solve, you can check it in the `insert` function of `vector`.

### iterators

`begin()` points to the first element of the container, `end()` points one unit after the last element, Incrementing `end()` results in undefined behaviour. Decrementing `end()` shouldn't result in any error.

For vector, the `vector<T>::iterator` is simply a pointer to a value. Thus `operator++` and `operator--` are really simple. 

`reverse_iterator` is a class that can use any error in a mirror way (increment should decrement, `rbegin()` should be the last element, `rend()` should point one unit before the first element, etc.)

`RBT_iterator` is a class specific to the RBT, that uses `node->sucessor()` as increment operator and `node->predecessor()` as decrement operator.

const_iterator and iterator should always be comparable. Thus it is necessary to have a constructor in const_iterator classes that uses as parameter an iterator (iterator to const_iterator is doable, the opposite is not).

### Red and Black Tree (RBT)

Here is an example of how my Red and Black Tree is working :

![alt text](https://github.com/B-ki/ft_containers/blob/master/RBT%20example.png "RBT example")

The RBT is composed mainly of 2 `node_ptr` : `_root` and `_m_null`.

**_root :**
_root→parent = _m_null

**_m_null :**
_m_null→parent = NULL
_m_null→left = _root
_m_null→right = _root

Thus, `end()` is equivalent to `_m_null`. Decrementing it calls to `node->predecssor()` which is equivalent to calling `node->maximum()` on `_root`.

When constructed, `_m_null` is created and `_root = _m_null`

---

## Improvements

* Coding standards, I'm on my way to developp my own CPP standard, so you may find awfull things due to my lack of experience in CPP.
* Vector capacity management : I'm not doubling the capacity like STL vector does, though I don't have a too big difference in execution time
* More containers : deque, list, etc.
* Allowing special allocators.
