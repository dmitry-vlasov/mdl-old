/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_proof_Question.hpp                         */
/* Description:     abstract interface for unproved proof step               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_PROOF_QUESTION_HPP_
#define MDL_INTERFACE_PROOF_QUESTION_HPP_

#include "mdl/interface/proof/mdl_interface_proof_Step.hpp"

namespace mdl {
namespace interface {
namespace proof {

class Question : virtual public Step {
public :
	virtual void compress (const Time timeLimit) = 0;
	virtual void prove (const Time timeLimit) = 0;
	virtual void clear() = 0;
	virtual bool isProved() const = 0;
	virtual void confirmAnswer (Step*) = 0;
	virtual void confirmGuess() = 0;
	virtual void rejectGuess() = 0;
	virtual Step* getAnswer() = 0;
	virtual Step* getGuess() = 0;
	virtual const Step* getHint() = 0;
	virtual const Step* getAnswer() const = 0;
	virtual const Step* getGuess() const = 0;
	virtual const Step* getHint() const = 0;
};

}
}
}

#endif /*MDL_INTERFACE_PROOF_QUESTION_HPP_*/
