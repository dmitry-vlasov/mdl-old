/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_Theory.hpp                                 */
/* Description:     abstract interfaces for mdl theory                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_THEORY_HPP_
#define MDL_INTERFACE_THEORY_HPP_

#include "mdl/interface/object/mdl_interface_object.hpp"

namespace mdl {
namespace interface {

class Theory : virtual public object :: Identifiable {
public :
	virtual void checkUnused (const value :: Name) const = 0;
	virtual index :: Form checkUsed (const mdl :: Identificator*) const = 0;
	virtual void addComponent (object :: Verifiable*) = 0;
	virtual void addName (const index :: Form, const value :: Name) = 0;

	virtual index :: Form getIndex (const Identificator*) const = 0;
	virtual index :: Form getIndexUp (const Identificator*) const = 0;
	virtual index :: Form getIndexDown (const Identificator*) const = 0;

	virtual Identificator* getPath() = 0;
	virtual const Identificator* getPath() const = 0;
};

}
}

#endif /*MDL_INTERFACE_THEORY_HPP_*/
