/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_expression_Expression.ipp                            */
/* Description:     smm symbolic expression                                  */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_EXPRESSION_EXPRESSION_IPP_
#define SMM_EXPRESSION_EXPRESSION_IPP_

namespace smm {
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
	Expression :: getVariable() const {
		return expression_.getReference (1);
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
	inline bool
	Expression :: contains (const value :: Literal x) const
	{
		for (index :: Literal i = 0; i < expression_.getSize(); ++ i) {
			const Symbol&
				symbol = expression_.getReference (i);
			if (symbol.getLiteral() == x) {
				return true;
			}
		}
		return false;
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
		expression.show (string);
		return string;
	}
}
}

#endif /* SMM_EXPRESSION_EXPRESSION_IPP_ */
