# BMinor Compiler Construction
Semester project implementing different parts of a compiler to work with the BMinor language.

This repository contains the Bminor compiler project followed the examples and textbook by [Douglas Thain](https://github.com/dthain/compilerbook-examples)
The following project completed the scanner, parser, pretty printer, and type checker for the compiler as defined in the course outline. The compiler
still needs bugs to be cleaned for the type checker, but aside from that, all other aspects are fully functional.

# Learning Objectives 
Implementing the scanner in the compiler project taught us about lexical analysis and the importance of designing an efficient tokenizer that recognizes tokens based on regular expressions. We learned to handle complex token patterns, such as regular expressions for identifiers, numbers, and strings, and handle comments and whitespace properly.

The parser implementation exposed us to formal grammars and parsing techniques like Recursive Descent or LALR(1). We had to construct a robust syntax tree that accurately represented the language's grammar, enabling further semantic analysis and code generation stages. Dealing with ambiguous grammar rules required careful consideration to ensure correct parsing behavior.

The pretty printer module provided us with insights into representing the syntax tree in a readable and formatted manner, making debugging and understanding the compiler's intermediate stages much more manageable. It involved traversing the syntax tree effectively and generating well-structured code that maintains the original program's indentation and layout.

The type checker phase was critical in ensuring the language's type safety. We learned about type inference algorithms and the complexities of handling polymorphic types and type compatibility. Additionally, we understood the importance of detecting type errors early in the compilation process, allowing developers to fix issues before executing the program.

Throughout these implementations, we faced error handling, memory management, and shift reduction challenges. Handling ambiguous grammar and improving parser efficiency required us to fine-tune the grammar and consider lookahead strategies. Moreover, managing the symbol table and scope resolution for the type checker demanded attention to detail to ensure accurate type validation.

By completing these modules, we comprehensively understood the different phases involved in a compiler construction project, from lexical analysis and parsing to semantic analysis and type checking. It also deepened our knowledge of programming language theory and the complexities of building a reliable and efficient compiler for a specific language.

# Collabroators
[Zach Le](https://github.com/ezachle)
[Meet Kothari](https://github.com/MeetKothari)
[Krestina Beshara](https://github.com/KrestinaBeshara01842423)
[Alexan Chaprazian](https://github.com/ahchaprazian)
