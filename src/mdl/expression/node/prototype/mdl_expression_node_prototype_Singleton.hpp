/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_prototype_Singleton.hpp              */
/* Description:     represents a singleton node (0-dimensional)              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/expression/mdl_expression_Symbol.hpp"
#include "mdl/expression/iterator/mdl_expression_iterator.hpp"

namespace mdl {
namespace expression {
namespace node {
namespace prototype {

template<class T, class N, template<class, class> class S, class A>
class Singleton :
	public Symbol,
	public Scalar<N, A> {
public :
	typedef T Term_;
	typedef N Node_;
	typedef A Allocator_;
	typedef S<Term_, Allocator_> Terms_;
	template<class T1, class A1>
	class _Terms_ : public S<T1, A1> {
	};

	typedef
		typename iterator :: Singleton<Node_>
		Iterator_;
	typedef
		typename iterator :: constant :: Singleton<Node_>
		const_Iterator_;

	Singleton();
	Singleton (const Symbol&);
	~ Singleton();

	void deleteNodes() const;

	template<class P>
	void cloneContents (P*) const;

	Iterator_ getIterator();
	const_Iterator_ getIterator() const;

	Terms_& terms();
	const Terms_& getTerms() const;

	void write (String&) const;
	void operator = (const Symbol&);
	void operator = (const Singleton&);
	bool isReacheable (const index :: Step) const;
	index :: Step getLevel() const;
	void setLevel (const index :: Step);
	bool getAccessible() const;
	void setAccessible (const bool = true);

	template<class T1, class N1, template<class, class> class S1, class A1>
	bool coinsides
	(
		const Singleton<T1, N1, S1, A1>&,
		const Term_*,
		const T1*
	) const;

	void showSymbol (String&) const;
	void showTerms (String&) const;
	void showAll (String&) const;
	void showBack (String&) const;
	static void showKind (String&);

	// object :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	void show (String&) const;
	void dump() const;

protected :
	template<class R>
	Size_t getAggregateVolume (const R* const) const;
	template<class R>
	void deleteAggregateObject (R*&);

private :
	Terms_ terms_;
};

	template<class T, class N, template<class, class> class S, class A>
	String&
	operator << (String&, const Singleton<T, N, S, A>&);
}
}
}
}


