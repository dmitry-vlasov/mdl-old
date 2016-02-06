/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_List.hpp                                  */
/* Description:     list expression class                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/auxiliary/mdl_auxiliary_Pool.hpp"
#include "mdl/expression/mdl_expression_Linear.hpp"
#include "mdl/expression/mdl_expression_Array.hpp"
#include "mdl/expression/node/mdl_expression_node_List.hpp"

namespace mdl {
namespace expression {

template<class A = allocator :: Heap>
class List :
	public Linear<node :: List, A>,
	public Scalar<List<A>, A> {
private :
	typedef
		Linear<node :: List, A>
		Expression_;
public :
	typedef
		typename Expression_ :: Node_
		Node_;
	typedef
		typename Expression_ :: Allocator_
		Allocator_;
	typedef
		typename Expression_ :: Term_
		Term_;
	typedef
		typename Term_ :: Substitution_
		Substitution_;
	typedef
		typename Expression_ :: const_Iterator_
		const_Iterator_;
	typedef
		typename Expression_ :: Iterator_
		Iterator_;

	List();
	template<class E>
	List (const E* const);
	List (const Term_*);
	// single variable
	List (const mdl :: Type*, const Term_*);
	virtual ~ List();

	static const Term_* createTerm (const Term_* const, List* const = NULL);
	template<class T>
	static const Term_* createTerm (const T* const, List* const = NULL);
	template<class T>
	static List* createList (const T* const);

	static const Term_* createSingleton (const Symbol&);
	static const Term_* createSingleton (mdl :: Type*, const Term_*);

	static void clearCounter();
	bool isNull() const;
	bool isEmpty() const;

	virtual const Term_* getTerm() const;
	virtual Term_* getTerm();

	template<class T>
	void execute (const Substitution<T>* const);
	//void factorize (const value :: Integer, const value :: Integer);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	typedef
		typename Node_ :: Terms_
		_Terms_;
	typedef
		typename _Terms_ :: Initial_
		_Initial_;
	typedef
		typename _Terms_ :: Terminal_
		_Terminal_;
	typedef
		Pool<Allocator_>
		Pool_;

	void excludeTerm (const Term_*);
	void excludeSubterms (const Term_*, Iterator_&);
	static const Term_* createListTerm (const Term_* const);
	static void cloneListTerms (const Node_*, const Node_*, Pool_*);

	const Term_* term_;
	static value :: Integer counter_;
};

namespace type {

template<class A>
class Map<node :: List<A> > {
public :
	typedef
		List<A>
		Expression_;
};

}

}
}



