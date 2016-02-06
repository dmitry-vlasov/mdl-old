/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_source_Block.hpp                            */
/* Description:     abstract interface for metamath block                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "interface/object/mm_interface_object.hpp"

namespace mm {
namespace interface {
namespace source {

class Block : public object :: Verifiable {
public :
	virtual const Source* getSource() const = 0;
	virtual const Constants* getConstants() const = 0;
	virtual const Variables* getVariables() const = 0;
	virtual const Disjoined* getDisjoined() const = 0;
	virtual const Hypothesis* getHypothesis() const = 0;

	virtual void pushConstants (const Constants* const) = 0;
	virtual void pushVariables (const Variables* const) = 0;
	virtual void pushDisjoined (const Disjoined* const) = 0;
	virtual void pushHypothesis (const Hypothesis* const) = 0;
	virtual void pushAssertion (const Assertion* const) = 0;
	virtual void pushBlock (const Block* const) = 0;
	virtual void pushSource (const Source* const) = 0;
	virtual void pushInclude (const Include* const)= 0;

	virtual void translateTo (target :: Block* const) const  = 0;
};

}
}
}


