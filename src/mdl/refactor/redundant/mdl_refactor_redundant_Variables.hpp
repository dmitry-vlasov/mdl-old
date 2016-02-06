/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_refactor_redundant_Variables.hpp                     */
/* Description:     remove redundant variables                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace refactor {
namespace redundant {

class Variables :
	public object :: Object,
	public Scalar<Variables> {
public :
	Variables (Format&);
	virtual ~ Variables();

	index :: Arity removeUnusedVariables (mdl :: Theorem*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :

	typedef
		mdl :: form :: block :: Theorem
		Theorem_;
	typedef
		mdl :: form :: header :: Variables
		Variables_;
	typedef
		mdl :: form :: block :: Proof
		BlockProof_;
	typedef
		mdl :: form :: proof :: Proof
		Proof_;

	typedef
		vector :: Vector
		<
			set :: Symbol,
			storage :: ByPointer,
			allocator :: Heap
		>
		SymbolSetVector_;

	enum {
		INITIAL_VARIABLE_SET_CAPACITY      = 32,
		INITIAL_VARIABLE_SET_VECTOR_CAPACITY = 8
	};

	void collectUsedVariables (const mdl :: Theorem*);
	void collectUsedVariables (const mdl :: Proof*, set :: Symbol*);
	void collectUsedVariables (const array :: Expression*, set :: Symbol*);

	bool setContainsVariableLiteral (const set :: Symbol* set, Symbol variable);

	Format format_;
	Format subFormat_;

	set :: Symbol    assertionVariableSet_;
	SymbolSetVector_ proofVariableSetVector_;
};

}
}
}


