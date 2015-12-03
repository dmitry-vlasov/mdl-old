/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_Array.hpp                            */
/* Description:     array expression node                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_NODE_ARRAY_HPP_
#define MDL_EXPRESSION_NODE_ARRAY_HPP_

#include "mdl/expression/node/prototype/mdl_expression_node_prototype_Singleton.hpp"
#include "mdl/expression/node/terms/mdl_expression_node_terms.hpp"
#include "mdl/expression/mdl_expression_Term.hpp"
#include "mdl/expression/parse/mdl_expression_parse_Term.hpp"

namespace mdl {
namespace expression {
namespace node {

template<class A = allocator :: Heap>
class Array :
	public prototype :: Singleton
	<
		parse :: Term<Array<A> >,
		Array<A>,
		terms :: Linear, A
	> {
public :
	typedef A Allocator_;
	typedef Array<Allocator_> Node_;
	typedef
		typename parse :: Term<Node_>
		Term_;
	typedef
		typename prototype :: Singleton
		<
			Term_, Node_,
			terms :: Linear, Allocator_
		>
		Singleton_;
	typedef
		typename iterator :: modifier :: Lintree
		<
			iterator :: Linear<Array>
		>
		Iterator_;
	typedef
		typename iterator :: modifier :: Lintree
		<
			iterator :: constant :: Linear<Array>
		>
		const_Iterator_;

	template<class A1>
	class Alternative {
	public :
		typedef A1 Allocator_;
		typedef
			Array<Allocator_>
			Result_;
	};
	enum {
		IS_ITERABLE_FORTH = true,
		IS_ITERABLE_BACK = true
	};

	Array();
	Array (const Array&);
	~ Array();

	template<class>
	Node_* cloneSelf() const;

	Iterator_ getIterator();
	const_Iterator_ getIterator() const;

	Node_* getLeft();
	Node_* getRight();
	const Node_* getLeft() const;
	const Node_* getRight() const;

	Array* goLeft();
	Array* goRight();
	const Array* goLeft() const;
	const Array* goRight() const;

	template<Direction>
	bool isTerminal (const typename expression :: Array<Allocator_>* = NULL) const;

	void operator = (const Symbol&);
	void operator = (const Array&);

	void showSymbol (String&) const;
	void showTerms (String&) const;
	void showBack (String&) const;

	static void showKind (String&);

	// object :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	void show (String&) const;
	void dump() const;
};

}
}
}

#endif /*MDL_EXPRESSION_NODE_ARRAY_HPP_*/
