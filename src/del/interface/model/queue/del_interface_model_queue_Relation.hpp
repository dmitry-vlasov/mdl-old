/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_model_queue_Relation.hpp                   */
/* Description:     abstract interface for relations in model trees          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface_Object.hpp"
#include "del/interface/del_interface_Cloneable.hpp"
#include "del/interface/model/queue/del_interface_model_queue.dpp"

namespace del {
namespace interface {
namespace model {
namespace queue{

class Relation : public Object {
public :
	virtual void addPair (const value :: Variable, const value :: Variable) = 0;
	virtual bool isTrue (const value :: Variable, const value :: Variable) const = 0;
};

}
}
}
}


