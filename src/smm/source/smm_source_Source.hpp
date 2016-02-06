/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File Name:       smm_source_Source.hpp                                    */
/* Description:     smm source                                               */
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

class Source :
	public smm :: Source,
	public Scalar<Source> {
public :
	Source();
	virtual ~ Source();

	// smm :: Source interface
	virtual void addComponent (const object :: Verifiable*);

	// object :: Verifiable interface
	virtual void verify() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	typedef
		list :: object :: Verifiable
		Contents_;

	Contents_* contents_;
};

}
}


