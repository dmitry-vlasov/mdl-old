/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_sub_tree_Unit.hpp                   */
/* Description:     array of iterators for the unification algorithm         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_SUB_TREE_UNIT_HPP_
#define MDL_EXPRESSION_UNIFY_SUB_TREE_UNIT_HPP_

#include "mdl/expression/iterator/mdl_expression_iterator.hpp"

namespace mdl {
namespace expression {
namespace unify {
namespace sub {
namespace tree {

template<class C, class A>
class Unit : public
	iterator :: modifier :: Array<typename C :: Term_ :: const_Iterator_, A> {
public :
	typedef	C Cell_;
	typedef A Allocator_;
	typedef
		typename Cell_ :: Term_
		Term_;
	typedef
		typename mdl :: vector :: Vector
		<
			Cell_*,
			storage :: ByValue,
			allocator :: Stack
		>
		Vector_;
	typedef
		typename mdl :: vector :: Vector
		<
			Vector_*,
			storage :: ByValue,
			allocator :: Stack
		>
		Matrix_;
	typedef
		typename Term_ :: const_Iterator_
		Iterator_;
	typedef
		typename iterator :: modifier :: Array<Iterator_, Allocator_>
		Array_;
	typedef
		List<allocator :: Stack>
		Expression_;
	typedef
		typename Expression_ :: Term_ :: Substitution_
		Substitution_;
	typedef
		typename Term_ :: Node_ :: Data_ :: Container_
		Container_;
	typedef
		typename nstd :: type :: template Unpointer<typename Container_ :: Value_> :: Result_
		Evidence_;

	Unit (const index :: Arity, const Matrix_&);
	Unit (const Unit&);

	void operator + ();
	void operator ++ ();
	value :: Integer getComplexity() const;
	value :: Integer getIndex() const;

	const Substitution_* findSubstitution (const index :: Arity) const;
	void newSubstitution (Substitution_* = NULL);
	const Substitution_* getSubstitution() const;
	Substitution_*& substitution();

	index :: Arity getVariable() const;
	index :: Arity getTerm (const index :: Arity) const;
	bool findVarTermPair (index :: Arity&, index :: Arity&) const;

	bool isVarTermPair (const index :: Arity, const index :: Arity) const;

	bool fixedAreEqual() const;
	bool allAreEqual() const;
	bool checkTermType
	(
		const index :: Arity,
		const index :: Arity,
		const Term_* const
	) const;
	bool checkTermAccessible (const index :: Arity, const Term_* const) const;
	bool checkTermVariables (const index :: Arity, const Term_* const) const;

	void initData();
	void intersectData (const bool);
	void intersectData (const index :: Arity, const Term_*);
	bool isGood();
	bool isNonempty();

	//Evidence_* getValue (const index :: Arity) const;
	Container_&  getValues (const index :: Arity) const;
	void insert (const index :: Arity, const Term_*);

	bool isLastColumn() const;
	void shiftColumn (const Unit*);

	void show (String&) const;
	void showUnit (String&) const;
	void showBranch (String&) const;
	void dump() const;
	void verifyIntegrity() const;

private :
	template<class, class>
	friend class Unifier;

	value :: Integer getUnitLength (const Substitution_*) const;
	value :: Integer getComplexity
	(
		const index :: Arity,
		const Term_* const
	) const;
	value :: Integer getUnitLength
	(
		const index :: Arity,
		const value :: Integer insertionLength,
		const Substitution_* substitution
	) const;
	value :: Integer getUnitLength
	(
		const Symbol& variable,
		const value :: Integer insertionLength,
		const Substitution_* substitution
	) const;
	index :: Literal getSubstitutedLength (const Term_* const) const;
	index :: Literal getSubstitutedLength
	(
		const Symbol& variable,
		const index :: Literal insertionLength,
		const typename Substitution_ :: Term_* const term
	) const;
	bool checkResult (Expression_**, const Substitution_*) const;
	void verificationFail (Expression_**, const Substitution_*) const;

	typedef
		typename array :: Array
		<
			Container_,
			storage :: ByValue,
			Allocator_
		>
		_Data_;

	struct Data_ : public _Data_ {
		Data_ (const value :: Integer size, const Data_* prev = NULL) :
		_Data_ (size),
		prev_ (prev) {
		}
		const Data_* prev_;
	};

	const Substitution_* substitution_;
	Data_* data_;
	const Matrix_& matrix_;
	value :: Integer index_;
	const Unit* prev_;
};

	template<class C, class A>
	String&
	operator << (String&, const Unit<C, A>&);
	template<class C, class P, class A>
	std :: ostream&
	operator << (std :: ostream&, const Unit<C, A>&);
}
}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_SUB_TREE_UNIT_HPP_*/
