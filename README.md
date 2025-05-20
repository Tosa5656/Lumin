# ✨ Lumin: Your Programming Language of the Future ✨
[![GitHub stars](https://img.shields.io/github/stars/Tosa5656/Lumin?style=social)](https://github.com/Tosa5656/Lumin)
[![GitHub forks](https://img.shields.io/github/forks/Tosa5656/Lumin?style=social)](https://github.com/Tosa5656/Lumin)
[![GitHub issues](https://img.shields.io/github/issues/Tosa5656/Lumin)](https://github.com/Tosa5656/Lumin/issues)
[![License](https://img.shields.io/github/license/Tosa5656/Lumin)](./LICENSE)

[Russian readme](https://github.com/Tosa5656/Lumin/docs/ru/README.md)

**Lumin** is a new, developing programming language created with an emphasis on simplicity, readability, and performance. It is designed to be a versatile tool for a wide range of tasks, from small scripts to large, complex applications. Lumin aims to offer developers an intuitive syntax and powerful features, while ensuring safety and preventing common errors.

## 💡 Core Principles and Philosophy
*   **Purpose:** Universal programming language.
*   **Simplicity:** Easy to learn and use.
*   **Readability:** Code should be easy to read and understand.
*   **Performance:** Performant enough for a wide range of tasks.
*   **Safety:** Preventing errors and ensuring code safety.

## 📦 Installation
*(This section will be updated when it is possible to install Lumin)*

Currently, since Lumin is in active development, direct installation is not possible. Stay tuned for updates!

## 🚀 Getting Started

*(This section will be updated when it is possible to run Lumin code)*

When Lumin becomes available for use, instructions for running your first programs will be here.

## 📚 Language Features
### Data Types
#### Primitive Types
*   `int`: Integer numbers.
*   `float`: Floating-point numbers.
*   `bool`: Boolean values (`true`/`false`).
*   `string`: Strings.
*   `null`: Null value.

#### Data Structures
*   **Arrays:**
    *   Can be of fixed or dynamic size.
    *   Homogeneous (all elements of the same type).
    *   Strong typing.

    ##### Creation:
    ```cpp
    iтt[length] array = new int[length]; // Creating a fixed-length array
    int array = {1, 2, 3};
    int array = [1, 2, 3];
    ```

    ##### Operations:
    ```cpp
    array[index];        // access by index
    array.length();      // array length
    array.reverse();     // reverse
    array.sort();        // sort
    array.add(element);  // add element to the end (for dynamic arrays)
    array.remove(index); // remove element by index (for dynamic arrays)
    array.find(element); // find element
    ```

*   **Lists:**
    ##### Implementation:

    *   Linked list.
    *   Homogeneous (all elements of the same type).
    *   Strong typing.

    ##### Operations:
    ```cpp
    list.add(element);          // add to the end
    list.remove(index);         // remove by index
    list.insert(index, element); // insert by index
    list.get(index);            // get element by index
    list.length();              // list length
    list.find(element);         // find element
    ```

*   **Dictionaries:**
    ##### Implementation:
    *   Hash Table.
    *   Flexible typing: The key type and value type are determined when the first element is added.

    ##### Operations:
    ```cpp
    dictionary[key] = value; // add/modify
    value = dictionary[key]; // get value
    dictionary.remove(key);  // remove pair
    dictionary.containsKey(key); // check if key exists
    dictionary.size();       // number of pairs
    dictionary.keys();       // list of keys
    dictionary.values();     // list of values
    ```

*   **Strings:**
    *   Mutable.
    *   Regular expression support (implementation details are yet to be determined).

    ##### Operations:

    ```cpp
    string1 + string2;                     // concatenation
    string.length();                       // string length
    string[index];                         // access character by index
    string.find(substring);                // find substring
    string.replace(oldSubstring, newSubstring); // replace substring
    string.split(delimiter);               // split string
    string.toUpper(); || string.toLower();    // case conversion
    string.trim();                         // remove whitespace
    string.insert(index, substring);      // insert substring
    string.remove(startIndex, length);     // remove substring
    ```

### Memory Management
*   Automatic memory management based on ownership (for local variables).
*   Explicit object deletion: `delete(object)`. For custom types, you can overload `delete` for custom logic.
*   `setLifeTime(seconds)`: Sets the lifetime of an object in seconds.
*   Cyclic reference detector.

### Operators
*   Arithmetic: `+`, `-`, `*`, `/`, `%`.
*   Comparisons: `==`, `!=`, `>`, `<`, `>=`, `<=`.
*   Logical: `&&`, `||`, `!`.
*   Assignment: `=`, `+=`, `-=`, `*=`, `/=`, `%=`.

### Control Structures
*   `if else`
    ```cpp
    int a = 5;
    int b = 3;

    if (a == b) // Output: a != b
    {
        print("a = b");
    }
    else
    {
        print("a != b");
    }
    ```

*   `for`
    ```cpp
    int array = {1, 2, 3, 4, 5, 6};
    for (int element : array) // Output: 1 2 3 4 5 6
    {
        print(element);
    }
    ```

*   `while`
    ```cpp
    int array = {1, 2, 3, 4, 5, 6};
    int i = 0;

    while (i < array.length()) // Output: 1 2 3 4 5 6
    {
        print(array[i]);
        i++;
    }
    ```

### Functions
*   Function definition:
    ```cpp
    type function_name(arg_type arg, ... )
    {
        return optional type;
    }
    ```

*   `return` is used to return values.

### Exception Handling
*   `try-catch-finally`
*   Ability to create custom exception types (inheriting from the base class `Exception`).
*   Unhandled exceptions are logged and terminate the program.

### Modules and Namespaces
*   Each file is a module.
*   Import modules: `%include "name"`.
*   Namespaces:

    *   Usage:
        ```cpp
        namespace MyNamespace
        {
            function Test();
            // Somethink...
        }

        MyNamespace::Test();
        ```

### Multithreading
*   Support for threads.
*   Synchronization mechanisms: mutexes, semaphores, channels.

## 🤝 Contributing
Contributions to the development of Lumin are welcome! If you want to contribute, please review our [contributing guidelines](https://github.com/Tosa5656/Lumin/CONTRIBUTING.md).

## 📄 License
Lumin is distributed under the [GPL-3.0](LICENSE) license.

## ✉️ Contacts
*   eea85670@gmail.com

## 🎉 Acknowledgements
We express our gratitude to everyone who helps in the development of Lumin!