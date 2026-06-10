# 2D Graphics Editor in C

## Overview

This project is a console-based 2D Graphics Editor developed in C. It simulates a simple drawing environment using a two-dimensional character array as the canvas. The application allows users to create, edit, remove, and manage graphical objects directly from a menu-driven interface.

The canvas is initialized with underscore (`_`) characters, while graphical objects are rendered using asterisk (`*`) characters.

## Functionalities

### Shape Creation

The editor supports the following geometric primitives:

* Line
* Rectangle
* Triangle
* Circle

Each shape can be added to the drawing area through interactive user input.

### Object Management

To enable editing operations, every graphical object is assigned a unique identifier.

Supported operations include:

* Adding new objects
* Deleting existing objects
* Modifying object parameters
* Listing active objects

### Canvas Rendering

The entire canvas can be displayed at any time. A redraw mechanism reconstructs the scene from stored object information, ensuring consistency after modifications and deletions.

## Algorithms Used

### Bresenham's Line Algorithm

Used for efficient rasterization of straight lines between two points.

### Midpoint Circle Algorithm

Used for plotting circular boundaries using integer arithmetic for improved performance.

## Data Structures

The project utilizes:

* Enumerations for shape classification
* Structures for storing object properties
* Arrays for object management
* A 2D character matrix as the drawing canvas

## Program Workflow

1. Initialize the canvas.
2. Display the main menu.
3. Perform shape operations.
4. Update object storage.
5. Re-render the canvas.
6. Display the updated drawing.

## Technologies

* Programming Language: C
* Compiler: GCC / MinGW
* Platform: Console-based application

## Learning Outcomes

This project demonstrates:

* Structured programming
* Graphics representation using arrays
* Geometric drawing algorithms
* Dynamic object management
* Menu-driven application design
* Modular programming practices


