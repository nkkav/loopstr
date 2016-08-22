/* file "loopstr/suif_main.cpp" */
/*
 *     Copyright (c) 2004, 2005, 2006, 2007, 2008, 2009, 2010,
 *                   2011, 2012, 2013, 2014, 2015, 2016 Nikolaos Kavvadias
 *
 *     This software was written by Nikolaos Kavvadias, Ph.D. candidate
 *     at the Physics Department, Aristotle University of Thessaloniki,
 *     Greece (at the time).
 *
 *     This software is provided under the terms described in
 *     the "machine/copyright.h" include file.
 */

#include <machine/copyright.h>
#include <machine/machine.h>

//#include <loopstr/suif_pass.h>
#include "loopstr/suif_pass.h"

#ifdef USE_DMALLOC
#include <dmalloc.h>
#define new D_NEW
#endif

int main(int argc, char* argv[])
{
    // initialize the environment
    SuifEnv* suif_env = new SuifEnv;
    suif_env->init();

    init_loopstr(suif_env);

    // transform the input arguments into a stream of input tokens
    TokenStream token_stream(argc, argv);

    // execute the Module "loopstr"
    ModuleSubSystem* mSubSystem = suif_env->get_module_subsystem();
    mSubSystem->execute("loopstr", &token_stream);

    delete suif_env;

    return 0;
}
