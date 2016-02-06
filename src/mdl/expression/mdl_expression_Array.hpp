/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_Array.hpp                                 */
/* Description:     array expression                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/expression/mdl_expression_Linear.hpp"
#include "mdl/expression/node/mdl_expression_node_Array.hpp"

namespace mdl {
namespace expression {

template<class A = allocator :: Heap>
class Array :
	public Linear<node :: Array, A>,
	public Scalar<Array<A>, A> {
private :
	typedef
		Linear<node :: Array, A>
		Expression_;
public :
	typedef A Allocator_;
	typedef
		typename Expression_ :: Term_
		Term_;
	typedef
		typename Term_ :: Substitution_
		Substitution_;
	typedef
		typename Expression_ :: Node_
		Node_;
	typedef
		typename array :: Array
		<
			Node_,
			storage :: ByValue,
			Allocator_
		>
		Array_;
	typedef
		typename Expression_ :: const_Iterator_
		const_Iterator_;
	typedef
		typename Expression_ :: Iterator_
		Iterator_;

	Array (const value :: Literal*, const index :: Literal, const bool isReplaceable = true);
	Array (const vector :: value :: Literal&, const bool isReplaceable = true);
	Array (const Array&, const bool isReplaceable = true);
	template<class E>
	Array (const E* const);
	~ Array();

	template<class T>
	static const Term_* createTerm (const T*);
	template<class T>
	static Array* createArray (const T*);

	const Node_& operator [] (const index :: Literal) const;
	const Symbol& getSymbol (const index :: Literal) const;
	index :: Literal getSize() const;

	bool isEqual (const Array*) const;
	bool operator == (const Array&) const;
	bool operator != (const Array&) const;
	bool isPrimitive() const;
	bool isSingleton() const;
	bool isVariable() const;
	bool isConstant() const;
	bool isEmpty() const;
	bool isNull() const;

	Iterator_ getBegin();
	Iterator_ getEnd();
	const_Iterator_ getBegin() const;
	const_Iterator_ getEnd() const;

	virtual const Term_* getTerm() const;
	virtual Term_* getTerm();

	void build (const object :: Typing*, const bool makeFixed = false);
	void parse (const mdl :: Type*);
	void create (const mdl :: Rule*);

	void write (String&) const;
	void write (String&, const Indent) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	Array (const index :: Literal);
	template<class P>
	void clone (P*);

	Array_ array_;
};

}
}


