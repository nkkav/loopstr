/* file "loopstr/suif_pass.h" */
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

#ifndef LOOPSTR_SUIF_PASS_H
#define LOOPSTR_SUIF_PASS_H

#include <machine/copyright.h>

#ifdef USE_PRAGMA_INTERFACE
#pragma interface "loopstr/suif_pass.h"
#endif

#include <machine/pass.h>
#include <machine/machine.h>

//#include <loopstr/loopstr.h>
#include "loopstr/loopstr.h"

class LoopStrSuifPass : public PipelinablePass {
  protected:
    LoopStr loopstr;		// the OPI-pass object

    // command-line arguments
    OptionString *proc_names;
    OptionString *file_names;	// names of input and/or output files
    IdString o_fname;		// optional output file name

    set<IdString> out_procs;
  public:
    LoopStrSuifPass(SuifEnv* suif_env, const IdString &name = "loopstr");
    ~LoopStrSuifPass(void);

    // We only need a single copy of this pass, since we should never
    // need more than one print_cfg pass in any compiler.
    Module* clone() const { return (Module*)this; }

    void initialize();
    bool parse_command_line(TokenStream* command_line_stream);
    void execute();

    void do_file_set_block(FileSetBlock*);
    void do_file_block(FileBlock*);
    void do_procedure_definition(ProcedureDefinition*);

    void finalize();
};

extern "C" void init_loopstr(SuifEnv *suif_env);

#endif /* IL2CFG_SUIF_PASS_H */
