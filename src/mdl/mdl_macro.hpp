/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_macro.hpp                                            */
/* Description:     macro definitions, used in mdl                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

	/****************************
	 *		General macros
	 ****************************/

//#define DEBUG
//#define VERIFY_SORT
//#define DEBUG_EQUATION_MONOTONIC
//#define DEBUG_REFACTORING

	/****************************
	 *	Proving control macros
	 ****************************/

//#define DEBUG_PROVER_ALL

//#define DEBUG_PROVER_UP
//#define DEBUG_PROVER_DOWN
//#define DEBUG_PROVER_PROOF
//#define DEBUG_PROVER_ROOT

//#define DEBUG_POINTERS
//#define DEBUG_WEIGHT
#define VERIFY_PROOF_STEPS
//#define DEBUG_USE_PROD_MATRIX_UNIFICATION
//#define DEBUG_PROVER_MATRIX_UNIFICATION
//#define DEBUG_UNIFICATION true

//#define ALLOW_MULTIPLE_PREMISE

#ifdef DEBUG_PROVER_ALL
	#define DEBUG_PROVER_UP
	#define DEBUG_PROVER_DOWN
	#define DEBUG_PROVER_ROOT
	#define DEBUG_PROVER_MATRIX_UNIFICATION
#endif


	/****************************
	 *		Memory macros
	 ****************************/

//#define DEBUG_ALL_MEMORY_LEAKS
//#define DEBUG_HEAP_MEMORY_LEAKS
//#define DEBUG_BOXED_MEMORY_LEAKS
//#define DEBUG_STANDARD_MEMORY_LEAKS
//#define DEBUG_DISPOSED
//#define DEBUG_HEAP_MAP
//#define DEBUG_HEAP_CONTROL_ALLOCATION

#define USE_STANDARD_HEAP

	/****************************
	 *		Concurrency macros
	 ****************************/

#define MULTY_THREADED true
//#define TREE_GROW_UP_MULTY_THREADED   true
//#define TREE_GROW_DOWN_MULTY_THREADED true
