# SmartCode

Smart Code is a lightweight integrated development environment written in C ++ and based on the Qt Framework for the C ++ language.

# Building

For building the projet you gonna need :

GCC >= 4.4.0

Qt Library >= 4.8.0

QScintilla2

# Project Structure

The project is divised into modules (shared libraries)

 - **Core**       : it's the main module on the project and contains shared functionalities with all other modules.
 - **Make**       : responsable for generating make files.
 - **GUI**        : contains application interfaces including the main interface and others.
 - **Project**    : contains project explorer ,used for reading and writing smart code projects.
 - **Build**      : used for building the project by calling a toolchain (only gcc is supported) on the background and reporting errors and   
                    warnings,contains also a basic gdb debugger integration.
 - **TextEditor** : contains a text editor based on qscintilla2
 - **Astyle**     : used for formatting code
 - **Search**     : used for searching in source code
 - **Compability**: used for opening project from an other IDE, only Dev-C++ projects are supported at the moment, others projects like CodeBlocks projects may need more work.