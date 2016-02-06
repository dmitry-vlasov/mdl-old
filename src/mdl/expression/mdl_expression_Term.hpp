/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_Term.hpp                                  */
/* Description:     expression term (subexpression)                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.dpp"

namespace mdl {
namespace expression {

template<class N>
class Term : public Scalar<Term<N>, typename N :: Allocator_ > {
public :
	typedef N Node_;
	typedef
		typename Node_ :: const_Iterator_
		const_Iterator_;
	typedef
		typename Node_ :: Term_
		Term_;
	typedef
		typename Node_ :: Allocator_
		Allocator_;
	typedef
		typename Node_ :: Iterator_
		Iterator_;
	typedef
		Substitution<Term>
		Substitution_;

	template<class A>
	struct Alternative {
		typedef A Allocator_;
		typedef Term
		<
			typename Node_ ::
				template Alternative<Allocator_> :: Result_
		>
		Result_;
		typedef typename Result_ :: Iterator_ Iterator_;
		typedef typename Result_ :: const_Iterator_  const_Iterator_;
	};

	template<class A>
	typename Alternative<A> :: Result_*
	castAway(); // respect to Green Day
	template<class A>
	const typename Alternative<A> :: Result_*
	castAway() const; // respect to Green Day

	template<class A>
	static Term* create (const Term&);
	template<class A>
	static Term* create
	(
		const Iterator_,
		const mdl :: Type* const = NULL
	);
	template<class A>
	static Term* create
	(
		const Iterator_,
		const Iterator_,
		const mdl :: Type* const = NULL
	);
	template<class P>
	const Term* clone (P*) const;
	template<class>
	const Term* cloneSelf () const;
	template<class P>
	void cloneContents (P*) const;

	template<class A>
	const Term<typename node :: List<A> >*
	createList() const;
	template<class N1>
	const Term<N1>*
	createOther() const;

	Term
	(
		const Iterator_,
		const mdl :: Type* = NULL
	);
	Term
	(
		const Iterator_,
		const Iterator_,
		const mdl :: Type* = NULL
	);
	Term (const Term&);
	Term (const Term*);
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

	bool isNull() const;
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
	template<class I>
	bool isEqualLiteraly (const I, const I) const;
	bool contains (const Symbol&) const;

	void operator = (const Term&);
	bool operator == (const Symbol&) const;
	bool operator != (const Symbol&) const;
	template<class T>
	bool operator == (const T&) const;
	template<class T>
	bool operator != (const T&) const;
	template<class T>
	bool coinsides (const T&) const;
	template<class T>
	bool isEqual (const T&) const;
	template<class T>
	bool isEqualLiteraly (const T&) const;

	const Term_* getTerm() const;
	const Term_* getParent() const;
	const mdl :: Type* getType() const;
	void setParent (const Term_*) const;
	void setType (const mdl :: Type*) const;

	template<class S>
	const Term_* execute (const S*);

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
	void writeMultylineForward (String& string, const Indent indent = Indent(), int depth = 0) const;
	void writeMultylineBackward (String& string, const Indent indent = Indent(), int depth = 0) const;

	// object :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	void show (String&) const;
	void dump() const;

private :
	template<class>
	friend class List;
	template<class>
	friend class parse :: Term;

	template<class T1, class T0>
	bool coinsides_p (const T1&, const T0*) const;

	typedef
		typename Node_ :: Terms_
		_Terms_;
	typedef
		typename _Terms_ :: Initial_
		_Initial_;
	typedef
		typename _Terms_ :: Terminal_
		_Terminal_;

	template<class T>
	const Term_* insertTerm (const Iterator_&, const T*);
	const Term_* insert (const Term_*, const Term_*);
	void fixInsertionEnd (const Term_*, const Term_*);
	void fixInsertionBegin (const Term_*, const Term_*);

	enum {
		VERIFICATION_CRITICAL_LENGTH = 1024 * 16
	};

	void verifyNodes (const bool) const;
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

	value :: Integer computeHeight() const;

	mutable Iterator_ begin_;
	mutable Iterator_ end_;
	mutable const Term_* parent_;
	mutable const mdl :: Type* type_;
};

	template<class N>
	String&
	operator << (String&, const Term<N>&);
	template<class N>
	std :: ostream&
	operator << (std :: ostream&, const Term<N>&);
}
}


