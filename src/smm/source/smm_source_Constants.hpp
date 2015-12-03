/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File Name:       smm_source_Constants.hpp                                 */
/* Description:     smm constants                                            */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_SOURCE_CONSTANTS_HPP_
#define SMM_SOURCE_CONSTANTS_HPP_

#include "smm/interface/smm_interface.hpp"

namespace smm {
namespace source {

class Constants :
	public smm :: Constants,
	public Scalar<Constants> {
public :
	Constants
	(
		const Location&,
		const Expression*
	);
	virtual ~ Constants();

	// smm :: Constants interface
	virtual void addTo (vector :: Literal&) const;

	// object :: Verifiable interface
	virtual void verify() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	const Location location_;
	const Expression* literals_;
};

}
}

#endif /*SMM_SOURCE_CONSTANTS_HPP_*/
