/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_object_Identifiable.hpp                    */
/* Description:     abstract interface for identifiable objects              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_OBJECT_IDENTIFIABLE_HPP_
#define MDL_INTERFACE_OBJECT_IDENTIFIABLE_HPP_

#include "mdl/interface/object/mdl_interface_object_Verifiable.hpp"

namespace mdl {
namespace interface {
namespace object {

class Identifiable : virtual public Verifiable {
public :
	virtual const Location& getLocation() const = 0;
	virtual value :: Name getName() const = 0;

	virtual void translateName (String&, const index :: Arity = 0) const = 0;
	virtual void replicateName (String&) const = 0;

	virtual mdl :: Theory* getTheory() = 0;
	virtual Identificator* getIdentificator() = 0;
	virtual const mdl :: Theory* getTheory() const = 0;
	virtual const Identificator* getIdentificator() const = 0;

	virtual void replicateReversedName (String&) const;
};

}
}
}

#endif /*MDL_INTERFACE_OBJECT_IDENTIFIABLE_HPP_*/
