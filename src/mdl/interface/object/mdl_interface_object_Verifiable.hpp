/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_object_Verifiable.hpp                      */
/* Description:     abstract interface for verifiable objects                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_OBJECT_VERIFIABLE_HPP_
#define MDL_INTERFACE_OBJECT_VERIFIABLE_HPP_

#include "mdl/interface/object/mdl_interface_object_Buildable.hpp"

namespace mdl {
namespace interface {
namespace object {

class Verifiable : virtual public Buildable {
public :
	Verifiable();
	virtual ~ Verifiable();

	virtual bool isVerified() const;

	virtual void check();
	virtual void compress();
	virtual void reprove();
	virtual void prove();

	virtual void mine (String&) const;
	virtual void setContents (Contents*);

protected :
	Contents* contents_;
};

}
}
}

#endif /*MDL_INTERFACE_OBJECT_VERIFIABLE_HPP_*/
