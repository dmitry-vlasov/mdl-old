/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_Substitution.hpp                          */
/* Description:     substitution expression class                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_SUBSTITUTION_HPP_
#define MDL_EXPRESSION_SUBSTITUTION_HPP_

#include "mdl/expression/mdl_expression_Symbol.hpp"
#include "mdl/expression/mdl_expression_Substiunit.hpp"

namespace mdl {
namespace expression {

template<class T>
class Substitution :
	public Scalar
	<
		Substitution<T>,
		typename T :: Node_ :: Allocator_
	> {
public :
	typedef
		typename T :: Node_ :: Allocator_
		Allocator_;
	typedef T Term_;

	typedef Substiunit<Term_> Substiunit_;
	typedef
		typename Term_ :: Iterator_
		Iterator_;
	typedef
		typename Term_ :: const_Iterator_
		const_Iterator_;

	template<class A>
	struct Alternative {
		typedef A Allocator_;
		typedef Substitution
		<
			typename Substitution :: Term_ ::
				template Alternative<Allocator_> :: Result_
		>
		Result_;
		typedef typename Result_ :: Term_ Term_;
		typedef typename Term_ :: Iterator_ Iterator_;
		typedef typename Term_ :: const_Iterator_  const_Iterator_;
	};

	template<class A>
	typename Alternative<A> :: Result_*
	castAway(); // respect to Green Day
	template<class A>
	const typename Alternative<A> :: Result_*
	castAway() const; // respect to Green Day

	template<class A>
	static Substitution* create
	(
		const Symbol&,
		const Term_*,
		const Substitution* = NULL,
		const bool = false
	);
	static Substitution* create (const Substitution*);
	template<class T1>
	static Substitution* create (const Substitution<T1>*);

	template<class A>
	const Substitution* clone() const;
	template<class P>
	const Substitution* clone (P*) const;
	template<class A>
	Substitution* cloneSelf() const;
	template<class P>
	void cloneContents (P*) const;

	template<class A>
	const Substitution<Term<typename node :: List<A> > >*
	createList() const;

	Substitution
	(
		const Symbol&,
		const Term_*,
		const Substitution* const = NULL,
		const bool = false
	);
	Substitution (const Substitution* const);
	template<class T1>
	Substitution (const Substitution<T1>* const);
	~ Substitution();

	const_Iterator_ follow (const const_Iterator_) const;
	bool coinsides (const const_Iterator_, const const_Iterator_) const;
	const Substitution* find (const Symbol&) const;
	const Substitution* findTerm (const Symbol&) const;
	const Substitution* find (const value :: Literal) const;

	const Term_* getTerm () const;
	Term_* term();
	const Symbol& getVariable() const;
	const Substitution* getNext() const;
	void setNext (const Substitution*) const;
	Substitution* next() const;

	value :: Integer getLength() const;
	value :: Integer getSymbolVolume() const;
	value :: Integer getComplexity() const;
	value :: Integer getCardinality() const;

	bool isTrivial() const;

	Substitution* compose (const Substitution* const, const bool = true);
	Substitution* unite (const Substitution* const);
	Substitution* join (const Substitution* const);
	bool isComposableWith (const Substitution* const) const;
	template<class I>
	Substitution* restrictTo (const I);
	Substitution* inverse() const;
	bool operator == (const Substitution&) const;
	bool operator != (const Substitution&) const;

	bool isEqual (const Substitution*) const;
	template<int K>
	bool isLessGeneral (const Substitution*) const;
	template<int K>
	bool isMoreGeneral (const Substitution*) const;
	bool domainsAreEqual (const Substitution*) const;
	bool domainsSubset (const Substitution*) const;

	bool isIdentical (const Substitution*) const;
	bool inside (const Substitution*) const;
	bool includes (const Substiunit_&) const;

	static bool unifyCommonVariables (Substitution*&, Substitution*&);
	static bool compositionClosure (const value :: Integer, Substitution*&);

	void verifyIntegrity() const;
	void inverse();

	// object :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	void show (String&) const;
	void dump() const;

private :
	const_Iterator_ follow (const_Iterator_, const_Iterator_) const;
	const_Iterator_ match (const const_Iterator_, const_Iterator_) const;

	const_Iterator_ getBegin() const;
	const_Iterator_ getEnd() const;

	// composition routines
	Substitution* apply (const Substitution* const);
	Substitution* add (const Substitution* const);
	Substitution* addUnit (Substitution* const, const Substiunit_&);
	Substitution* removeTrivial();

	// common variable unification routines
	static bool unifyCommonVariable
	(
		Substitution*&,
		Substitution*&,
		bool& iterate
	);
	static bool unifyCommonPair
	(
		Substitution*&,
		Substitution*&,
		const Term_*,
		const Term_*
	);

	Substiunit_ unit_;
	mutable const Substitution* next_;
	template<class T1>
	friend class Substitution;
};

	template<class T>
	String&
	operator << (String&, const Substitution<T>&);
	template<class T>
	std :: ostream&
	operator << (std :: ostream&, const Substitution<T>&);
}
}

#endif /*MDL_EXPRESSION_SUBSTITUTION_HPP_*/
