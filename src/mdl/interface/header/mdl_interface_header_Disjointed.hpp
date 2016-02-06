/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_header_Disjointed.hpp                      */
/* Description:     abstract interface for disjointed variable set           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.dpp"
#include "mdl/interface/object/mdl_interface_object.hpp"

namespace mdl {
namespace interface {
namespace header {

class Disjointed : virtual public object :: Writable {
public :
	virtual bool noRestriction() const = 0;
	virtual void check
	(
		const array :: Substitution* const,
		const Assertion* const
	) const = 0;
	virtual bool check
	(
		const list :: Substitution* const,
		const Assertion* const
	) const = 0;
	virtual bool contains (const value :: Literal) const = 0;
	virtual bool isMoreRestrictive (const Disjointed*) const = 0;
	virtual bool isLessRestrictive (const Disjointed*) const = 0;
};

}
}
}


