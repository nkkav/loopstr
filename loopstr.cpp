/* file "loopstr/loopstr.cpp" */
/*
 *     Copyright (c) 2004, 2005, 2006, 2007, 2008, 2009, 2010,
 *                   2011, 2012, 2013, 2014 Nikolaos Kavvadias
 *
 *     This software was written by Nikolaos Kavvadias, Ph.D. candidate
 *     at the Physics Department, Aristotle University of Thessaloniki,
 *     Greece (at the time).
 *
 *     Current affiliation:
 *     Dr. Nikolaos Kavvadias
 *     Independent Consultant -- Research Scientist
 *     Kornarou 12 Rd., Nea Ampliani,
 *     35100 Lamia, Greece
 *
 *     This software is provided under the terms described in
 *     the "machine/copyright.h" include file.
 */

//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include <ctype.h>
//#include <string.h>

#include <machine/copyright.h>

#ifdef USE_PRAGMA_INTERFACE
#pragma implementation "loopstr/loopstr.h"
#endif

#include <machine/machine.h>
#include <cfa/cfa.h>
#include <cfa/dom.h>
#include <cfa/loop.h>

//#include <loopstr/loopstr.h>
#include "loopstr/loopstr.h"

#ifdef USE_DMALLOC
#include <dmalloc.h>
#define new D_NEW
#endif


void LoopStr::do_opt_unit(OptUnit *unit)
{
    OptUnit *cur_unit;

    // Make local copy of the optimization unit
    cur_unit = unit;

    // Get the name of the optimization unit
    IdString name = get_name(get_proc_sym(cur_unit));

    // Report name of the CFG under processing
    printf("Processing CFG \"%s\"\n", name.chars());
    const char *cur_proc_name = get_name(cur_unit).chars();

    // Get the body of the OptUnit
    AnyBody *cur_body = get_body(cur_unit);

    // verify that it is a CFG
    claim(is_kind_of<Cfg>(cur_body), "expected OptUnit's body in CFG form");
    //remove_unreachable_nodes(unit_cfg);

    // Create a local copy of the input CFG
    Cfg *cfg = (Cfg *)cur_body;

    DominanceInfo temp_dom(cfg);

    // Generate dominance info
    temp_dom.find_dominators();
    temp_dom.print(stdout);

    //NaturalLoopInfo temp_lnat(temp_dom) : dom_info(temp_dom), _depth(NULL), _loop(NULL);
    NaturalLoopInfo temp_lnat(&temp_dom);

    // Generate natural loop info
    temp_lnat.find_natural_loops();
    //
    temp_lnat.print(stdout);


}   /*** END OF loopstr.cpp */

