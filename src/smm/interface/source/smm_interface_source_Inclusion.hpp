/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_interface_source_Inclusion.hpp                       */
/* Description:     abstract interface for smm inclusion                     */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "smm/interface/object/smm_interface_object.hpp"

namespace smm {
namespace interface {
namespace source {

class Inclusion : public object :: Verifiable {
public :
	virtual const String& getPath() const = 0;
};

}
}
}


