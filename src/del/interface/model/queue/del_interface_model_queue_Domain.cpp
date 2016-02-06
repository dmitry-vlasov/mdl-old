/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_model_queue_Domain.cpp                     */
/* Description:     abstract interface for domain element                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/model/queue/del_interface_model_queue_Element.hpp"

namespace del {
namespace interface {
namespace model {
namespace queue {

	/****************************
	 *		Public members
	 ****************************/

	bool
	Domain :: operator < (const Domain& domain) const
	{
		if (getConcept() < domain.getConcept()) {
			return true;
		}
		if (getConcept() > domain.getConcept()) {
			return false;
		}
		return getRelation() < domain.getRelation();
	}
	inline bool
	Domain :: operator > (const Domain& domain) const {
		return domain.operator < (*this);
	}
	bool
	Domain :: operator == (const Domain& domain) const
	{
		return
			(getConcept() == domain.getConcept()) &&
			(getRelation() == domain.getRelation());
	}
}
}
}
}


