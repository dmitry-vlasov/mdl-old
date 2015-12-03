/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_interface_object_Verifiable.hpp                      */
/* Description:     abstract interface for verifiable object                 */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_INTERFACE_OBJECT_VERIFIABLE_HPP_
#define SMM_INTERFACE_OBJECT_VERIFIABLE_HPP_

#include "smm/interface/object/smm_interface_object_Object.hpp"

namespace smm {
namespace interface {
namespace object {

class Verifiable : virtual public Object {
public :
	virtual void verify() const = 0;
};

}
}
}

#endif /*SMM_INTERFACE_OBJECT_VERIFIABLE_HPP_*/
