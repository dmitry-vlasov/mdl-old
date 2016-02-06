/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_math_Assertions.hpp                                  */
/* Description:     global container for assertions                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/math/mdl_math_Container.hpp"

namespace mdl {
namespace math {

class Assertions :
	public Container<mdl :: Assertion, index :: Assertion>,
	public Scalar<Assertions> {
public :
	Assertions ();
	virtual ~ Assertions();
	
	index :: Assertion getSize() const;
	index :: Assertion add (mdl :: Assertion*);
	mdl :: Assertion* get (const index :: Assertion);
	mdl :: Assertion* get (const char* name);

	mdl :: Assertion* getAxiom (const index :: Assertion);
	mdl :: Assertion* getDefinition (const index :: Assertion);
	mdl :: Assertion* getTheorem (const index :: Assertion);
	mdl :: Assertion* getProblem (const index :: Assertion);

	index :: Assertion getAxiomNumber() const;
	index :: Assertion getDefinitionNumber() const;
	index :: Assertion getTheoremNumber() const;
	index :: Assertion getProblemNumber() const;
	index :: Assertion getAxiomaticNumber() const;
	index :: Assertion getProvableNumber() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;
	
private :
	typedef
		Container<mdl :: Assertion, index :: Assertion>
		Container_;

	enum {
		INITIAL_ASSERTION_VECTOR_CAPACITY  = size :: KILOBYTE * 64,
		INITIAL_AXIOM_VECTOR_CAPACITY      = size :: KILOBYTE,
		INITIAL_DEFINITION_VECTOR_CAPACITY = size :: KILOBYTE * 4,
		INITIAL_THEOREM_VECTOR_CAPACITY    = size :: KILOBYTE * 64,
		INITIAL_PROBLEM_VECTOR_CAPACITY    = size :: KILOBYTE
	};

	vector :: Assertion axiomVector_;
	vector :: Assertion definitionVector_;
	vector :: Assertion theoremVector_;
	vector :: Assertion problemVector_;

	pthread_mutex_t mutex_;
};

}
}


