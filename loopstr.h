/* file "loopstr/loopstr.h" */
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

#ifndef LOOPSTR_LOOPSTR_H
#define LOOPSTR_LOOPSTR_H

#include <machine/copyright.h>

#ifdef USE_PRAGMA_INTERFACE
#pragma interface "loopstr/loopstr.h"
#endif

#include <machine/machine.h>

class LoopStr {
  public:
    LoopStr() { }

    void initialize() { }
    void do_opt_unit(OptUnit*);
    void finalize() { }
};

#endif /* LOOPSTR_LOOPSTR_H */
