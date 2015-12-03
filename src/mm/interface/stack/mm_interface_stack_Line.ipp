/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_stack_Line.ipp                              */
/* Description:     metamath stack line                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_INTERFACE_STACK_LINE_IPP_
#define MM_INTERFACE_STACK_LINE_IPP_

namespace mm {
namespace interface {
namespace stack {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Line :: Line() :
	expression_ (),
	step_ (NULL),
	hypothesis_ (NULL) {
	}
	inline
	Line :: Line (const Expression& expression) :
	expression_ (expression),
	step_ (NULL),
	hypothesis_ (NULL) {
	}
	inline
	Line :: Line (const Expression* const expression) :
	expression_ (*expression),
	step_ (NULL),
	hypothesis_ (NULL) {
	}
	Line :: ~ Line() {
	}

	inline void
	Line :: init()
	{
		step_ = NULL;
		hypothesis_ = NULL;
	}
	inline bool
	Line :: isTerm() const {
		return expression_.isTerm();
	}

	inline const Expression*
	Line :: getExpression() const {
		return &expression_;
	}
	inline const target :: Step*
	Line :: getStep() const {
		return step_;
	}
	inline const source :: Hypothesis*
	Line :: getHypothesis() const {
		return hypothesis_;
	}

	inline void
	Line :: setStep (const target :: Step* step) {
		step_ = step;
	}
	inline void
	Line :: setHypothesis (const source :: Hypothesis* hypothesis) const {
		hypothesis_ = hypothesis;
	}
	inline void
	Line :: setLine (const Line* line)
	{
		expression_.copy (line->getExpression());
		step_ = line->step_;
		hypothesis_ = line->hypothesis_;
	}

	inline void
	Line :: copyExpression (const Expression* expression) {
		expression_.copy (expression);
	}
	inline void
	Line :: copyExpression (const Symbol type, const Symbol variable) {
		expression_.copy (type, variable);
	}
	inline void
	Line :: copyHypothesis (const Expression* hypothesis) const {
		const_cast<source :: Hypothesis*>(hypothesis_)->assignTo (hypothesis);
	}
}
}
}

#endif /* MM_INTERFACE_STACK_LINE_IPP_ */
