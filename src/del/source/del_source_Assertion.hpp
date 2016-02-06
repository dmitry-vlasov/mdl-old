/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_Assertion.hpp                                 */
/* Description:     test assertion class                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.hpp"

namespace del {
namespace source {

class Assertion :
	public del :: Assertion,
	public Scalar<Assertion> {
public :
	Assertion
	(
		const Location&,
		const del :: Comments* const,
		const value :: Theory,
		const value :: Signature,
		const vector :: value :: Symbol&,
		const bool
	);
	virtual ~ Assertion();

	// Assertion interface
	virtual void verify() const;
	virtual del :: Decompose* decompose();
	virtual del :: Decomposition* decomposition();

	// Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// Object interface
	virtual void commitSuicide();
	virtual Size_t getSizeOf() const;
	virtual Size_t getVolume() const;

private :
	const Location location_;
	const del :: Comments* comments_;
	del :: Decompose* decompose_;
	del :: Decomposition* decomposition_;
};

}
}


