/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_List.hpp                                  */
/* Description:     list container                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONTAINER_LIST_HPP_
#define NSTD_CONTAINER_LIST_HPP_

#include "container/discrete/nstd_container_discrete.hpp"

namespace nstd {
namespace container {

template
<
	class T,
	template<class> class H,
	class A,
	template<class, class, class> class N = discrete :: Unidirectional
>
class List : public
	memory :: storage :: Scalar
	<
		List<T, H, A, N>,
		A
	> {
public :
	typedef H<T> Storage_;
	struct Node_ : public N<Storage_, A, Node_> {
		typedef N<Storage_, A, Node_> Ancestor_;
		typedef
			typename Ancestor_ :: Argument_
			Argument_;
		Node_ ();
		Node_ (const Argument_, const discrete :: Direction, const Node_* = NULL);
	};

	typedef typename Node_ :: Argument_ Argument_;
	typedef typename Node_ :: Value_ Value_;
	typedef typename Node_ :: Reference_ Reference_;
	typedef typename Node_ :: const_Reference_ const_Reference_;

	List ();
	List (const List&);
	virtual ~ List();

	void operator = (const List&);
	void copy (const List&);

	const Node_* getFirst() const;
	const Node_* getLast() const;

	void addFirst (Argument_);
	void addLast (Argument_);
	void insertNextTo (Argument_, const Argument_);

	void intersect (const List&);
	bool contains (Argument_) const;

	void join (const List&);
	void unite (const List&);
	void clear();

	bool isEmpty() const;
	bool isSingleton() const;
	bool hasNoRepeats() const;
	Size_t getSize() const;

	// nstd :: Object interface
	void commitSuicide();
	Size_t getVolume () const;
	Size_t getSizeOf() const;
	template<class S>
	void show (S&) const;

private :
	const Node_* first_;
	const Node_* last_;
};

	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N,
		class S
	>
	S&
	operator << (S&, const List<T, H, A, N>&);
}
}

#endif /* NSTD_CONTAINER_LIST_HPP_ */
