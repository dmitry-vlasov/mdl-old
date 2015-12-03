/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_header_Disjointeds.hpp                     */
/* Description:     abstract interface for set of disjointed variable sets   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_HEADER_DISJOINTEDS_HPP_
#define MDL_INTERFACE_HEADER_DISJOINTEDS_HPP_

#include "mdl/interface/mdl_interface.dpp"
#include "mdl/interface/object/mdl_interface_object.hpp"

namespace mdl {
namespace interface {
namespace header {

class Disjointeds : virtual public object :: Writable {
public :
	virtual void check
	(
		const array :: Substitution*,
		const Assertion*
	) const = 0;
	virtual bool check
	(
		const list :: Substitution*,
		const Assertion*
	) const = 0;
	virtual bool check (const Symbol&, const Symbol&) const = 0;
	virtual bool isMoreRestrictive (const Disjointeds*) const = 0;
	virtual bool isLessRestrictive (const Disjointeds*) const = 0;
};

}
}
}

#endif /*MDL_INTERFACE_HEADER_DISJOINTEDS_HPP_*/
