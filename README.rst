=====================
 loopstr user manual
=====================

+-------------------+----------------------------------------------------------+
| **Title**         | loopstr (Natural loop analysis pass for Machine-SUIF)    |
+-------------------+----------------------------------------------------------+
| **Author**        | Nikolaos Kavvadias 2004, 2005, 2006, 2007, 2008, 2009    |
|                   | 2010, 2011, 2012, 2013, 2014                             |
+-------------------+----------------------------------------------------------+
| **Contact**       | nikos@nkavvadias.com                                     |
+-------------------+----------------------------------------------------------+
| **Website**       | http://www.nkavvadias.com                                |
+-------------------+----------------------------------------------------------+
| **Release Date**  | 25 September 2014                                        |
+-------------------+----------------------------------------------------------+
| **Version**       | 1.1.1                                                    |
+-------------------+----------------------------------------------------------+
| **Rev. history**  |                                                          |
+-------------------+----------------------------------------------------------+
|        **v1.1.1** | 2014-09-25                                               |
|                   |                                                          |
|                   | Updated headers in all source code files. Added File     |
|                   | Listing section in README; new files AUTHORS, LICENSE    |
|                   | and VERSION; renamed README to README.rst.               |
+-------------------+----------------------------------------------------------+
|        **v1.1.0** | 2014-02-24                                               |
|                   |                                                          |
|                   | Changed documentation format to RestructuredText.        |
+-------------------+----------------------------------------------------------+
|        **v1.0.0** | 2004-07-19                                               |
|                   |                                                          |
|                   | Initial release.                                         |
+-------------------+----------------------------------------------------------+


1. Introduction
===============

``loopstr`` is an analysis pass built to be used with the SUIF2/MachSUIF2 
compiler infrastructure. This pass generates a textual representation for the 
loop structure of each given C procedure.

This pass uses the cfa library of MachSUIF. What it actually generates is the 
natural loop analysis report for the procedure. The format of such file is 
shown below:

::

  Loop info:
    node depth begin end exit
     int: int   Y/N  Y/N  Y/N
     ...................................

where:

node: 
  the number of the corresponding basic block (integer)
depth: 
  the loop nesting depth (integer)
begin: 
  a boolean flag to report if a loop begins at the specified node
end: 
  a boolean flag to report if a loop ends at the specified node
exit: 
  a boolean flag to report if an exit from the loop is possible from that node.

This pass works for the SUIFvm instruction set as well as other MachSUIF 
backends. The ``loopstr`` pass has been tested with MachSUIF 2.02.07.15.


2. File listing
===============

The ``loopstr`` distribution includes the following files:
   
+-----------------------+------------------------------------------------------+
| /loopstr              | Top-level directory                                  |
+-----------------------+------------------------------------------------------+
| AUTHORS               | List of ``loopstr`` authors.                         |
+-----------------------+------------------------------------------------------+
| LICENSE               | The modified BSD license governs ``loopstr``.        |
+-----------------------+------------------------------------------------------+
| README.rst            | This file.                                           |
+-----------------------+------------------------------------------------------+
| README.html           | HTML version of README.                              |
+-----------------------+------------------------------------------------------+
| README.pdf            | PDF version of README.                               |
+-----------------------+------------------------------------------------------+
| VERSION               | Current version of the project sources.              |
+-----------------------+------------------------------------------------------+
| loopstr.cpp           | Implementation of the ``loopstr`` pass.              |
+-----------------------+------------------------------------------------------+
| loopstr.h             | C++ header file containing declarations and          |
|                       | prototypes for the above.                            |
+-----------------------+------------------------------------------------------+
| rst2docs.sh           | Bash script for generating the HTML and PDF versions |
|                       | of the documentation (README).                       |
+-----------------------+------------------------------------------------------+
| suif_main.cpp         | Entry point for building the standalone program      |
|                       | ``do_loopstr`` that implements the pass.             |
+-----------------------+------------------------------------------------------+
| suif_pass.cpp         | Define the SUIF pass built as the dynamically        |
|                       | loadable library ``libloopstr.so``.                  |
+-----------------------+------------------------------------------------------+
| suif_main.h           | C++ header file for the above.                       |
+-----------------------+------------------------------------------------------+


3. Installation
===============

Unpack the ``loopstr`` archive wherever you like, e.g. in ``$MACHSUIFHOME/cfa/loopstr``.
You don't need to modify anything in the Makefile, if you have a working
MachSUIF 2 installation.

The program binary (``do_loopstr``) will be installed at ``$NCIHOME/bin`` and 
the shared library (``libloopstr.so``) at ``$NCIHOME/solib``, where NCIHOME is 
the SUIF 2 top-level directory.


4. Usage details
================

The pass accepts an input file in CFG form to operate. Textual output is 
generated, written to stdout by default.

Usage synopsys:
| ``$ do_loopstr test.cfg``
