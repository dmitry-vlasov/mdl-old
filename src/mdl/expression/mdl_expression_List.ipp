/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_List.ipp                                  */
/* Description:     list expression class                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_LIST_IPP_
#define MDL_EXPRESSION_LIST_IPP_

namespace mdl {
namespace expression {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	List<A> :: List () :
	Expression_ (),
	term_ (NULL) {
	}
	template<class A>
	template<class E>
	inline
	List<A> :: List (const E* const expression) :
	Expression_ (),
	term_ (NULL)
	{
		typedef E Expression;
		term_ =
			createTerm<typename Expression :: Term_>
				(expression->getTerm());
		#ifdef DEBUG
		term_->verifyIntegrity();
		#endif
	}
	template<class A>
	inline
	List<A> :: List (const Term_* term) :
	Expression_ (),
	term_ (term) {
		#ifdef DEBUG
		term_->verifyIntegrity();
		#endif
	}
	// single variable
	template<class A>
	inline
	List<A> :: List
	(
		const mdl :: Type* type,
		const Term_* parent
	) :
	Expression_ (),
	term_ (NULL) {
		term_ = createTerm (type, parent);
		#ifdef DEBUG
		term_->verifyIntegrity();
		#endif
	}
	template<class A>
	inline
	List<A> :: ~ List ()
	{
		if (term_ != NULL) {
			term_->deleteNodes();
			term_ = NULL;
		}
	}

using manipulator :: endLine;

	template<class A>
	inline const typename List<A> :: Term_*
	List<A> :: createTerm (const Term_* const term, List* const list)
	{
		Builder<List, Term_> builder (term);
		return builder.build (list);
	}
	template<class A>
	template<class T>
	inline const typename List<A> :: Term_*
	List<A> :: createTerm (const T* const term, List* const list)
	{
		typedef T Term;
		Builder<List, Term> builder (term);
		return builder.build (list);
	}
	template<class A>
	template<class T>
	inline typename List<A> :: List*
	List<A> :: createList (const T* const term)
	{
		typedef T Term;
		List* list = new List();
		list->term_ = createTerm<Term> (term, list);
		return list;
	}

using manipulator :: underline;

	template<class A>
	const typename List<A> :: Term_*
	List<A> :: createSingleton (const Symbol& symbol)
	{
		Node_* node = new Node_ (symbol);
		Iterator_ iterator (node);
		Term_* const
			term = Term_ :: template create<Allocator_>
				(iterator, iterator, symbol.getType());
		node->terms().initial().addFirst (term);
		node->terms().terminal().addFirst (term);
		#ifdef DEBUG
		term->verifyIntegrity();
		#endif
		return term;
	}
	template<class A>
	const typename List<A> :: Term_*
	List<A> :: createSingleton
	(
		mdl :: Type* type,
		const Term_* parent
	)
	{
		value :: Literal
			literal = value :: undefined :: LITERAL;
		Memory :: stack().push();
		nstd :: String<allocator :: Stack> string (64);
		const String&
			originalString = Table :: literals()->add ("x");
		while (true) {
			string << originalString << underline << counter_ ++;
			if (Table :: literals()->find (string) == value :: undefined :: LITERAL) {
				literal = Table :: literals()->add (string);
				break;
			} else {
				string.clear();
			}
		}
		Memory :: stack().pop();

		Symbol symbol (literal);
		symbol.setType (type);
		symbol.setReplaceable();
		Node_* node = new Node_ (symbol);
		Iterator_ iterator (node);
		Term_* const
			term = Term_ :: template create<Allocator_>
				(iterator, iterator, type);
		node->terms().initial().addFirst (term);
		node->terms().terminal().addFirst (term);
		term->setParent (parent);
		#ifdef DEBUG
		term->verifyIntegrity();
		#endif
		return term;
	}

	template<class A>
	inline void
	List<A> :: clearCounter() {
		counter_ = 0;
	}
	template<class A>
	inline bool
	List<A> :: isNull() const {
		return (term_ == NULL);
	}
	template<class A>
	inline bool
	List<A> :: isEmpty() const {
		return (term_ == NULL);
	}

	template<class A>
	const typename List<A> :: Term_*
	List<A> :: getTerm() const {
		return term_;
	}
	template<class A>
	typename List<A> :: Term_*
	List<A> :: getTerm() {
		return const_cast<Term_*>(term_);
	}

	template<class A>
	template<class T>
	inline void
	List<A> :: execute (const Substitution<T>* const substitutions) {
		term_ = const_cast<Term_*>(term_)->execute (substitutions);
	}

	// object :: Object interface
	template<class A>
	void
	List<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	inline Size_t
	List<A> :: getVolume() const {
		return Expression_:: getVolume();
	}
	template<class A>
	inline Size_t
	List<A> :: getSizeOf() const {
		return sizeof (List);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	void
	List<A> :: excludeTerm (const Term_* term)
	{
		const Term_*
			insertion = createTerm
			(
				term->getType(),
				term->getParent()
			);
		term_ = term_->insert (term, insertion);
	}
	template<class A>
	void
	List<A> :: excludeSubterms
	(
		const Term_* term,
		Iterator_& iterator
	)
	{
		while (true) {
			++ iterator;
			const Term_* const
				subterm = iterator->getTerms().getInitial().getTerm();
			if (subterm->isComplex()) {
				excludeTerm (subterm);
			}
			if (iterator == term->getEnd()) {
				break;
			}
		}
	}
	template<class A>
	const typename List<A> :: Term_*
	List<A> :: createListTerm (const Term_* const term)
	{
		Memory :: stack().push();
		Pool_* pool = new Pool_();

		const Iterator_ begin = const_cast<Term_*>(term)->getBegin();
		const Iterator_ end = const_cast<Term_*>(term)->getEnd();
		Iterator_ iterator = begin;

		Node_* node = NULL;
		Node_* first = NULL;
		Node_* last = NULL;

		while (true) {
			Node_* next = new Node_();
			Node_* prev = node;
			*next = *iterator;
			if (prev != NULL) {
				prev->template link<direction :: RIGHT> (next);
			}
			next->template link<direction :: LEFT> (prev);
			next->template link<direction :: RIGHT> (NULL);
			node = next;

			first = (first == NULL) ? node : first;

			pool->add (iterator.getNode(), node);

			if (iterator == end) {
				last = node;
				break;
			}
			++ iterator;
		}
		cloneListTerms (first, last, pool);
		Memory :: stack().pop();
		const Term_* result = first->getTerms().getInitial().getTerm();
		return result;
	}
	template<>
	const List<allocator :: Stack> :: Term_*
	List<allocator :: Stack> :: createListTerm (const Term_* const term)
	{
		Pool_* pool = new Pool_();

		const Iterator_ begin = const_cast<Term_*>(term)->getBegin();
		const Iterator_ end = const_cast<Term_*>(term)->getEnd();
		Iterator_ iterator = begin;

		Node_* node = NULL;
		Node_* first = NULL;
		Node_* last = NULL;

		while (true) {
			Node_* next = new Node_();
			Node_* prev = node;
			*next = *iterator;
			if (prev != NULL) {
				prev->link<direction :: RIGHT> (next);
			}
			next->link<direction :: LEFT> (prev);
			next->link<direction :: RIGHT> (NULL);
			node = next;

			first = (first == NULL) ? node : first;

			pool->add (iterator.getNode(), node);

			if (iterator == end) {
				last = node;
				break;
			}
			++ iterator;
		}
		cloneListTerms (first, last, pool);
		const Term_* result = first->getTerms().getInitial().getTerm();
		return result;
	}
	template<class A>
	void
	List<A> :: cloneListTerms (const Node_* first, const Node_* last, Pool_* pool)
	{
		const Node_* node = first;
		while (true) {
			node->cloneContents (pool);
			if (node == last) {
				break;
			}
			node = node->goRight();
		}
	}

	/************************************
	 *		Static private attributes
	 ************************************/

	template<class A>
	value :: Integer
		List<A> :: counter_ = 0;
}
}

#endif /*MDL_EXPRESSION_LIST_IPP_*/
