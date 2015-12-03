/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_interface_source_Constants.hpp                       */
/* Description:     abstract interface for smm constants                     */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_INTERFACE_SOURCE_CONSTANTS_HPP_
#define SMM_INTERFACE_SOURCE_CONSTANTS_HPP_

#include "smm/interface/object/smm_interface_object.hpp"

namespace smm {
namespace interface {
namespace source {

class Constants : public object :: Verifiable {
public :
	virtual void addTo (vector :: Literal&) const = 0;
};

}
}
}

#endif /*SMM_INTERFACE_SOURCE_CONSTANTS_HPP_*/
