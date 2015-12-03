/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_Term.ipp                                  */
/* Description:     expression term (subexpression)                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_TERM_IPP_
#define MDL_EXPRESSION_TERM_IPP_

#include "mdl/expression/mdl_expression_Mode.hpp"

namespace mdl {
namespace expression {

	/****************************
	 *		Public members
	 ****************************/

	template<class N>
	template<class A>
	inline typename Term<N> :: template Alternative<A> :: Result_*
	Term<N> :: castAway()
	{
		typedef A Allocator;
		typedef
			typename Alternative<Allocator> :: Result_
			Alternative;
		return reinterpret_cast<Alternative*>(this);
	}
	template<class N>
	template<class A>
	inline const typename Term<N> :: template Alternative<A> :: Result_*
	Term<N> :: castAway() const
	{
		typedef A Allocator;
		typedef
			typename Alternative<Allocator> :: Result_
			Alternative;
		return reinterpret_cast<const Alternative*>(this);
	}

	template<class N>
	template<class A>
	inline Term<N>*
	Term<N> :: create (const Term& term)
	{
		typedef A Allocator;
		return Factory<Term, Allocator> :: template
			create<const Term&> (term);
	}
	template<class N>
	template<class A>
	inline Term<N>*
	Term<N> :: create
	(
		const Iterator_ variable,
		const mdl :: Type* const type
	)
	{
		typedef A Allocator;
		return Factory<Term, Allocator> :: template
			create<const Iterator_, const mdl :: Type*> (variable, type);
	}
	template<class N>
	template<class A>
	inline Term<N>*
	Term<N> :: create
	(
		const Iterator_ begin,
		const Iterator_ end,
		const mdl :: Type* type
	)
	{
		typedef A Allocator;
		return Factory<Term, Allocator> :: template create
			<const Iterator_,const Iterator_,const mdl :: Type* const>
				(begin, end, type);
	}

	template<class N>
	template<class P>
	inline const Term<N>*
	Term<N> :: clone (P* pool) const
	{
		return pool->clone (this);
	}
	template<class N>
	template<class A>
	inline const Term<N>*
	Term<N> :: cloneSelf () const
	{
		typedef A Allocator;
		return create<Allocator> (*this);
	}
	template<class N>
	template<class P>
	inline void
	Term<N> :: cloneContents (P* pool) const
	{
		parent_ = pool->clone (parent_);
		begin_ = Iterator_ (pool->clone (begin_.operator ->()));
		end_ = Iterator_ (pool->clone (end_.operator ->()));
	}

	template<class N>
	template<class A>
	inline const Term<typename node :: List<A> >*
	Term<N> :: createList() const
	{
		typedef A Allocator;
		typedef List<Allocator> List;
		return List :: createTerm (this);
	}
	template<class N>
	template<class N1>
	inline const Term<N1>*
	Term<N> :: createOther() const
	{
		typedef
			typename type :: template Map<N1> :: Expression_
			Expression;
		return Expression :: template createTerm<Term> (this);
	}

	template<class N>
	inline
	Term<N> :: Term
	(
		const Iterator_ symbol,
		const mdl :: Type* type
	) :
	begin_ (symbol),
	end_  (symbol),
	parent_ (NULL),
	type_ ((type == NULL) ? symbol->getType() : type) {
	}
	template<class N>
	inline
	Term<N> :: Term
	(
		const Iterator_ begin,
		const Iterator_ end,
		const mdl :: Type* type
	) :
	begin_ (begin),
	end_  (end),
	parent_ (NULL),
	type_ (type) {
	}
	template<class N>
	inline
	Term<N> :: Term (const Term& term) :
	begin_ (term.begin_),
	end_  (term.end_),
	parent_ (term.parent_),
	type_ (term.type_) {
	}
	template<class N>
	inline
	Term<N> :: Term (const Term* const term) :
	begin_ (term->begin_),
	end_  (term->end_),
	parent_ (term->parent_),
	type_ (term->type_) {
	}
	template<class N>
	inline
	Term<N> :: ~ Term() {
	}

	template<class N>
	inline void
	Term<N> :: addSelf (const bool first) const
	{
		if (first) {
			begin_->terms().initial().addFirst (this);
			end_->terms().terminal().addFirst (this);
		} else {
			begin_->terms().initial().addLast (this);
			end_->terms().terminal().addLast (this);
		}
	}
	template<class N>
	inline void
	Term<N> :: deleteNodes() const
	{
		Iterator_ iterator = end_;
		while (true) {
			const Node_*
				node = iterator.getNode();
			if (iterator == begin_) {
				delete node;
				break;
			}
			-- iterator;
			delete node;
		}
	}

	template<class N>
	inline typename Term<N> :: Iterator_
	Term<N> :: getBegin() {
		return begin_;
	}
	template <class N>
	inline typename Term<N> :: Iterator_
	Term<N> :: getEnd() {
		return end_;
	}
	template<class N>
	inline typename Term<N> :: const_Iterator_
	Term<N> :: getBegin() const {
		return const_Iterator_ (begin_);
	}
	template<class N>
	inline typename Term<N> :: const_Iterator_
	Term<N> :: getEnd() const {
		return const_Iterator_ (end_);
	}

	template<class N>
	value :: Integer
	Term<N> :: getLength() const
	{
		value :: Integer length = 1;
		for (const_Iterator_ iterator = getEnd(); iterator != getBegin(); -- iterator) {
			++ length;
			#ifdef DEBUG
			if (length > VERIFICATION_CRITICAL_LENGTH) {
				return value :: undefined :: INTEGER;
			}
			#endif
		}
		return length;
	}
	template<class N>
	value :: Integer
	Term<N> :: getDepth() const
	{
		value :: Integer depth = 0;
		const Term_* term = parent_;
		while (term != NULL) {
			++ depth;
			term = term->getParent();
		}
		return depth;
	}
	template<class N>
	inline value :: Integer
	Term<N> :: getHeight() const {
		return computeHeight();
	}
	template<class N>
	inline value :: Integer
	Term<N> :: getSymbolVolume() const {
		return getLength();
	}
	template<class N>
	inline value :: Integer
	Term<N> :: getComplexity() const {
		return getLength();
	}

	template<class N>
	inline bool
	Term<N> :: isNull() const {
		return (this == NULL);
	}
	template<class N>
	inline bool
	Term<N> :: isEmpty() const {
		return (this == NULL);
	}
	template<class N>
	inline bool
	Term<N> :: isUndefined() const
	{
		return
			(begin_->isUndefined()) &&
			(end_->isUndefined());
	}
	template<class N>
	inline bool
	Term<N> :: isLambda() const
	{
		return
			(begin_->isLambda()) &&
			(end_->isLambda());
	}
	template<class N>
	inline bool
	Term<N> :: isDefined() const {
		return !isUndefined();
	}
	template<class N>
	inline bool
	Term<N> :: isVariable() const
	{
		return
			(begin_ == end_) &&
			(begin_->isVariable());
	}
	template<class N>
	inline bool
	Term<N> :: isConstant() const
	{
		return
			(begin_ == end_) &&
			(begin_->isConstant());
	}
	template<class N>
	inline bool
	Term<N> :: isReplaceable() const
	{
		return
			(begin_ == end_) &&
			(begin_->isReplaceable());
	}
	template<class N>
	inline bool
	Term<N> :: isSimple() const {
		return (begin_ == end_);
	}
	template<class N>
	inline bool
	Term<N> :: isComplex() const {
		return (begin_ != end_);
	}
	template<class N>
	inline bool
	Term<N> :: isSymbol (const Symbol& symbol) const {
		return
			(begin_ == end_) &&
			(*begin_ == symbol);
	}
	template<class N>
	template<class I>
	inline bool
	Term<N> :: isEqual (const I begin_2, const I end_2, const mdl :: Type* type) const
	{
		if (getType() != type) {
			return false;
		}
		const const_Iterator_ end_1 = getEnd();
		const const_Iterator_ begin_1 = getBegin();
		const_Iterator_ iterator_1 = end_1;

		typedef I Iterator;
		Iterator iterator_2 = end_2;

		while (true) {
			if (*iterator_1 != *iterator_2) {
				return false;
			}
			if (iterator_1 == begin_1) {
				if (iterator_2 == begin_2) {
					return true;
				}
				return false;
			}
			if (iterator_2 == begin_2) {
				if (iterator_1 == begin_1) {
					return true;
				}
				return false;
			}
			-- iterator_1;
			-- iterator_2;
		}
		return true;
	}
	template<class N>
	template<class I>
	inline bool
	Term<N> :: isEqualLiteraly (const I begin_2, const I end_2) const
	{
		const const_Iterator_ end_1 = getEnd();
		const const_Iterator_ begin_1 = getBegin();
		const_Iterator_ iterator_1 = end_1;

		typedef I Iterator;
		Iterator iterator_2 = end_2;

		while (true) {
			if (!iterator_1->isEqualLiteraly (*iterator_2)) {
				return false;
			}
			if (iterator_1 == begin_1) {
				if (iterator_2 == begin_2) {
					return true;
				}
				return false;
			}
			if (iterator_2 == begin_2) {
				if (iterator_1 == begin_1) {
					return true;
				}
				return false;
			}
			-- iterator_1;
			-- iterator_2;
		}
		return true;
	}
	template<class N>
	bool
	Term<N> :: contains (const Symbol& symbol) const
	{
		const const_Iterator_ end = getEnd();
		const const_Iterator_ begin = getBegin();
		const_Iterator_ iterator = end;
		while (true) {
			if (*iterator == symbol) {
				return true;
			}
			if (iterator == begin) {
				return false;
			}
			-- iterator;
		}
	}

	template<class N>
	inline void
	Term<N> :: operator = (const Term& term)
	{
		begin_ = term.begin_;
		end_ = term.end_;
		type_ = term.type_;
		parent_ = term.type_;
	}

	template<class N>
	bool
	Term<N> :: operator == (const Symbol& symbol) const
	{
		const const_Iterator_ end = getEnd();
		const const_Iterator_ begin = getBegin();
		if (end != begin) {
			return false;
		}
		return *begin == symbol;
	}
	template<class N>
	bool
	Term<N> :: operator != (const Symbol& symbol) const {
		return !operator == (symbol);
	}
	template<class N>
	template<class T>
	bool
	Term<N> :: operator == (const T& term) const
	{
		#ifdef DEBUG
		verifyIntegrity();
		#endif
		return isEqual (term);
	}
	template<class N>
	template<class T>
	inline bool
	Term<N> :: operator != (const T& term) const {
		return !(operator == (term));
	}
	template<class N>
	template<class T>
	inline bool
	Term<N> :: coinsides (const T& term) const
	{
		typedef Term Term_0;
		typedef T Term_1;
		#ifdef DEBUG
		verifyIntegrity();
		#endif /*DEBUG*/
		return coinsides_p<Term_1, Term_0>(term, this);
	}
	template<class N>
	template<class T>
	bool
	Term<N> :: isEqual (const T& term) const
	{
		typedef T Term1;
		typedef
			typename Term1 :: const_Iterator_
			const_Iterator_1_;
		const const_Iterator_1_ termEnd = term.getEnd();
		const const_Iterator_1_ termBegin = term.getBegin();
		const mdl :: Type* termType = term.getType();
		return isEqual<const_Iterator_1_> (termBegin, termEnd, termType);
	}
	template<class N>
	template<class T>
	bool
	Term<N> :: isEqualLiteraly (const T& term) const
	{
		typedef T Term1;
		typedef
			typename Term1 :: const_Iterator_
			const_Iterator_1_;
		const const_Iterator_1_ termEnd = term.getEnd();
		const const_Iterator_1_ termBegin = term.getBegin();
		return isEqualLiteraly<const_Iterator_1_> (termBegin, termEnd);
	}

	template<class N>
	inline const typename Term<N> :: Term_*
	Term<N> :: getTerm() const {
		return this;
	}
	template<class N>
	inline const typename Term<N> :: Term_*
	Term<N> :: getParent() const {
		return parent_;
	}
	template<class N>
	inline const mdl :: Type*
	Term<N> :: getType() const {
		return type_;
	}
	template<class N>
	inline void
	Term<N> :: setParent (const Term_* parent) const {
		parent_ = parent;
	}
	template<class N>
	inline void
	Term<N> :: setType (const mdl :: Type* type) const {
		type_ = type;
	}

	template<class N>
	template<class S>
	const typename Term<N> :: Term_*
	Term<N> :: execute (const S* substitution)
	{
		#ifdef DEBUG
		verifyIntegrity();
		#endif
		if (substitution == NULL) {
			return this;
		}
		typedef S Substitution;
		typedef
			typename Substitution :: Term_
			Term;
		const Iterator_ begin = begin_;
		const Iterator_ end = end_;
		Iterator_ iterator = end;
		Iterator_ iteratorDec = end;

		const Term_* result = this;
		while (true) {
			if (iterator != begin) {
			-- iteratorDec;
			}
			if (iterator->isReplaceable()) {
				const Symbol&
					symbol = *iterator;
				const Substitution*
					sub = substitution->find (symbol);
				if ((sub != NULL) && symbol.isReplaceable()) {
					result = insertTerm<Term> (iterator, sub->getTerm());
				}
			}
			if (iterator == begin) {
				break;
			}
			iterator = iteratorDec;
		}
		#ifdef DEBUG
		result->verifyIntegrity();
		#endif
		return result;
	}

	template<class N>
	template<class I>
	inline void
	Term<N> :: copyNode (Iterator_& target, const I& source)
	{
		*target = static_cast<const Symbol&>(*source);
		target->setLevel (source->getLevel());
		target->setAccessible (source->getAccessible());
	}
	template<class N>
	template<class I>
	inline bool
	Term<N> :: findNode (Iterator_& target, const I& source) {
		return (*target == *source);
	}
	template<class N>
	template<class I>
	inline void
	Term<N> :: addFindNode (Iterator_& target, const I& source) {
		*target = static_cast<const Symbol&>(*source);
	}

	template<class N>
	inline void
	Term<N> :: verifyIntegrity (const bool linear) const
	{
		Memory :: stack().push();
		verifyPlain (this, linear);
		verifyNodes (linear);
		Memory :: stack().pop();
	}

