/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_expression_Expression.ipp                             */
/* Description:     metamath symbolic expression                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_EXPRESSION_EXPRESSION_IPP_
#define MM_EXPRESSION_EXPRESSION_IPP_

namespace mm {
namespace expression {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Expression :: Expression (const Size_t initialCapacity) :
	expression_ (initialCapacity) {
	}
	inline
	Expression :: Expression (const Expression& expression) :
	expression_ (expression.expression_) {
	}

	inline index :: Literal
	Expression :: getSize() const {
		return expression_.getSize();
	}
	inline const Symbol&
	Expression :: getType() const {
		return expression_.getReference (0);
	}
	inline const Symbol&
	Expression :: getSymbol (const index :: Literal index) const {
		return expression_.getReference (index);
	}
	inline const Symbol&
	Expression :: operator [] (const index :: Literal index) const {
		return expression_.getReference (index);
	}
	inline void
	Expression :: addSymbol (const Symbol& symbol) {
		expression_.add (symbol);
	}

	inline void
	Expression :: copy (const Expression* const expression) {
		expression_.copy (expression->expression_);
	}
	inline void
	Expression :: copy
	(
		const Symbol symbol_1,
		const Symbol symbol_2
	) {
		expression_.clear();
		expression_.add (symbol_1);
		expression_.add (symbol_2);
	}
	inline bool
	Expression :: operator == (const Expression& expression) const {
		return expression_ == expression.expression_;
	}
	inline bool
	Expression :: operator != (const Expression& expression) const {
		return !(operator == (expression));
	}
	inline void
	Expression :: operator = (const Expression& expression) {
		expression_.copy (expression.expression_);
	}

	inline bool
	Expression :: isTerm() const {
		return !(isStatement());
	}
	inline bool
	Expression :: isTrivial() const
	{
		return
			(getSize() == 2) &&
			(getSymbol (0).isConstant()) &&
			(getSymbol (1).isVariable());
	}

	inline void
	Expression :: init() {
	}
	void
	Expression :: clear() {
		expression_.clear();
	}

	// object :: Object implementation
	inline void
	Expression :: commitSuicide() {
		delete this;
	}
	inline Size_t
	Expression :: getSizeOf() const {
		return sizeof (Expression);
	}
	inline Size_t
	Expression :: getVolume() const {
		return expression_.getVolume();
	}
	inline void
	Expression :: show (String& string) const
	{
		for (index :: Literal i = 0; i < expression_.getSize(); ++ i) {
			const Symbol&
				symbol = expression_.getReference (i);
			string << symbol;
		}
	}

	/*******************************
	 *		Overloaded operators
	 *******************************/

	template<class T>
	inline T&
	operator << (T& string, const Expression& expression) {
		expression.write (string);
		return string;
	}
}
}

#endif /* MM_EXPRESSION_EXPRESSION_IPP_ */
