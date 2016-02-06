/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_evaluation_Term.hpp                        */
/* Description:     abstract interface for evaluation of fitness             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/object/mdl_interface_object.hpp"

namespace mdl {
namespace interface {
namespace evaluation {

class Term : public object :: Buildable {
public :
	typedef
		prover :: Node<allocator :: Heap>
		HeapNode_;
	typedef
		prover :: Node<allocator :: Boxed>
		BoxedNode_;
	typedef
		form :: header :: statement :: Proposition
		Proposition_;

	Term();
	virtual ~ Term();

	value :: Integer getVersion() const;

	virtual index :: Arity getArity() const { return 0; }
	virtual value :: Real eval (const HeapNode_*) const = 0;
	virtual value :: Real eval (const BoxedNode_*) const;
	virtual value :: Real eval (const value :: Real [] = NULL) const;

	void setProposition (const Proposition_* proposition);
	void setDepth (const value :: Integer depth = 0);

	virtual Term* getSubTerm (const index :: Arity) { return NULL; }
	virtual const Term* getSubTerm (const index :: Arity) const { return NULL; }

	// object :: Writable interface
	virtual void translate (String&) const { };

	// object :: Object interface
	virtual void show (String& string) const { replicate (string); }

protected :
	const Proposition_* proposition_;
	value :: Integer depth_;
	value :: Integer version_;
};

}
}
}