using manipulator :: space;
using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: underline;
using manipulator :: iterate;
using manipulator :: mode;

	template<class N>
	inline Size_t
	Term<N> :: getExpressionVolume() const
	{
		Size_t volume = 0;
		const const_Iterator_ end = getEnd();
		const const_Iterator_ begin = getBegin();
		const_Iterator_ iterator = end;
		while (true) {
			volume += iterator->getVolume();
			volume += iterator->getSizeOf();
			if (iterator == begin) {
				break;
			}
			-- iterator;
		}
		return volume;
	}
	template<class N>
	void
	Term<N> :: showBody (String& string) const
	{
		const value :: Integer length = getLength();
		if (length == value :: undefined :: INTEGER) {
			string << "<undef>";
			return;
		}
		Symbol buffer [length];

		const_Iterator_ iterator = getEnd();
		for (value :: Integer i = 0; i < length; ++ i) {
			if (iterator.isNull()) {
				break;
			}
			buffer [i] = *iterator;
			-- iterator;
		}
		for (value :: Integer i = 0; i < length; ++ i) {
			buffer [length - i - 1].show (string);
			string << space;
		}
 	}
	template<class N>
	void
	Term<N> :: showKind (String& string) const {
		Node_ :: showKind (string);
 	}
	template<class N>
	void
	Term<N> :: showType (String& string) const
	{
		string << "type: ";
		if (type_!= NULL) {
			type_->replicateName (string);
		} else {
			string << "NULL";
		}
 	}
	template<class N>
	void
	Term<N> :: showTerms (String& string) const
	{
		Node_ :: showKind (string);
		string << "(" << this << " = ";
		string << *this << ")" << endLine;

		const value :: Integer length = getLength();
		if (length == value :: undefined :: INTEGER) {
			return;
		}
		String buffer [length];
		const_Iterator_ iterator = getEnd();
		for (value :: Integer i = 0; i < length; ++ i) {
			if (iterator.isNull()) {
				buffer [i] << "null iterator";
				break;
			}
			buffer [i] << "symbol: ";
			iterator->showSymbol (buffer [i]);
			buffer [i] << endLine;
			buffer [i] << iterate << 32 << '-' << endLine;
			iterator->showTerms (buffer [i]);
			buffer [i] << iterate << 32 << '=' << endLine;
			-- iterator;
		}
		for (value :: Integer i = 0; i < length; ++ i) {
			string << buffer [length - i - 1] << space;
		}
	}
	template<class N>
	void
	Term<N> :: writeMultylineForward
	(
		String& string,
		const Indent indent,
		int depth
	) const
	{
		const bool showTypes = Config :: expressionsWithTypes();
		const int length = getLength();
		const bool oneLine =
			(length < Config :: multylineMinWidth()) ||
			(depth  * Config :: multylineTabWidth() + length < Config :: multylineMaxWidth());

		const const_Iterator_ begin = getBegin();
		const const_Iterator_ end = getEnd();
		const_Iterator_ iterator = begin;

		typedef
			typename Node_ :: Terms_ :: Initial_ :: Node_
			InitialNode;
		typedef
			typename Node_ :: Terms_ :: Terminal_ :: Node_
			TerminalNode;

		while (true) {
			if (iterator == getEnd()) {
				-- depth;
			}
			if (!oneLine && iterator != getBegin()) {
				string << indent << iterate << depth << tab;
			}
			if (iterator == getBegin()) {
				++ depth;
			}
			const InitialNode* initial = iterator->getTerms().getInitial().getFirst();
			if (iterator != getBegin() && initial != NULL) {
				const Term_* subTerm = initial->getValue();
				subTerm->writeMultylineForward (string, indent, depth);
				iterator = subTerm->getEnd();
			} else {
				iterator->write (string);
				string << space;
			}
			if (iterator == getEnd()) {
				if (showTypes) {
					string << ": ";
					getType()->replicateName (string);
				}
				break;
			}
			if (!oneLine) {
				string << endLine;
			}
			++ iterator;
		}
	}
	template<class N>
	void
	Term<N> :: writeMultylineBackward
	(
		String& string,
		const Indent indent,
		int depth
	) const
	{
		const bool showTypes = Config :: expressionsWithTypes();
		const int length = getLength();
		const bool oneLine =
			(length < Config :: multylineMinWidth()) ||
			(depth  * Config :: multylineTabWidth() + length < Config :: multylineMaxWidth());

		const const_Iterator_ begin = getBegin();
		const const_Iterator_ end = getEnd();
		const_Iterator_ iterator = end;

		typedef
			typename Node_ :: Terms_ :: Initial_ :: Node_
			InitialNode;
		typedef
			typename Node_ :: Terms_ :: Terminal_ :: Node_
			TerminalNode;
		typedef
			typename vector :: Vector
			<
				const TerminalNode*,
				storage :: ByValue,
				allocator :: Standard
			>
			TerminalNodeVector;

		if (showTypes) {
			TerminalNodeVector nodeVector;
			const TerminalNode* terminal = iterator->getTerms().getTerminal().getFirst();
			while (terminal != NULL) {
				nodeVector.add (terminal);
				terminal = terminal->getNext();
			}
			nodeVector.reverse();
			for (int i = 0; i < nodeVector.getSize(); ++ i) {
				const TerminalNode* terminal = nodeVector.getValue(i);
				const Term_* subTerm = terminal->getValue();
				subTerm->getType()->replicateReversedName (string);
				string << " :";
			}
		}
		while (true) {
			if (!oneLine && iterator != end) {
				string << endLine;
			}
			if (iterator == begin) {
				-- depth;
			}
			const TerminalNode* terminal = iterator->getTerms().getTerminal().getLast();
			if (terminal != NULL && terminal->getValue()->getTerm() != this) {
				const Term_* subTerm = terminal->getValue();
				subTerm->writeMultylineBackward (string, indent, depth);
				iterator = subTerm->getBegin();
			} else {
				string << space;
				iterator->writeReversed (string);
			}
			if (!oneLine && iterator != begin) {
				string << indent << iterate << depth << tab;
			}
			if (iterator == end) {
				++ depth;
			}
			if (iterator == begin) {
				break;
			}
			-- iterator;
		}
	}

	// object :: Object implementation
	template<class N>
	inline void
	Term<N> :: commitSuicide() {
		delete this;
	}
	template<class N>
	inline Size_t
	Term<N> :: getVolume() const {
		return 0;
	}
	template<class N>
	inline Size_t
	Term<N> :: getSizeOf() const {
		return sizeof (Term);
	}
	template<class N>
	void
	Term<N> :: show (String& string) const
	{
		Mode mode (string);
		if (mode.getValue (Mode :: SHOW_HEADER)) {
			string << "term:" << endLine;
		}
		showBody (string);
		if (!mode.isPlain()) {
			string << endLine;
		}
		if (mode.getValue (Mode :: SHOW_KIND)) {
			showKind (string);
		}
		if (mode.getValue (Mode :: SHOW_TYPE)) {
			string << tab;
			showType (string);
			string << endLine;
		}
		if (mode.getValue (Mode :: SHOW_TERMS)) {
			Mode m (mode);
			m.setValue (Mode :: SHOW_TERMS, false);
			string << m;
			showTerms (string);
			string << mode;
		}
 	}
	template<class N>
	void
	Term<N> :: dump() const
	{
		enum {
			INITIAL_STRING_CAPACITY = 64
		};
		String string (INITIAL_STRING_CAPACITY);
		show (string);
		std :: cout << std :: endl << string << std :: endl;
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class N>
	template<class T1, class T0>
	inline bool
	Term<N> :: coinsides_p
	(
		const T1& term_1,
		const T0* term_0
	) const
	{
		typedef T0 Term_0;
		typedef T1 Term_1;
		typedef
			typename Term_0 :: const_Iterator_
			const_Iterator_0_;
		typedef
			typename Term_1 :: const_Iterator_
			const_Iterator_1_;

		const const_Iterator_0_ begin0 = term_0->getBegin();
		const const_Iterator_0_ end0 = term_0->getEnd();
		const_Iterator_0_ iterator0 = end0;

		const const_Iterator_1_ begin1 = term_1.getBegin();
		const const_Iterator_1_ end1 = term_1.getEnd();
		const_Iterator_1_ iterator1 = end1;

		while (true) {
			if (!iterator0->coinsides (*iterator1, term_0, &term_1)) {
				return false;
			}
			if (iterator0 == begin0) {
				if (iterator1 != begin1) {
					return false;
				} else {
					return true;
				}
			}
			if (iterator1 == begin1) {
				if (iterator0 != begin0) {
					return false;
				} else {
					return true;
				}
			}
			-- iterator0;
			-- iterator1;
		}
		return true;
	}

	template<class N>
	template<class T>
	inline const typename Term<N> :: Term_*
	Term<N> :: insertTerm (const Iterator_& iterator, const T* term)
	{
		typedef T Term;
		const Term_*
			insertion = term->template createOther<Node_>();
		insertion->setParent (iterator->getTerms().getInitial().getTerm()->getParent());
		const Term_* result = insert
		(
			iterator->getTerms().getInitial().getFirst()->getValue(),
			insertion
		);
		return result;
	}
	template<class N>
	inline const typename Term<N> :: Term_*
	Term<N> :: insert
	(
		const Term_* source,
		const Term_* target
	)
	{
		if (this == source) {
			const_cast<Term_*>(source)->deleteNodes();
			return target;
		}

		Iterator_ left = const_cast<Term_*>(source)->getBegin();
		Iterator_ right = const_cast<Term_*>(source)->getEnd();

		Node_* const
			begin = const_cast<Node_*>(target->getBegin().getNode());
		Node_* const
			end = const_cast<Node_*>(target->getEnd().getNode());

		fixInsertionEnd (source, target);
		fixInsertionBegin (source, target);

		if (!left.template isTerminal<direction :: LEFT>()) {
			-- left;
			left->setRight (begin);
			begin->setLeft (left.getNode());
		} else if (left == getBegin()) {
			begin_ = Iterator_ (begin);
		}
		if (!right.template isTerminal<direction :: RIGHT>()) {
			++ right;
			right->setLeft (end);
			end->setRight (right.getNode());
		} else if (right == getEnd()) {
			end_ = Iterator_ (end);
		}
		const_cast<Term_*>(source)->deleteNodes();
		return this;
	}
	template<class N>
	inline void
	Term<N> :: fixInsertionEnd
	(
		const Term_* source,
		const Term_* target
	)
	{
		Node_* const
			end = const_cast<Node_*>(target->getEnd().getNode());

		const typename _Terminal_ :: Node_*
			node = source->getEnd()->getTerms().getTerminal().getFirst();

		bool supTerm = false;

		while (node != NULL) {
			const Term_* const
				term = node->getValue();
			if (supTerm) {
				term->end_ = Iterator_ (end);
				end->terms().terminal().addLast (term);
			}
			if (term == source) {
				if (term->isVariable()) {
					term->setType (target->getType());
				}
				supTerm = true;
			}
			node = node->getNext();
		}
	}
	template<class N>
	inline void
	Term<N> :: fixInsertionBegin
	(
		const Term_* source,
		const Term_* target
	)
	{
		Node_* const
			begin = const_cast<Node_*>(target->getBegin().getNode());

		const typename _Initial_ :: Node_*
			node = source->getEnd()->getTerms().getInitial().getFirst();

		bool supTerm = false;

		while (node != NULL) {
			const Term_* const
				term = node->getValue();
			if (supTerm) {
				term->begin_ = Iterator_ (begin);
				begin->terms().initial().addLast (term);
			}
			if (term == source) {
				if (term->isVariable()) {
					term->setType (target->getType());
				}
				supTerm = true;
			}
			node = node->getNext();
		}
	}

	template<class N>
	inline void
	Term<N> :: verifyNodes (const bool linear) const
	{
		value :: Integer length = 1;
		for (const_Iterator_ iterator = getEnd(); iterator != getBegin(); -- iterator) {
			const _Initial_&
				initial = iterator->getTerms().getInitial();
			verifyTerms<_Initial_>(initial, linear);
			const _Terminal_&
				terminal = iterator->getTerms().getTerminal();
			verifyTerms<_Terminal_>(terminal, linear);

			++ length;
			if (iterator.isNull() || (length > VERIFICATION_CRITICAL_LENGTH)) {
				break;
			}
		}
	}
	template<class N>
	template<class T>
	void
	Term<N> :: verifyTerms (const T& terms, const bool linear) const
	{
		typedef T Terms;
		typedef
			typename Terms :: Node_
			Node;
		typedef
			typename Terms :: Term_
			Term;
		const Node* node = NULL;
		node = terms.getFirst();
		while (node != NULL) {
			const Term* const
				term = node->getValue();
			term->template verifyPlain<Term> (term, linear);
			node = node->getNext();
		}
	}
	template<class N>
	template<class T>
	inline void
	Term<N> :: verifyPlain (const T* term, const bool linear) const
	{
		verifyType();
		verifyIteratibility (linear);
		verifyInitial (term, linear);
		verifyTerminal (term);
	}
	template<class N>
	void
	Term<N> :: verifyType() const
	{
		if ((type_ != NULL) || isUndefined() || isLambda()) {
			return;
		}
		Error* error = new Error (Error :: SEMANTIC);
		Mode mode;
		mode << Mode :: SHOW_REPLACEABILITY;
		error->message() << mode;
		error->message() << "typeless term: " << endLine;
		error->message() << "this = " << this << endLine;
		error->message() << "type_ = NULL" << endLine;
		showTerms (error->message());
		throw error;
	}
	template<class N>
	template<class T>
	void
	Term<N> :: verifyInitial (const T* term, const bool linear) const
	{
		const _Initial_&
			initialTerms = getBegin()->getTerms().getInitial();
		verifyUniquity<_Initial_> (initialTerms);
		const typename _Initial_ :: Node_*
			node = NULL;
		node = initialTerms.getFirst();
		if (node == NULL) {
			goto end;
		}
		if (linear) {
			const bool isInitial = (node->getValue() == term);
			const bool isUnique = (node->getNext() == NULL);
			if (isInitial && isUnique) {
				return;
			}
		} else {
			while (node != NULL) {
				if (node->getValue() == term) {
					return;
				}
				node = node->getNext();
			}
		}
		end :
		Error* error = new Error (Error :: SEMANTIC);
		Mode mode;
		mode << Mode :: SHOW_REPLACEABILITY;
		error->message() << mode;
		error->message() << "incoherent initial term part:" << endLine;
		error->message() << "term = " << term << endLine;
		error->message() << "this = " << this << endLine;
		if (initialTerms.isEmpty()) {
			error->message() << "initial terms list is empty" << endLine;
		} else {
			node = getBegin()->getTerms().getInitial().getFirst();
			while (node != NULL) {
				error->message() << "begin = " << node->getValue() << endLine;
				node = node->getNext();
			}
		}
		error->message() << endLine;
		showTerms (error->message());

		std :: cout << std :: endl << error->message() << std :: endl;

		throw error;
	}
	template<class N>
	template<class T>
	void
	Term<N> :: verifyTerminal (const T* term) const
	{
		const _Terminal_&
			terminalTerms = getEnd()->getTerms().getTerminal();
		verifyUniquity<_Terminal_> (terminalTerms);
		const typename _Terminal_ :: Node_*
			node = NULL;
		node = terminalTerms.getFirst();
		if (node == NULL) {
			goto end;
		}
		while (node != NULL) {
			if (node->getValue() == term) {
				return;
			}
			node = node->getNext();
		}
		end :
		Error* error = new Error (Error :: SEMANTIC);
		Mode mode;
		mode << Mode :: SHOW_REPLACEABILITY;
		error->message() << mode;
		error->message() << "incoherent terminal term part:" << endLine;
		error->message() << "this = " << this << endLine;
		if (terminalTerms.isEmpty()) {
			error->message() << "terminal terms list is empty" << endLine;
		} else {
			node = terminalTerms.getFirst();
			while (node != NULL) {
				error->message() << "end = " << node->getValue() << endLine;
				node = node->getNext();
			}
		}
		error->message() << endLine;
		showTerms (error->message());

		std :: cout << error->message() << std :: endl;

		throw error;
	}
	template<class N>
	template<class T>
	void
	Term<N> :: verifyUniquity (const T& terms) const
	{
		typedef T Terms;
		typedef
			typename Terms :: Node_
			Node;
		bool uniquity = true;
		const Node* node_1 = NULL;
		const Node* node_2 = NULL;
		node_1 = terms.getFirst();
		while (node_1 != NULL) {
			node_2 = terms.getFirst();
			while (node_2 != NULL) {
				if (node_1 != node_2) {
					if (node_1->getValue() == node_2->getValue()) {
						uniquity = false; break;
					}
				}
				node_2 = node_2->getNext();
			}
			if (!uniquity) {
				break;
			}
			node_1 = node_1->getNext();
		}
		if (uniquity) {
			return;
		}
		Error* error = new Error (Error :: SEMANTIC);
		Mode mode;
		mode << Mode :: SHOW_REPLACEABILITY;
		error->message() << mode;
		error->message() << "duplicate terms:" << endLine;
		error->message() << "this: " << *this << endLine;
		error->message() << "duplicate: " << *(node_1->getValue()) << endLine;
		error->message() << endLine;
		showTerms (error->message());
		std :: cout << error->message() << std :: endl;
		throw error;
	}
	template<class N>
	void
	Term<N> :: verifyIteratibility (const bool linear) const
	{
		bool correct = true;
		bool correctBack = true;
		bool correctForth = true;
		value :: Integer backLength = 1;
		value :: Integer forthLength = 1;
		try {
			const_Iterator_ iterator = getEnd();
			while (true) {
				if (iterator.isNull() || (backLength > VERIFICATION_CRITICAL_LENGTH)) {
					correctBack = false;
					break;
				}
				if (iterator == getBegin()) {
					break;
				}
				++ backLength;
				-- iterator;
			}
		} catch (...) {
			correctBack = false;
		}
		if (linear) {
			try {
				const_Iterator_ iterator = getBegin();
				while (true) {
					if (iterator.isNull() || (forthLength > VERIFICATION_CRITICAL_LENGTH)) {
						correctForth = false;
						break;
					}
					if (iterator == getEnd()) {
						break;
					}
					++ forthLength;
					++ iterator;
				}
			} catch (...) {
				correctForth = false;
			}
			if (backLength != forthLength) {
				correct = false;
			}
		}
		if (correct && correctForth && correctBack) {
			return;
		}
		Error* error = new Error (Error :: SEMANTIC);
		Mode mode;
		mode << Mode :: SHOW_REPLACEABILITY;
		error->message() << mode;
		error->message() << "incorrect term iterability:" << endLine;
		error->message() << "this = " << this << endLine;
		if (!correctForth) {
			error->message() << "forth iteration fails" << endLine;
		}
		if (!correctBack) {
			error->message() << "back iteration fails" << endLine;
		}
		if (!correct) {
			error->message() << "forth and back length differs" << endLine;
		}
		error->message() << endLine;
		if (correctBack) {
			showTerms (error->message());
		}
		throw error;
	}

	template<class N>
	value :: Integer
	Term<N> :: computeHeight() const
	{
		value :: Integer height = 0;
		value :: Integer heightCounter = 0;
		const const_Iterator_ begin = getBegin();
		const_Iterator_ iterator = getEnd();
		while (true) {
			if (iterator == begin) {
				break;
			}
			{
				const _Terminal_&
					terminalTerms = iterator->getTerms().getTerminal();
				const typename _Terminal_ :: Node_*
					terminalNode = NULL;
				terminalNode = terminalTerms.getFirst();
				while (terminalNode != NULL) {
					++ heightCounter;
					terminalNode = terminalNode->getNext();
				}
			}
			{
				const _Initial_&
					initialTerms = iterator->getTerms().getInitial();
				const typename _Initial_ :: Node_*
					initialNode = NULL;
				initialNode = initialTerms.getFirst();
				while (initialNode != NULL) {
					-- heightCounter;
					initialNode = initialNode->getNext();
				}
			}
			if (heightCounter > height) {
				height = heightCounter;
			}
			-- iterator;
		}
		return height;
	}

	/******************************
	 *		Overloaded operators
	 ******************************/

	template<class N>
	String&
	operator << (String& string, const Term<N>& term)
	{
		term.show (string);
		return string;
	}
	template<class N>
	std :: ostream&
	operator << (std :: ostream& os, const Term<N>& term)
	{
		String string (1024);
		return os << (string << term);
	}
}
}

#endif /*MDL_EXPRESSION_TERM_IPP_*/
