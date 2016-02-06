/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File Name:       smm_source_Inclusion.hpp                                 */
/* Description:     smm file inclusion                                       */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "smm/interface/smm_interface.hpp"

namespace smm {
namespace source {

class Inclusion :
	public smm :: Inclusion,
	public Scalar<Inclusion> {
public :
	Inclusion (const Location& location, const String&);
	virtual ~ Inclusion();

	// smm :: Inclusion interface
	virtual const String& getPath() const;

	// object :: Verifiable interface
	virtual void verify() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	const Location location_;
	const String path_;
};

}
}


