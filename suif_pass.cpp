/* file "loopstr/suif_pass.cpp" */
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

#include <machine/copyright.h>

#ifdef USE_PRAGMA_INTERFACE
#pragma implementation "loopstr/suif_pass.h"
#endif

#include <machine/pass.h>
#include <machine/machine.h>
#include <cfa/cfa.h>

//#include <loopstr/suif_pass.h>
#include "loopstr/suif_pass.h"

#ifdef USE_DMALLOC
#include <dmalloc.h>
#define new D_NEW
#endif

extern "C" void
init_loopstr(SuifEnv *suif_env)
{
    static bool init_done = false;

    if (init_done)
	return;
    init_done = true;

    ModuleSubSystem *mSubSystem = suif_env->get_module_subsystem();
    mSubSystem->register_module(new LoopStrSuifPass(suif_env));

    // initialize the libraries required by this OPI pass
    init_suifpasses(suif_env);
    init_machine(suif_env);
    init_cfa(suif_env);
}

LoopStrSuifPass::LoopStrSuifPass(SuifEnv *suif_env, const IdString& name)
    : PipelinablePass(suif_env, name)
{
    the_suif_env = suif_env;	// bind suif_env into our global environment
}

LoopStrSuifPass::~LoopStrSuifPass()
{
    // empty
}

void
LoopStrSuifPass::initialize()
{
    PipelinablePass::initialize();

    OptionLiteral *f;

    // Create grammar for parsing the command line.  This must occur
    // after the parent class's initialize routine has been executed.
    _command_line->set_description("process instruction list in Cfg form");

    // Collect optional flags.
    OptionSelection *flags = new OptionSelection(false);

    // -debug_proc procedure
    OptionList *l = new OptionList;
    l->add(new OptionLiteral("-proc"));
    proc_names = new OptionString("procedure name");
    proc_names->set_description("indicate procedures that need to be printed ");
    l->add(proc_names);
    _flags->add(l);

    // Accept tagged options in any order.
    _command_line->add(new OptionLoop(flags));

    // zero or more file names
    file_names = new OptionString("file name");
    OptionLoop *files =
	new OptionLoop(file_names,
		       "names of optional input and/or output files");
    _command_line->add(files);
}

bool
LoopStrSuifPass::parse_command_line(TokenStream *command_line_stream)
{
    // Set flag defaults
    o_fname = empty_id_string;

    if (!PipelinablePass::parse_command_line(command_line_stream))
	return false;

    int n = proc_names->get_number_of_values();

    for (int i = 0; i < n; i++) {
	String s = proc_names->get_string(i)->get_string();
	out_procs.insert(s);
	cout << s.c_str() << endl;
    }

    o_fname = process_file_names(file_names);

    return true;
}

void
LoopStrSuifPass::execute()
{
    PipelinablePass::execute();

    // Process the output file name, if any.
    if (!o_fname.is_empty())
        the_suif_env->write(o_fname.chars());
}

void
LoopStrSuifPass::do_file_set_block(FileSetBlock *fsb)
{
    claim(o_fname.is_empty() || fsb->get_file_block_count() == 1,
	  "Command-line output file => file set must be a singleton");

    set_opi_predefined_types(fsb);
}

void
LoopStrSuifPass::do_file_block(FileBlock *fb)
{
    claim(has_note(fb, k_target_lib),
	  "expected target_lib annotation on file block");

    focus(fb);

    loopstr.initialize();
}

void
LoopStrSuifPass::do_procedure_definition(ProcedureDefinition *pd)
{
    IdString pname = get_name(get_proc_sym(pd));
    if (!out_procs.empty() && out_procs.find(pname) == out_procs.end()) {
	return;
    }

    focus(pd);
    loopstr.do_opt_unit(pd);
    defocus(pd);
}

void
LoopStrSuifPass::finalize()
{
    loopstr.finalize();
}

