\# Inverted Search



\## Overview

A C-based inverted search engine that indexes words from 

multiple text files using a hash table and linked lists.



\## Objective

The objective of this project is to build an inverted search 

database in C that indexes all words from multiple text files 

using a hash table (26 buckets, one per alphabet). Each word 

maps to a linked list of files and occurrence counts, enabling 

fast word search, display, save and update operations.



\## Features

\- Create database from multiple text files

\- Search any word across all indexed files

\- Display entire database

\- Save database to backup file

\- Update database with new files

\- Case-insensitive word indexing



\## Files

| File | Description |

|------|-------------|

| `inverted.h` | Structs and function declarations |

| `create.c` | Database creation with hash table |

| `search.c` | Word search by hash index |

| `display.c` | Display entire database |

| `update.c` | Update database from new files |

| `save.c` | Save database to backup file |

| `main.c` | Main menu with all operations |



\## Compilation

```bash

gcc main.c create.c search.c display.c update.c save.c -o inverted

```



\## Usage

```bash

./inverted f1.txt f2.txt

```



\## Tech Stack

\- Language: C

\- Concepts: Hash table, Linked lists, File I/O, String operations

