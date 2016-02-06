/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_stack_Line.hpp                              */
/* Description:     metamath stack line                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "expression/mm_expression.hpp"
#include "interface/object/mm_interface_object.hpp"

namespace mm {
namespace interface {
namespace stack {

class Line : public Scalar<Line> {
public :
	Line ();
	Line (const Expression&);
	Line (const Expression* const);
	~ Line();

	void init();

	bool isTerm() const;

	const Expression* getExpression() const;
	const target :: Step* getStep() const;
	const source :: Hypothesis* getHypothesis() const;

	void setStep (const target :: Step*);
	void setHypothesis (const source :: Hypothesis*) const;
	void setLine (const Line*);

	void copyExpression (const Expression*);
	void copyExpression (const Symbol, const Symbol);
	void copyHypothesis (const Expression*) const;

	// nstd :: Object interface
	void commitSuicide();
	Size_t getVolume () const;
	Size_t getSizeOf () const;
	void show (String&) const;

private :
	Expression expression_;
	const target :: Step* step_;
	mutable const source :: Hypothesis* hypothesis_;
};

}
}
}

#include "interface/stack/mm_interface_stack_Line.ipp"


