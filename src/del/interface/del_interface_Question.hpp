/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_Question.hpp                               */
/* Description:     abstract interface for identificators                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_QUESTION_HPP_
#define MDL_INTERFACE_QUESTION_HPP_

#include "del/interface/del_interface_Writable.hpp"

namespace del {
namespace interface {

class Question : public Writable {
public :
	virtual const Answer* solve (Model* = NULL) const = 0;

};

}
}

#endif /*MDL_INTERFACE_QUESTION_HPP_*/
