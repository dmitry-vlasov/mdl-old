/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_prototype_Singleton.ipp              */
/* Description:     represents a singleton node (0-dimensional)              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_NODE_PROTOTYPE_SINGLETON_IPP_
#define MDL_EXPRESSION_NODE_PROTOTYPE_SINGLETON_IPP_

namespace mdl {
namespace expression {
namespace node {
namespace prototype {

	/****************************
	 *		Public members
	 ****************************/

	template<class T, class N, template<class, class> class S, class A>
	inline
	Singleton<T, N, S, A> :: Singleton() :
	Symbol (),
	terms_ () {
	}
	template<class T, class N, template<class, class> class S, class A>
	inline
	Singleton<T, N, S, A> :: Singleton (const Symbol& symbol) :
	Symbol (symbol),
	terms_ () {
	}
	template<class T, class N, template<class, class> class S, class A>
	inline
	Singleton<T, N, S, A> :: ~ Singleton() {
	}

	template<class T, class N, template<class, class> class S, class A>
	inline void
	Singleton<T, N, S, A> :: deleteNodes() const {
	}

	template<class T, class N, template<class, class> class S, class A>
	template<class P>
	inline void
	Singleton<T, N, S, A> :: cloneContents (P* pool) const {
		terms_.cloneContents (pool);
	}

	template<class T, class N, template<class, class> class S, class A>
	inline typename Singleton<T, N, S, A> :: const_Iterator_
	Singleton<T, N, S, A> :: getIterator() const {
		return const_Iterator_ (this);
	}
	template<class T, class N, template<class, class> class S, class A>
	inline typename Singleton<T, N, S, A> :: Iterator_
	Singleton<T, N, S, A> :: getIterator() {
		return Iterator_ (this);
	}

	template<class T, class N, template<class, class> class S, class A>
	inline typename Singleton<T, N, S, A> :: Terms_&
	Singleton<T, N, S, A> :: terms() {
		return terms_;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline const typename Singleton<T, N, S, A> :: Terms_&
	Singleton<T, N, S, A> :: getTerms() const {
		return terms_;
	}

	template<class T, class N, template<class, class> class S, class A>
	inline void
	Singleton<T, N, S, A> :: write (String& string) const {
		Symbol :: write (string);
	}
	template<class T, class N, template<class, class> class S, class A>
	inline void
	Singleton<T, N, S, A> :: operator = (const Symbol& symbol) {
		Symbol :: operator = (symbol);
	}
	template<class T, class N, template<class, class> class S, class A>
	inline void
	Singleton<T, N, S, A> :: operator = (const Singleton& singleton) {
		Symbol :: operator = (singleton);
		terms_ = singleton.terms_;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline bool
	Singleton<T, N, S, A> :: isReacheable (const index :: Step) const {
		return true;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline index :: Step
	Singleton<T, N, S, A> :: getLevel() const {
		return 0;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline void
	Singleton<T, N, S, A> :: setLevel (const index :: Step) {
	}
	template<class T, class N, template<class, class> class S, class A>
	inline bool
	Singleton<T, N, S, A> :: getAccessible() const {
		return true;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline void
	Singleton<T, N, S, A> :: setAccessible (const bool) {
	}

	template<class T, class N, template<class, class> class S, class A>
	template<class T1, class N1, template<class, class> class S1, class A1>
	inline bool
	Singleton<T, N, S, A> :: coinsides
	(
		const Singleton<T1, N1, S1, A1>& singleton,
		const Term_* term0,
		const T1* term1
	) const
	{
		bool result = true;
		result = result && (Symbol :: operator == (singleton));
		result = result && (terms_.coinside (singleton.getTerms(), term0, term1));
		return result;
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	template<class T, class N, template<class, class> class S, class A>
	inline void
	Singleton<T, N, S, A> :: showSymbol (String& string) const {
		Symbol :: show (string);
	}
	template<class T, class N, template<class, class> class S, class A>
	inline void
	Singleton<T, N, S, A> :: showTerms (String& string) const {
		terms_.show (string);
		string << endLine;
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	Singleton<T, N, S, A> :: showAll (String& string) const
	{
		showSymbol (string);
		showTerms (string);
	}
	template<class T, class N, template<class, class> class S, class A>
	inline void
	Singleton<T, N, S, A> :: showBack (String& string) const
	{
		showSymbol (string);
		if (Config :: expressionsWithTypes()) {
			terms_.showTypes (string, false);
		}
	}
	template<class T, class N, template<class, class> class S, class A>
	inline void
	Singleton<T, N, S, A> :: showKind (String& string) {
		string << "Singleton" << endLine;
	}

	// object :: Object implementation
	template<class T, class N, template<class, class> class S, class A>
	inline void
	Singleton<T, N, S, A> :: commitSuicide() {
		delete this;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline Size_t
	Singleton<T, N, S, A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += Symbol :: getVolume();
		volume += terms_.getVolume();
		return volume;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline Size_t
	Singleton<T, N, S, A> :: getSizeOf() const {
		return sizeof (Singleton);
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	Singleton<T, N, S, A> :: show (String& string) const
	{
		Symbol :: show (string);
		if (Config :: expressionsWithTypes()) {
			terms_.showTypes (string, false);
		}
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	Singleton<T, N, S, A> :: dump() const
	{
		enum {
			INITIAL_STRING_CAPACITY = 64
		};
		String string (INITIAL_STRING_CAPACITY);
		show (string);
		std :: cout << string;
	}

	/****************************
	 *		Protected members
	 ****************************/

	template<class T, class N, template<class, class> class S, class A>
	template<class R>
	Size_t
	Singleton<T, N, S, A> :: getAggregateVolume (const R* const object) const
	{
		if (object == NULL) {
			return 0;
		}
		Size_t volume = 0;
		volume += object->getVolume();
		volume += object->getSizeOf();
		return volume;
	}
	template<class T, class N, template<class, class> class S, class A>
	template<class R>
	void
	Singleton<T, N, S, A> :: deleteAggregateObject (R*& object)
	{
		if (object == NULL) {
			return;
		}
		delete object;
		object = NULL;
	}

	/******************************
	 *		Overloaded operators
	 ******************************/

	template<class T, class N, template<class, class> class S, class A>
	String&
	operator << (String& string, const Singleton<T, N, S, A>& singleton)
	{
		Mode mode (string);
		singleton.showSymbol (string);
		if (mode.getValue (Mode :: SHOW_TERMS)) {
			singleton.showTerms (string);
			string << endLine;
		}
		return string;
	}
}
}
}
}

#endif /*MDL_EXPRESSION_NODE_PROTOTYPE_SINGLETON_IPP_*/
