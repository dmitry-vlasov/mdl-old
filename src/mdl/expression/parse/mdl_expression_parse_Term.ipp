/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_parse_Term.ipp                            */
/* Description:     expression term for parser (subexpression)               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_PARSE_TERM_IPP_
#define MDL_EXPRESSION_PARSE_TERM_IPP_

namespace mdl {
namespace expression {
namespace parse {

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
		const mdl :: Type* const type,
		const Substitution_* const substitution
	)
	{
		typedef A Allocator;
		return Factory<Term, Allocator> :: template
			create<const Iterator_, const mdl :: Type*, const Substitution_* const>
				(variable, type, substitution);
	}
	template<class N>
	template<class A>
	inline Term<N>*
	Term<N> :: create
	(
		const Iterator_ begin,
		const Iterator_ end,
		const mdl :: Type* const type,
		const mdl :: Rule* const rule,
		const Substitution_* const substitution
	)
	{
		typedef A Allocator;
		return Factory<Term, Allocator> :: template
			create
			<
				const Iterator_,
				const Iterator_,
				const mdl :: Type* const,
				const mdl :: Rule* const,
				const Substitution_* const
			>
		(
			begin,
			end,
			type,
			rule,
			substitution
		);
	}

	template<class N>
	template<class P>
	inline const Term<N>*
	Term<N> :: clone (P* pool) const {
		return pool->clone (this);
	}
	template<class N>
	template<class A>
	inline const Term<N>*
	Term<N> :: cloneSelf () const {
		typedef A Allocator;
		return create<Allocator> (*this);
	}
	template<class N>
	template<class P>
	inline void
	Term<N> :: cloneContents (P* pool) const
	{
		typedef P Pool;
		substitution_ = pool->clone (substitution_);
		term_.template cloneContents<Pool>(pool);
	}

	template<class N>
	template<class A>
	inline const typename expression :: Term<typename node :: List<A> >*
	Term<N> :: createList() const
	{
		typedef A Allocator;
		typedef List<Allocator> List;
		return List :: template createTerm<Term> (this);
	}

	template<class N>
	inline
	Term<N> :: Term() :
	term_ (),
	rule_ (NULL),
	substitution_ (NULL) {
	}
	template<class N>
	inline
	Term<N> :: Term
	(
		const Iterator_ variable,
		const mdl :: Type* const type,
		const Substitution_* const substitution
	) :
	term_ (variable, type),
	rule_ (NULL),
	substitution_ (substitution) {
	}
	template<class N>
	inline
	Term<N> :: Term
	(
		const Iterator_ begin,
		const Iterator_ end,
		const mdl :: Type* const type,
		const mdl :: Rule* const rule,
		const Substitution_* const substitution
	) :
	term_ (begin, end, type),
	rule_ (rule),
	substitution_ (substitution) {
	}
	template<class N>
	inline
	Term<N> :: Term (const Term& term) :
	term_ (term.term_),
	rule_ (term.rule_),
	substitution_ (term.substitution_) {
	}
	template<class N>
	inline
	Term<N> :: ~ Term()
	{
		if (substitution_ != NULL) {
			const_cast<Substitution_*>(substitution_)->commitSuicide();
			substitution_ = NULL;
		}
	}

	template<class N>
	inline void
	Term<N> :: addSelf (const bool first) const
	{
		if (first) {
			term_.begin_->terms().initial().addFirst (this);
			term_.end_->terms().terminal().addFirst (this);
		} else {
			term_.begin_->terms().initial().addLast (this);
			term_.end_->terms().terminal().addLast (this);
		}
	}
	template<class N>
	inline void
	Term<N> :: deleteNodes() const {
		term_.deleteNodes();
	}

	template<class N>
	inline typename Term<N> :: Iterator_
	Term<N> :: getBegin() {
		return term_.getBegin();
	}
	template <class N>
	inline typename Term<N> :: Iterator_
	Term<N> :: getEnd() {
		return term_.getEnd();
	}
	template<class N>
	inline typename Term<N> :: const_Iterator_
	Term<N> :: getBegin() const {
		return term_.getBegin();
	}
	template<class N>
	inline typename Term<N> :: const_Iterator_
	Term<N> :: getEnd() const {
		return term_.getEnd();
	}

	template<class N>
	inline value :: Integer
	Term<N> :: getLength() const {
		return term_.getLength();
	}
	template<class N>
	inline value :: Integer
	Term<N> :: getDepth() const {
		return term_.getDepth();
	}
	template<class N>
	inline value :: Integer
	Term<N> :: getHeight() const {
		return term_.getHeight();
	}
	template<class N>
	inline value :: Integer
	Term<N> :: getSymbolVolume() const {
		return term_.getSymbolVolume();
	}
	template<class N>
	inline value :: Integer
	Term<N> :: getComplexity() const {
		return term_.getComplexity();
	}

	template<class N>
	inline bool
	Term<N> :: isEmpty() const {
		return term_.isEmpty();
	}
	template<class N>
	inline bool
	Term<N> :: isUndefined() const {
		return term_.isUndefined();
	}
	template<class N>
	inline bool
	Term<N> :: isLambda() const {
		return term_.isLambda();
	}
	template<class N>
	inline bool
	Term<N> :: isDefined() const {
		return term_.isDefined();
	}
	template<class N>
	inline bool
	Term<N> :: isVariable() const {
		return term_.isVariable();
	}
	template<class N>
	inline bool
	Term<N> :: isConstant() const {
		return term_.isConstant();
	}
	template<class N>
	inline bool
	Term<N> :: isReplaceable() const {
		return term_.isReplaceable();
	}
	template<class N>
	inline bool
	Term<N> :: isSimple() const {
		return term_.isSimple();
	}
	template<class N>
	inline bool
	Term<N> :: isComplex() const {
		return term_.isComplex();
	}
	template<class N>
	inline bool
	Term<N> :: isSymbol (const Symbol& symbol) const {
		return term_.isSymbol (symbol);
	}
	template<class N>
	template<class I>
	inline bool
	Term<N> :: isEqual (const I begin, const I end, const mdl :: Type* type) const {
		return term_.template isEqual<I> (begin, end, type);
	}
	template<class N>
	inline bool
	Term<N> :: contains (const Symbol& symbol) const {
		return term_.contains (symbol);
	}

	template<class N>
	inline void
	Term<N> :: operator = (const Term& term)
	{
		term_ = term.term_;
		rule_ = term.rule_;
		substitution_ = term.substitution_;
	}
	template<class N>
	template<class T>
	inline bool
	Term<N> :: operator == (const T& term) const
	{
		#ifdef DEBUG
		verifyIntegrity();
		#endif
		return term_.isEqual (term);
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
	Term<N> :: coinsides (const T& term) const {
		return term_.coinsides_p (term, this);
	}

	template<class N>
	inline const mdl :: Rule*
	Term<N> :: getRule() const {
		return rule_;
	}
	template<class N>
	const typename Term<N> :: Term_*
	Term<N> :: getParent() const {
		return term_.getParent();
	}
	template<class N>
	const mdl :: Type*
	Term<N> :: getType() const {
		return term_.getType();
	}
	template<class N>
	const typename Term<N> :: Term_*
	Term<N> :: getTerm() const {
		return &term_;
	}
	template<class N>
	inline void
	Term<N> :: setParent (const Term* parent) const {
		term_.setParent (parent);
	}
	template<class N>
	inline void
	Term<N> :: setType (const mdl :: Type* type) const {
		term_.setType (type);
	}

using manipulator :: space;
using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: underline;
using manipulator :: iterate;

	template<class N>
	inline void
	Term<N> :: translate (String& string, const mdl :: Type* type) const
	{
		if (rule_ == NULL) {
			translateVariable (string, type);
		} else {
			translateRule (string, type);
		}
	}

	template<class N>
	template<class I>
	inline void
	Term<N> :: copyNode (Iterator_& target, const I& source)
	{
		term_.copyNode (target, source);
		target->rule_ = source->getRule();
		target->substitution_ = Substitution_ :: create (source->getSubstitution());
	}
	template<class N>
	template<class I>
	inline bool
	Term<N> :: findNode (Iterator_& target, const I& source) {
		return term_.findNode (target, source);
	}
	template<class N>
	template<class I>
	inline void
	Term<N> :: addFindNode (Iterator_& target, const I& source) {
		term_.addFindNode (target, source);
	}

	template<class N>
	inline void
	Term<N> :: verifyIntegrity (const bool linear) const
	{
		term_.template verifyPlain<Term> (this, linear);
		term_.verifyNodes (linear);
	}

	template<class N>
	inline Size_t
	Term<N> :: getExpressionVolume() const {
		return term_.getExpressionVolume();
	}
	template<class N>
	inline void
	Term<N> :: showBody (String& string) const {
		term_.showBody (string);
 	}
	template<class N>
	inline void
	Term<N> :: showKind (String& string) const {
		term_.showKind (string);
 	}
	template<class N>
	inline void
	Term<N> :: showType (String& string) const {
		term_.showType (string);
 	}
	template<class N>
	inline void
	Term<N> :: showTerms (String& string) const	{
		term_.showTerms (string);
	}
	template<class N>
	inline void
	Term<N> :: writeMultylineForward (String& string, const Indent indent, int depth) const {
		term_.writeMultylineForward (string, indent, depth);
	}
	template<class N>
	inline void
	Term<N> :: writeMultylineBackward (String& string, const Indent indent, int depth) const {
		term_.writeMultylineBackward (string, indent, depth);
	}

	// object :: Object implementation
	template<class N>
	inline void
	Term<N> :: commitSuicide() {
		delete this;
	}
	template<class N>
	inline Size_t
	Term<N> :: getVolume() const
	{
		Size_t volume = term_.getVolume();
		if (substitution_ != NULL) {
			volume += substitution_->getVolume();
			volume += substitution_->getSizeOf();
		}
		return volume;
	}
	template<class N>
	inline Size_t
	Term<N> :: getSizeOf() const {
		return sizeof (Term);
	}
	template<class N>
	inline void
	Term<N> :: show (String& string) const {
		term_.show (string);
 	}
	template<class N>
	inline void
	Term<N> :: dump() const {
		term_.dump();
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class N>
	inline void
	Term<N> :: showRule (String& string) const
	{
		string << tab << "rule: ";
		if (rule_!= NULL) {
			rule_->replicateName (string);
		} else {
			string << "NULL";
		}
		string << endLine;
 	}
	template<class N>
	inline void
	Term<N> :: showSubstitution (String& string) const
	{
		string << tab << "substitution: " << endLine;
		if (substitution_ != NULL) {
			substitution_->show (string);
		} else {
			string << tab << "NULL";
		}
		string << endLine;
 	}

	template<class N>
	inline void
	Term<N> :: translateVariable (String& string, const mdl :: Type* supType) const
	{
		const mdl :: Type*
			infType = term_.getBegin()->getType();
		const mdl :: Variables*
			variables = form :: header :: Variables :: getCurrent();
		const header :: Variable*
			variable = variables->getDeclaration (term_.getBegin()->getLiteral());
		variable->translateReference (string);
		string << space;
		if (infType != supType) {
			const mdl :: Super*
				super = infType->getSuper (supType);
			super->translateReference (string);
			string << space;
		}
	}
	template<class N>
	inline void
	Term<N> :: translateRule (String& string, const mdl :: Type* supType) const
	{
		const mdl :: Type*
			infType = rule_->getType();
		const mdl :: Variables* const
			variables = rule_->getVariables();
		for (index :: Arity i = 0; i < variables->getSize(); ++ i) {
			const mdl :: header :: Variable* const
				variable = variables->getVariable (i);
			const Substitution_* substitution = substitution_->find (variable->getSymbol());
			substitution->getTerm()->translate (string, variable->getType());
		}
		rule_->translateName (string);
		string << space;

		if (infType != supType) {
			const mdl :: Super*
				super = infType->getSuper (supType);
			super->translateReference (string);
			string << space;
		}
	}

	template<class N>
	template<class T>
	inline void
	Term<N> :: verifyTerms (const T& terms, const bool linear) const {
		term_.verifyTerms (terms, linear);
	}
	template<class N>
	template<class T>
	inline void
	Term<N> :: verifyPlain (const T* term, const bool linear) const {
		term_.verifyPlain (term, linear);
	}
	template<class N>
	inline void
	Term<N> :: verifyType() const {
		term_.verifyType();
	}
	template<class N>
	template<class T>
	inline void
	Term<N> :: verifyInitial (const T* term, const bool linear) const {
		term_.verifyInitial (term, linear);
	}
	template<class N>
	template<class T>
	inline void
	Term<N> :: verifyTerminal (const T* term) const {
		term_.verifyTerminal (term);
	}
	template<class N>
	template<class T>
	inline void
	Term<N> :: verifyUniquity (const T& terms) const {
		term_.verifyUniquity (terms);
	}
	template<class N>
	inline void
	Term<N> :: verifyIteratibility (const bool linear) const {
		term_.verifyIteratibility (linear);
	}

	/******************************
	 *		Overloaded operators
	 ******************************/

	template<class N>
	inline String&
	operator << (String& string, const Term<N>& term)
	{
		term.show (string);
		return string;
	}
	template<class N>
	inline std :: ostream&
	operator << (std :: ostream& os, const Term<N>& term)
	{
		String string (1024);
		return os << (string << term);
	}
}
}
}

#endif /*MDL_EXPRESSION_PARSE_TERM_IPP_*/
