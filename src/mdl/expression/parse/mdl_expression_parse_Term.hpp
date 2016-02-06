/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_parse_Term.hpp                            */
/* Description:     expression term for parser (subexpression)               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.dpp"
#include "mdl/expression/iterator/mdl_expression_iterator.hpp"
#include "mdl/expression/mdl_expression_Term.hpp"
#include "mdl/expression/mdl_expression_Substitution.hpp"

namespace mdl {
namespace expression {
namespace parse {

template<class N>
class Term : public Scalar<Term<N>, typename N :: Allocator_ > {
public :
	typedef
		typename expression :: Term<N>
		Term_;
	typedef N Node_;
	typedef
		typename Node_ :: Allocator_
		Allocator_;
	typedef
		Substitution<Term>
		Substitution_;
	typedef
		typename Node_ :: const_Iterator_
		const_Iterator_;
	typedef
		typename Node_ :: Iterator_
		Iterator_;

	template<class A>
	struct Alternative {
		typedef A Allocator_;
		typedef Term
		<
			typename Node_ ::
				template Alternative<Allocator_> :: Result_
		>
		Result_;
	};

	template<class A>
	typename Alternative<A> :: Result_*
	castAway(); // respect to Green Day
	template<class A>
	const typename Alternative<A> :: Result_*
	castAway() const; // respect to Green Day

	template<class>
	static Term* create (const Term&);
	template<class>
	static Term* create
	(
		const Iterator_,
		const mdl :: Type* const = NULL,
		const Substitution_* const = NULL
	);
	template<class>
	static Term* create
	(
		const Iterator_,
		const Iterator_,
		const mdl :: Type* const = NULL,
		const mdl :: Rule* const = NULL,
		const Substitution_* const = NULL
	);
	template<class P>
	const Term* clone (P*) const;
	template<class>
	const Term* cloneSelf () const;
	template<class P>
	void cloneContents (P*) const;

	template<class A>
	const typename expression :: Term<typename node :: List<A> >*
	createList() const;

	Term();
	Term
	(
		const Iterator_,
		const mdl :: Type* const = NULL,
		const Substitution_* const = NULL
	);
	Term
	(
		const Iterator_,
		const Iterator_,
		const mdl :: Type* const = NULL,
		const mdl :: Rule* const = NULL,
		const Substitution_* const = NULL
	);
	Term (const Term&);
	~ Term();

	void addSelf (const bool) const;
	void deleteNodes() const;

	Iterator_ getBegin();
	Iterator_ getEnd();
	const_Iterator_ getBegin() const;
	const_Iterator_ getEnd() const;

	value :: Integer getLength() const;
	value :: Integer getDepth() const;
	value :: Integer getHeight() const;
	value :: Integer getSymbolVolume() const;
	value :: Integer getComplexity() const;

	bool isEmpty() const;
	bool isUndefined() const;
	bool isLambda() const;
	bool isDefined() const;
	bool isVariable() const;
	bool isConstant() const;
	bool isReplaceable() const;
	bool isSimple() const;
	bool isComplex() const;
	bool isSymbol (const Symbol&) const;
	template<class I>
	bool isEqual (const I, const I, const mdl :: Type*) const;
	bool contains (const Symbol&) const;

	void operator = (const Term&);
	template<class T>
	bool operator == (const T&) const;
	template<class T>
	bool operator != (const T&) const;
	template<class T>
	bool coinsides (const T&) const;

	const mdl :: Rule* getRule() const;
	const Term_* getParent() const;
	const mdl :: Type* getType() const;
	const Term_* getTerm() const;
	void setParent (const Term*) const;
	void setType (const mdl :: Type*) const;

	void translate (String&, const mdl :: Type*) const;

	template<class I>
	void copyNode (Iterator_&, const I&);
	template<class I>
	bool findNode (Iterator_&, const I&);
	template<class I>
	void addFindNode (Iterator_&, const I&);

	void verifyIntegrity (const bool = false) const;

	Size_t getExpressionVolume() const;
	void showBody (String&) const;
	void showKind (String&) const;
	void showType (String&) const;
	void showTerms (String&) const;
	void writeMultylineForward (String& string, const Indent, int depth) const;
	void writeMultylineBackward (String& string, const Indent, int depth) const;

	// object :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	void show (String&) const;
	void dump() const;

private :
	template<class>
	friend class expression :: Term;

	void showRule (String&) const;
	void showSubstitution (String&) const;

	void translateVariable (String&, const mdl :: Type*) const;
	void translateRule (String&, const mdl :: Type*) const;

	template<class T>
	void verifyTerms (const T&, const bool) const;
	template<class T>
	void verifyPlain (const T*, const bool = false) const;
	void verifyType() const;
	template<class T>
	void verifyInitial (const T*, const bool) const;
	template<class T>
	void verifyTerminal (const T*) const;
	template<class T>
	void verifyUniquity (const T&) const;
	void verifyIteratibility (const bool) const;


	Term_ term_;
	const mdl :: Rule* const rule_;
	mutable const Substitution_* substitution_;
};

	template<class N>
	String&
	operator << (String&, const Term<N>&);
	template<class N>
	std :: ostream&
	operator << (std :: ostream&, const Term<N>&);
}
}
}


