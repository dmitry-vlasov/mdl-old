/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_Answer.hpp                                 */
/* Description:     abstract interface for answer class                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_INTERFACE_ANSWER_HPP_
#define DEL_INTERFACE_ANSWER_HPP_

#include "del/interface/del_interface_Writable.hpp"

namespace del {
namespace interface {

class Answer : public Writable {
public :
	virtual bool isPositive() const = 0;
};

}
}

#endif /*DEL_INTERFACE_ANSWER_HPP_*/
